#pragma once

#include <string>
#include <vector>

/**
 * Interface for a class that provides a word to be used as the answer in a Wordle game.
 */
class IWordProvider {
    public:
    /**
     * @brief Provides a word to be used as the answer in a Wordle game.
     * 
     * @param allowedWords a list of words that are allowed to be used in the game
     * @return the word to be used as the answer in a Wordle game
     */
    virtual std::string provideWord(std::vector<std::string> allowedWords) const = 0; 
};
