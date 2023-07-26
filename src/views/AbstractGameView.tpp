#pragma once

#include <iostream>
#include "views/AbstractGameView.hpp"
#include "views/TextModifiers.hpp"

template<typename T>
void AbstractGameView<T>::printRecommendations(std::vector<std::pair<std::string, bool>> recommendations) const {
    std::cout << "Recommendations:\n";
    for (unsigned int i = 0; i < recommendations.size(); i++) {
        std::cout << TextModifiers::bold << recommendations[i].first << TextModifiers::reset;
        if (recommendations[i].second) {
            std::cout << " (valid answer)";
        } else {
            std::cout << " (invalid answer)";
        }
        std::cout << "\n";
    }
}

template<typename T>
void AbstractGameView<T>::clear() const {
    std::cout << "\n\n\n\n\n\n\n\n\n\n\n\n";
}

template<typename T>
void AbstractGameView<T>::printGuessesRemaining(int guessesRemaining) const {
    std::cout << "You have " << guessesRemaining << " guesses remaining.\n";
}

template<typename T>
void AbstractGameView<T>::printWordsRemaining(int wordsEliminated, int wordsRemaining) const {
    std::cout << "There are " << TextModifiers::bold << wordsRemaining << TextModifiers::reset << " possible words remaining. ";
    std::cout << "You have eliminated " << wordsEliminated << " words.\n";
}

template<typename T>
void AbstractGameView<T>::promptCommand() const {
    std::cout << TextModifiers::backgroundBlack << TextModifiers::white << "Enter a command | ";
    std::cout << "guess [word] | recommend [num] | ";
    std::cout << "match [template] [num] | quit" << TextModifiers::reset << "\n";
}

template<typename T>
void AbstractGameView<T>::printInvalidCommand(std::string reason) const {
    std::cout << TextModifiers::red << "Command failed - " << reason << " - Please try again\n";
    std::cout << TextModifiers::reset;
}

template<typename T>
void AbstractGameView<T>::printInvalidGuess(std::string reason) const {
    std::cout << TextModifiers::red << "Invalid guess - " << reason << " - Please guess again\n";
    std::cout << TextModifiers::reset;
}

template<typename T>
void AbstractGameView<T>::printWin(std::string answer) const {
    std::cout << TextModifiers::bold << "You win! The answer was " << answer << "\n";
    std::cout << TextModifiers::reset;
}

template<typename T>
void AbstractGameView<T>::printLoss(std::string answer) const {
    std::cout << TextModifiers::bold << "Game over. The answer was " << answer << "\n";
    std::cout << TextModifiers::reset;
}
