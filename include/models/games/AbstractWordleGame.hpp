#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include "IWordProvider.hpp"
#include "IWordleGame.hpp"

/**
 * @brief An abstract class that provides generalized implementations for a Wordle-style word guessing game.
 * 
 * @tparam T the type of feedback that the game should provide
 */
template <typename T>
class AbstractWordleGame : public IWordleGame<T> {
    protected:
    const std::string word; // the answer to this wordle game
    std::unordered_set<std::string> allowedWords; // all valid words for this game
    std::unordered_set<std::string> usedWords; // words that have been guessed
    int guessesLeft;

    /**
     * @brief Calculates the feedback for a given guess based on the answer.
     * 
     * @param guess the guess to find feedback for
     * @return T the feedback for the guess
     */
    virtual T calculateFeedback(std::string guess) const = 0;

    public:
    /**
     * @brief 
     * 
     * @param allowedWords 
     * @param wordProvider 
     */
    virtual AbstractWordleGame(const std::vector<std::string> allowedWords, const IWordProvider& wordProvider, int maxGuesses);

    /**
     * @brief Provides a guess for the game and returns the edit distance between the guess and the answer.
     * 
     * @param guess the guess
     * @return int the edit distance between the guess and the answer
     */
    virtual T makeGuess(std::string guess) override;

    /**
     * @brief Get the answer to the game.
     * 
     * @return std::string the answer
     */
    virtual std::string getAnswer() const override;

    /**
     * @brief Get the state of the game
     * 
     * @return WordleGameState 
     */
    virtual WordleGameState getGameState() const override;

};
