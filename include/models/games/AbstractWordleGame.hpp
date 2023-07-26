#pragma once

#include <string>
#include <vector>
#include <map>
#include <unordered_set>
#include "models/IWordProvider.hpp"
#include "IWordleGame.hpp"

/**
 * @brief An abstract class that provides generalized implementations for a Wordle-style word guessing game.
 * 
 * @tparam T the type of feedback that the game should provide
 */
template <typename T>
class AbstractWordleGame : public IWordleGame<T> {
    protected:
    std::string word; // the answer to this wordle game
    std::unordered_set<std::string> allowedWords; // all valid words for this game
    std::vector<std::string> usedWords; // words that have been guessed
    std::vector<T> feedback; // feedback for each guess
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
     * @brief Constructs a new Wordle game with the given allowed words, max guesses, and using 
     * the given word provider to generate the answer.
     * 
     * @param allowedWords the list of allowed words
     * @param wordProvider the word provider to use to generate the answer
     * @param maxGuesses the maximum number of guesses allowed
     */
    AbstractWordleGame(const std::vector<std::string> allowedWords, const IWordProvider& wordProvider, int maxGuesses);

    virtual int guessesRemaining() const override;

    virtual std::vector<std::string> getGuesses() const override;

    virtual std::vector<T> getFeedback() const override;

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

#include "../../../src/models/games/AbstractWordleGame.tpp"
