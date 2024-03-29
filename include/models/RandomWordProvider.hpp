#pragma once

#include <string>
#include <vector>
#include "IWordProvider.hpp"

/**
 * Class that directly provides a specified word to be used as the answer in a Wordle game.
 */
class RandomWordProvider : public IWordProvider {
    private:
    std::vector<std::string> wordsToChoseFrom;

    public:
    /**
     * @brief Construct a new Basic Word Provider object
     * 
     * @param word the word this provider should provide
     */
    RandomWordProvider(std::vector<std::string> wordsToChoseFrom);

    /**
     * @brief Provides a word to be used as the answer in a Wordle game.
     * 
     * @param allowedWords a list of words that are allowed to be used in the game
     * @return the word to be used as the answer in a Wordle game
     */
    std::string provideWord(std::vector<std::string> allowedWords) const override; 
};
