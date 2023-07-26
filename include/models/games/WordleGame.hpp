#pragma once

#include <string>
#include <vector>
#include <map>
#include "models/IWordProvider.hpp"
#include "IWordleGame.hpp"
#include "AbstractWordleGame.hpp"

/**
 * @brief Wordle feedback values. Black represents a letter that is not in the answer, yellow
 * represents a letter that is in the answer but in the wrong position, and green represents
 * a letter that is in the answer and in the correct position.
 */
enum WordleFeedback {
    BLACK,
    YELLOW,
    GREEN
};

/**
 * @brief A class that encapsulates the functionality to provide a Wordle game that uses edit distance.
 */
class WordleGame : public AbstractWordleGame<std::vector<WordleFeedback>> {
    protected:
    /**
     * @brief Calculates the feedback for each letter of a given guess.
     * 
     * @param guess the guess
     * @return std::vector<WordleFeedback> the feedback for each letter of the guess
     */
    std::vector<WordleFeedback> calculateFeedback(std::string guess) const override;

    public:
    /**
     * @brief 
     * 
     * @param allowedWords 
     * @param wordProvider 
     */
    WordleGame(const std::vector<std::string> allowedWords, const IWordProvider& wordProvider, int maxGuesses);
};
