#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "IWordleSolver.hpp"
#include "structures/LevenshteinTree.hpp"

class EditDistanceWordleSolver : public IWordleSolver<int> {
    private:
    std::vector<std::string> availableOptions; // all words that have yet to be guessed
    std::vector<std::string> validOptions; // words that could be the answer based on feedback
    std::unordered_map<std::string, LevenshteinTree::LevenshteinTuple> levenshteinTuples; // tuples of words edit distances

    // calculate the effectiveness of a potential guess
    double calcEffect(const std::string word);

    // sort a given list of strings in descending order based on their calculated effect
    void sortBy(std::vector<std::string> &list);

    
    public:
    EditDistanceWordleSolver(std::vector<std::string> allowedWords);

    int numOptions() const;

    std::vector<std::pair<std::string, bool>> recommendGuesses(unsigned int num);

    std::vector<std::pair<std::string, bool>> matchGuesses(std::string temp, unsigned int num);

    void takeGuess(std::string guess, int feedback);

};
