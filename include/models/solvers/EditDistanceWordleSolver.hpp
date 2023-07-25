#pragma once

#include <string>
#include <vector>
#include <map>


class EditDistanceWordleSolver {
    private:
    // const int numLetters = 5;
    std::vector<std::string> availableOptions; // all words that have yet to be guessed
    // calculate the effectiveness of a potential guess
    // double calcEffect(const std::string word);

    // sort a given list of strings in descending order based on their calculated effect
    // void sortBy(std::vector<std::string> &list);

    // update the frequencies of the letters at each position
    // void updateFrequencies();
    
    public:

    EditDistanceWordleSolver();

    /* 
     * Constructs a WordleSolver object.
     */ 
    EditDistanceWordleSolver(std::vector<std::string> allowedWords);

    /*
     * Takes a guess for Wordle and the associated feedback
     * as a vector of integers, 0 for gray, 1 for yellow, 2
     * for green. 
     * 
     * If the feedback or the word is invalid, an error is thrown.
     * If no words remain after the guess, an error is thrown.
     */
    void takeGuess(std::string guess, const int feedback);

    /*
     * Produces the number of options for words remaining.
     */
    // int numOptions();

    /*
     * Produces a mapping of the first _n_ recommended guesses from best
     * to worst. The guesses are mapped onto a boolean which indicates
     * whether or not the guess is potential correct answer or not.
     * Throws an error if n exceeds the total number of possible options.
     */
    // std::vector<std::pair<std::string, bool>> getAllOptions(int n);

    /*
     * Produces a mapping of the first _n_ potentially correct guesses remaining,
     * in order of best to worst. The guesses are mapped onto a boolean which indicates
     * whether or not the guess is potential correct answer or not (all true in this case).
     * Throws an error if n exceeds the number of valid remaining words.
     */
    // std::vector<std::pair<std::string, bool>> getValidOptions(int n);
    

};
