#pragma once

#include <string>
#include <vector>

/**
 * @brief Represents the state of a Wordle game. Either won, lost, or ongoing.
 */
enum WordleGameState {
    WON,
    LOST,
    ONGOING
};

/**
 * @brief Interface for a class that hosts a Wordle-style word guessing game.
 * 
 * @tparam T The type used to provide feedback for the game.
 */
template <typename T>
class IWordleGame {
    public:
    
    /**
     * @brief Makes a guess for the game and returns feedback.
     * 
     * @param guess the word to guess
     * @return T feedback about the guess
     */
    virtual T makeGuess(std::string guess) = 0;

    /**
     * @brief Get the answer to the game.
     * 
     * @return std::string the answer
     */
    virtual std::string getAnswer() const = 0;

    /**
     * @brief Determine the state of the game. Either won, lost, or ongoing.
     * 
     * @return WordleGameState the state of the game
     */
    virtual WordleGameState getGameState() const = 0;
};
