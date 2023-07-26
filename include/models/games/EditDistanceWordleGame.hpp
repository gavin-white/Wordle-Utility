#pragma once

#include <string>
#include <vector>
#include <map>
#include "models/IWordProvider.hpp"
#include "IWordleGame.hpp"
#include "AbstractWordleGame.hpp"

/**
 * @brief A class that encapsulates the functionality to provide a Wordle game that uses edit distance.
 */
class EditDistanceWordleGame : public AbstractWordleGame<int> {
    protected:
    /**
     * @brief Calculates the edit distance between the given guess and the answer.
     * 
     * @param guess the guess to find feedback for
     * @return int the feedback for the guess
     */
    virtual int calculateFeedback(std::string guess) const override;

    public:
    using AbstractWordleGame::AbstractWordleGame;

    /**
     * @brief Calculates the edit distance between two strings.
     * 
     * @param str1 first string
     * @param str2 second string
     * @return int edit distance
     */
    static int editDistance(const std::string& str1, const std::string& str2);
};
