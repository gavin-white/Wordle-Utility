#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "IWordleSolver.hpp"
#include "../games/WordleGame.hpp"

/* Note that the words _best_ and _worst_ are used. The terms are 
used to refer to how good the particular algorithm that the implementation
of the WordleSolver uses to judge guesses believes a guess is. This may
vary between implementations */

/* Module that encapsulates the functionality to solve a Wordle game */
class WordleSolver : public IWordleSolver<std::vector<WordleFeedback>> {
    private:
    unsigned int numLetters;
    std::vector<std::string> availableOptions; // all words that have yet to be guessed
    std::vector<std::string> validOptions; // words that could be the answer based on feedback
    std::vector<std::unordered_map<char, int>> letterFrequencies; // frequencies of letters at each position
    std::vector<bool> alreadyFound; // whether each letter has been found
    std::unordered_map<char, int> wordsWithLetter; // how many words contain each letter
    std::unordered_map<char, int> wordsWithoutLetter; // how many words do not contain each letter
    std::vector<std::unordered_map<char, int>> wordsWithLetterHereOrWithout; // how many words contain each
                                                                   // letter here or not at all

    // calculate the effectiveness of a potential guess
    double calcEffect(const std::string word);

    // sort a given list of strings in descending order based on their calculated effect
    void sortBy(std::vector<std::string> &list);

    // update the frequencies of the letters at each position
    void updateFrequencies();
    
    public:

    /**
     * @brief Construct a new Wordle Solver object.
     * 
     * @throws std::invalid_argument if any of the words in allowedWords are not of equal length
     * @throws std::invalid_argument if the list of allowed words is empty
     * @param allowedWords words for this wordle game (must be of equal length)
     */
    WordleSolver(std::vector<std::string> allowedWords);

    /*
     * Takes a guess for Wordle and the associated feedback
     * as a vector of integers, 0 for gray, 1 for yellow, 2
     * for green. 
     * 
     * If the feedback or the word is invalid, an error is thrown.
     * If no words remain after the guess, an error is thrown.
     */
    void takeGuess(std::string guess, const std::vector<WordleFeedback> feedback) override;

    /*
     * Produces the number of options for words remaining.
     */
    int numOptions() const override;

    /*
     * Produces a mapping of the first _n_ recommended guesses from best
     * to worst. The guesses are mapped onto a boolean which indicates
     * whether or not the guess is potential correct answer or not.
     * Throws an error if n exceeds the total number of possible options.
     */
    std::vector<std::pair<std::string, bool>> recommendGuesses(unsigned int n) override;

    /**
     * @brief Produces a mapping of the first _num_ guesses that match the given template.
     * 
     * @param temp the template
     * @param num the number of guesses to produce
     * @return std::vector<std::pair<std::string, bool>> the guesses mapped to whether or not 
     * they are potential correct answers
     */
    std::vector<std::pair<std::string, bool>> matchGuesses(std::string temp, unsigned int num) override;

};
