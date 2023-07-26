#include <iostream>
#include "views/EditDistanceWordleGameView.hpp"

void EditDistanceWordleGameView::printWelcome(int numGuesses) const {
    std::cout << TextModifiers::backgroundBlue << "--------------------------------------------------";
    std::cout << TextModifiers::reset << "\nWelcome to the game of Edit Distance Wordle!\n";
    std::cout << "You have " << numGuesses << " attempts to guess the secret word.\n";
    std::cout << TextModifiers::backgroundBlue << "--------------------------------------------------" << TextModifiers::reset << "\n";
}

void EditDistanceWordleGameView::printGuesses(std::vector<std::string> guesses, std::vector<int> feedback) const {
    std::cout << "Your guesses so far:\n";
    for (unsigned int i = 0; i < guesses.size(); i++) {
        std::cout << TextModifiers::bold << guesses[i] << TextModifiers::reset;
        std::cout << " Edit distance from answer: " << feedback[i] << "\n";
    }
}