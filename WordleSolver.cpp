#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include "WordleSolver.h"

WordleSolver::WordleSolver() {}

void WordleSolver::init(std::string filename) {
    std::ifstream stream = std::ifstream(filename);
    if (!stream.good()) {
        throw std::invalid_argument("File could not be opened.");
    }

    std::string nextWord;
    while (getline(stream, nextWord)) {
        if (nextWord.size() == numLetters) {
            availableOptions.push_back(nextWord);
            validOptions.push_back(nextWord);
        } else {
            throw std::invalid_argument("File contained non-5-letter words.");
        }
    }
}

// invariant:
void WordleSolver::takeGuess(std::string guess, std::vector<int> feedback) {
    auto guessInOptions = std::find(availableOptions.begin(), availableOptions.end(), guess);
    if (guessInOptions == availableOptions.end()) {
        throw std::invalid_argument("Invalid guess.");
    }
    if (feedback.size() != numLetters) {
        throw std::invalid_argument("Feedback did not contain exactly 5 numbers.");
    }
    for (int i : feedback) {
        if (i < 0 || i > 2)
            throw std::invalid_argument("Feedback contained invalid number.");
    }

    validOptions.erase(guessInOptions);
    validOptions.erase(std::find(validOptions.begin(), validOptions.end(), guess));

    // update valid options, removing now invalid options
    // resort available options
}

int WordleSolver::numOptions() {
    return validOptions.size();
}

// invariant: assumes list of valid 
std::map<std::string, bool> WordleSolver::getAllOptions(int n) {
    if (n > availableOptions.size()) {
        throw std::invalid_argument("n > number of options remaining");
    }
    std::map<std::string, bool> options;
    for (int i = 0; i < n; i++) {
        options.insert(std::pair<std::string, bool>(availableOptions[i],
            std::find(validOptions.begin(), validOptions.end(), availableOptions[i]) != validOptions.end()));
    }
    return options;
}

std::map<std::string, bool> WordleSolver::getValidOptions(int n) {
    if (n > validOptions.size()) {
        throw std::invalid_argument("n > number of valid options remaining");
    }
    std::map<std::string, bool> options;
    for (int i = 0; i < n; i++) {
        options.insert(std::pair<std::string, bool>(validOptions[i], true));
    }
    return options;
}

// note: assumes the given word exists within the list of available words
double WordleSolver::calcEffect(std::string word) {
    double sum = 0;
    for (int i = 0; i < numLetters; i++) {
        int numExactOccurences = 0;
        int numAnyOccurences = 0;
        int numNoOccurences = 0;
        for (auto it = availableOptions.begin(); it != availableOptions.end(); it++) {
            if ((*it)[i] == word[i])
                ++numExactOccurences;
            if ((*it).find(word[i]) >= 0)
                ++numAnyOccurences;
            else 
                ++numNoOccurences;
        }
        sum += (numExactOccurences / availableOptions.size()) * 3;
        sum += (numAnyOccurences / availableOptions.size());
        sum += (numNoOccurences / availableOptions.size()) * 2;
    }
    return sum;
}

std::vector<std::string> sortBy(std::vector<std::string> list, double (*func)(std::string)) {
    
}
    