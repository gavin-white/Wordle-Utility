#pragma once

#include <string>
#include <vector>
#include <map>

/* Note that the words _best_ and _worst_ are used. The terms are 
used to refer to how good the particular algorithm that the implementation
of the WordleSolver uses to judge guesses believes a guess is. This may
vary between implementations */

/* Module that encapsulates the functionality to solve a Wordle game */
class WordleSolver {
    private:
    unsigned int numLetters = 5;
    std::vector<std::string> availableOptions; // all words that have yet to be guessed
    std::vector<std::string> validOptions; // words that could be the answer based on feedback
    std::vector<std::map<char, int>> letterFrequencies; // frequencies of letters at each position
    std::vector<bool> alreadyFound; // whether each letter has been found
    std::map<char, int> wordsWithLetter; // how many words contain each letter
    std::map<char, int> wordsWithoutLetter; // how many words do not contain each letter
    std::vector<std::map<char, int>> wordsWithLetterHereOrWithout; // how many words contain each
                                                                   // letter here or not at all

    // calculate the effectiveness of a potential guess
    double calcEffect(const std::string word);

    // sort a given list of strings in descending order based on their calculated effect
    void sortBy(std::vector<std::string> &list);

    // update the frequencies of the letters at each position
    void updateFrequencies();
    
    public:

    /* 
     * Constructs a WordleSolver object.
     */ 
    WordleSolver();

    /*
     * Initializes the Wordle solver, loading in the wordlist
     * from _filename_. 
     * Throws an error if the file cannot be opened or if it 
     * does not contain only 1+ 5 letter words on seperate lines.
     */
    void init(const std::string filename);

    /*
     * Takes a guess for Wordle and the associated feedback
     * as a vector of integers, 0 for gray, 1 for yellow, 2
     * for green. 
     * 
     * If the feedback or the word is invalid, an error is thrown.
     * If no words remain after the guess, an error is thrown.
     */
    void takeGuess(std::string guess, const std::vector<int> feedback);

    /*
     * Produces the number of options for words remaining.
     */
    int numOptions();

    /*
     * Produces a mapping of the first _n_ recommended guesses from best
     * to worst. The guesses are mapped onto a boolean which indicates
     * whether or not the guess is potential correct answer or not.
     * Throws an error if n exceeds the total number of possible options.
     */
    std::vector<std::pair<std::string, bool>> getAllOptions(unsigned int n);

    /*
     * Produces a mapping of the first _n_ potentially correct guesses remaining,
     * in order of best to worst. The guesses are mapped onto a boolean which indicates
     * whether or not the guess is potential correct answer or not (all true in this case).
     * Throws an error if n exceeds the number of valid remaining words.
     */
    std::vector<std::pair<std::string, bool>> getValidOptions(unsigned int n);
    

};
