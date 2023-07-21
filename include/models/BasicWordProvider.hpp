#pragma once

#include <string>
#include <vector>
#include "IWordProvider.hpp"

/**
 * Class that directly provides a specified word to be used as the answer in a Wordle game.
 */
class BasicWordProvider : public IWordProvider {
    private:
    std::string word;

    public:
    /**
     * @brief Construct a new Basic Word Provider object
     * 
     * @param word the word this provider should provide
     */
    BasicWordProvider(std::string word);

    /**
     * @brief Provides a word to be used as the answer in a Wordle game.
     * 
     * @param allowedWords a list of words that are allowed to be used in the game
     * @return the word to be used as the answer in a Wordle game
     */
    std::string provideWord(std::vector<std::string> allowedWords) const override; 
};
