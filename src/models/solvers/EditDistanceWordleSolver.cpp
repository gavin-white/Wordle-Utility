#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "models/solvers/EditDistanceWordleSolver.hpp"
#include "models/games/EditDistanceWordleGame.hpp"
#include "structures/LevenshteinTree.hpp"

EditDistanceWordleSolver::EditDistanceWordleSolver(std::vector<std::string> allowedWords) {
    this->availableOptions = allowedWords;
    this->validOptions = allowedWords;
    LevenshteinTree* tree = LevenshteinTree::buildTree(allowedWords);
    for (std::string word : allowedWords) {
        this->levenshteinTuples[word] = tree->levenshteinDistance(word);
    }
    delete tree;
}

int EditDistanceWordleSolver::numOptions() const {
    return validOptions.size();
}

void EditDistanceWordleSolver::takeGuess(std::string guess, int feedback) {
    if (feedback == 0) {
        validOptions.clear();
        validOptions.push_back(guess);
        return;
    }

    validOptions.erase(
    std::remove_if(validOptions.begin(), validOptions.end(),
                   [&](const std::string& option) {
                       return levenshteinTuples[option].second[guess] != feedback;
                   }),
    validOptions.end());

    LevenshteinTree* tree = LevenshteinTree::buildTree(validOptions);
    for (std::string word : availableOptions) {
        this->levenshteinTuples[word] = tree->levenshteinDistance(word);
    }
    delete tree;

    sortBy(validOptions);
    sortBy(availableOptions);
}

std::vector<std::pair<std::string, bool>> EditDistanceWordleSolver::recommendGuesses(unsigned int num) {
    std::vector<std::pair<std::string, bool>> result;
    for (unsigned int i = 0; result.size() < num; i++) {
        if (std::find(validOptions.begin(), validOptions.end(), availableOptions[i]) != validOptions.end()) {
            result.push_back(std::pair<std::string, bool>(availableOptions[i], 
            std::find(validOptions.begin(), validOptions.end(), availableOptions[i]) != validOptions.end()));
        }
    }
    return result;
}

std::vector<std::pair<std::string, bool>> EditDistanceWordleSolver::matchGuesses(std::string temp, unsigned int num) {
    std::vector<std::pair<std::string, bool>> options;
    for (std::string& option : availableOptions) {
        bool flag = false;
        if (temp.size() != option.size()) continue;
        for (unsigned int i = 0; i < temp.size(); i++) {
            if (temp[i] != '_' && temp[i] != option[i]) {
                flag = true;
                break;
            }
        }
        if (!flag) {
            options.push_back(std::pair<std::string, bool>(option,
                std::find(validOptions.begin(), validOptions.end(), option) != validOptions.end()));
        }
        if (options.size() >= num) break;
    }
    return options;
}

double EditDistanceWordleSolver::calcEffect(const std::string word) {
    LevenshteinTree::LevenshteinTuple tuple = levenshteinTuples[word];
    double total = (double) validOptions.size();
    double sum = 0;
    for (auto& frequency : tuple.first) {
        sum += frequency.second / total * (double) frequency.second;
    }

    return sum;
}

void EditDistanceWordleSolver::sortBy(std::vector<std::string> &list) {
    // making use of Schwartzian transform (decorate-sort-undecorate) to efficiently sort list
    std::vector<std::pair<std::string, double>> decoratedList;
    for (std::string& word : list) {
        decoratedList.push_back(std::pair<std::string, double>(word, calcEffect(word)));
    }

    std::sort(decoratedList.begin(), decoratedList.end(),
        [](auto& pair1, auto& pair2) { return pair1.second > pair2.second; });
        // lambda to sort in descending order of values
    
    list.clear();
    for (auto& elem : decoratedList) {
        list.push_back(elem.first);
    }
}
