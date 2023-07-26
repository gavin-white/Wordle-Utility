#pragma once

#include <iostream>
#include <vector>
#include <string>

template<typename T>
class AbstractGameView {
    public:
    virtual void printWelcome(int numGuesses) const = 0;
    virtual void printGuesses(std::vector<std::string> guesses, std::vector<T> feedback) const = 0;
    virtual void clear() const;
    virtual void printRecommendations(std::vector<std::pair<std::string, bool>> recommendations) const;
    virtual void printGuessesRemaining(int guessesRemaining) const;
    virtual void printWordsRemaining(int wordsEliminated, int wordsRemaining) const;
    virtual void promptCommand() const;
    virtual void printInvalidCommand(std::string reason) const;
    virtual void printInvalidGuess(std::string reason) const;
    virtual void printWin(std::string answer) const;
    virtual void printLoss(std::string answer) const;

};

#include "../../src/views/AbstractGameView.tpp"
