#pragma once

#include <string>
#include <vector>
#include <map>
#include "IWordProvider.hpp"

/**
 * @brief A class that encapsulates the functionality to provide a Wordle game that uses edit distance.
 */
class EditDistanceWordle {
    private:
    std::string word; // the answer to this wordle game
    std::vector<std::string> allowedWords; // all words that have yet to be guessed
    std::vector<std::string> usedWords; // words that have been guessed

    public:
    /**
     * @brief Calculates the edit distance between two strings.
     * 
     * @param str1 first string
     * @param str2 second string
     * @return int edit distance
     */
    static int editDistance(std::string& str1, std::string& str2);
    
    /**
     * @brief You can construct an EditDistanceWordle object with a list of allowed words and a word provider.
     * 
     * @param allowedWords 
     * @param wordProvider 
     */
    EditDistanceWordle(const std::vector<std::string> allowedWords, const IWordProvider& wordProvider);

    /**
     * @brief Provides a guess for the game and returns the edit distance between the guess and the answer.
     * 
     * @param guess the guess
     * @return int the edit distance between the guess and the answer
     */
    int guess(std::string guess);

};
