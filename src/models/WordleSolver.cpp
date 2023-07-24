#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include "models/WordleSolver.hpp"

WordleSolver::WordleSolver(std::vector<std::string> allowedWords) {
    if (allowedWords.size() == 0) 
        throw std::invalid_argument("Provided word list is empty.");
    numLetters = allowedWords[0].size();
    for (std::string& word : allowedWords) {
        if (word.size() != numLetters) {
            throw std::invalid_argument("Provided word list contains words of different lengths.");
        }
    }

    for (unsigned int i = 0; i < numLetters; i++) {
        std::unordered_map<char, int> freqs;
        std::unordered_map<char, int> freqs2;
        for (unsigned char letter = 'a'; letter <= 'z'; letter++) {
            freqs.insert(std::pair<char, int>(letter, 0));
            freqs2.insert(std::pair<char, int>(letter, 0));
        }
        letterFrequencies.push_back(freqs);
        wordsWithLetterHereOrWithout.push_back(freqs2);
    }

    for (unsigned char letter = 'a'; letter <= 'z'; letter++) {
        wordsWithLetter.insert(std::pair<char, int>(letter, 0));
        wordsWithoutLetter.insert(std::pair<char, int>(letter, 0));
    }

    alreadyFound.assign(numLetters, false);
    updateFrequencies();
    sortBy(availableOptions);
    sortBy(validOptions);
}

// invariant:
void WordleSolver::takeGuess(std::string guess, const std::vector<int> feedback) {
    auto guessInOptions = std::find(availableOptions.begin(), availableOptions.end(), guess);
    if (guessInOptions == availableOptions.end()) {
        throw std::invalid_argument("Invalid guess.");
    }
    if (feedback.size() != numLetters) {
        throw std::invalid_argument("Feedback did not contain exactly 5 numbers.");
    }

    availableOptions.erase(guessInOptions);
    if (std::find(validOptions.begin(), validOptions.end(), guess) != validOptions.end()) {
        validOptions.erase(std::find(validOptions.begin(), validOptions.end(), guess));
    }

    for (unsigned int i = 0; i < numLetters; i++) {
        switch (feedback[i]) {
            case 0:
                for (unsigned int j = 0; j < validOptions.size(); j++) {
                    if (validOptions[j].find(guess[i]) != std::string::npos && validOptions[j].find_first_of(guess[i]) == validOptions[j].find_last_of(guess[i])) {
                        validOptions.erase(validOptions.begin() + j);
                        j--;
                    }
                }
                break;
            case 1: 
                for (unsigned int j = 0; j < validOptions.size(); j++) {
                    if (validOptions[j][i] == guess[i]
                        || validOptions[j].find(guess[i]) == std::string::npos) {
                        validOptions.erase(validOptions.begin() + j);
                        j--;
                    }
                }
                break;
            case 2:
                alreadyFound[i] = true;
                for (unsigned int j = 0; j < validOptions.size(); j++) {
                    if (validOptions[j][i] != guess[i]) {
                        validOptions.erase(validOptions.begin() + j);
                        j--;
                    }
                }
                break;
            default:
                throw std::invalid_argument("Feedback contained non-0-1-or-2 number.");
        }
    }

    updateFrequencies();
    sortBy(availableOptions);
    sortBy(validOptions);
}

int WordleSolver::numOptions() {
    return validOptions.size();
}

// invariant: assumes list of valid 
std::vector<std::pair<std::string, bool>> WordleSolver::getAllOptions(unsigned int n) {
    if (n > availableOptions.size()) {
        throw std::invalid_argument("n > number of options remaining");
    }
    std::vector<std::pair<std::string, bool>> options;
    for (unsigned int i = 0; i < n; i++) {
        options.push_back(std::pair<std::string, bool>(availableOptions[i],
            std::find(validOptions.begin(), validOptions.end(), availableOptions[i]) != validOptions.end()));
    }
    return options;
}

std::vector<std::pair<std::string, bool>> WordleSolver::getValidOptions(unsigned int n) {
    if (n > validOptions.size()) {
        throw std::invalid_argument("n > number of valid options remaining");
    }
    std::vector<std::pair<std::string, bool>> options;
    for (unsigned int i = 0; i < n; i++) {
        options.push_back(std::pair<std::string, bool>(validOptions[i], true));
    }
    return options;
}

void WordleSolver::updateFrequencies() {
    for (unsigned int i = 0; i < numLetters; i++) {
        for (unsigned char letter = 'a'; letter <= 'z'; letter++) {
            letterFrequencies[i][letter] = 0;
            wordsWithLetterHereOrWithout[i][letter] = 0;
        }
    }

    for (unsigned char letter = 'a'; letter <= 'z'; letter++) {
        wordsWithLetter[letter] = 0;
        wordsWithoutLetter[letter] = 0;
    }

    for (unsigned int i = 0; i < numLetters; i++) {
        if (alreadyFound[i]) continue;

        for (std::string& word : validOptions) {
            letterFrequencies[i][word[i]]++;
        }
    }

    for (std::string& word : validOptions) {
        for (unsigned char letter = 'a'; letter <= 'z'; letter++) {
            if (word.find(letter) != std::string::npos && !alreadyFound[word.find(letter)])
                wordsWithLetter[letter]++;
            else
                wordsWithoutLetter[letter]++;

            for (unsigned int i = 0; i < numLetters; i++) {
                if (word.find(letter) == std::string::npos || word[i] == letter)
                    wordsWithLetterHereOrWithout[i][letter]++;
            }
        }
    }
}

// note: assumes the given word exists within the list of available words
double WordleSolver::calcEffect(const std::string word) {
    double sum = 0;
    for (unsigned int i = 0; i < numLetters; i++) {
        int numExactOccurences = letterFrequencies[i][word[i]];
        int numAnyOccurences = wordsWithLetter[word[i]];
        int numNoOccurences = wordsWithoutLetter[word[i]];
        
        if (word.find(word[i]) == i) {
            sum += ((double) numExactOccurences / validOptions.size()) * (validOptions.size() - numExactOccurences);
            sum += ((double) numAnyOccurences / validOptions.size()) * wordsWithLetterHereOrWithout[i][word[i]];
            sum += ((double) numNoOccurences / validOptions.size()) * numAnyOccurences;
        }
    }
    return sum;
}

void WordleSolver::sortBy(std::vector<std::string> &list) {
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
    