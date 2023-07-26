#include <iostream>
#include "views/WordleGameView.hpp"

std::string WordleGameView::feedbackToColor(WordleFeedback feedback, char c) const {
    switch (feedback) {
        case WordleFeedback::BLACK:
            return TextModifiers::backgroundBlack + c + TextModifiers::reset;
        case WordleFeedback::YELLOW:
            return TextModifiers::backgroundYellow + c + TextModifiers::reset;
        case WordleFeedback::GREEN:
            return TextModifiers::backgroundGreen + c + TextModifiers::reset;
        default:
            return "";
    }
}

void WordleGameView::printWelcome(int numGuesses) const {
    std::cout << TextModifiers::backgroundBlue << "--------------------------------------------------";
    std::cout << TextModifiers::reset << "\nWelcome to the game of Wordle!\n";
    std::cout << "You have " << numGuesses << " attempts to guess the secret word.\n";
    std::cout << TextModifiers::backgroundBlue << "--------------------------------------------------" << TextModifiers::reset << "\n";
}

void WordleGameView::printGuesses(std::vector<std::string> guesses, std::vector<std::vector<WordleFeedback>> feedback) const {
    std::cout << "Your guesses so far:\n";
    for (unsigned int i = 0; i < guesses.size(); i++) {
        for (unsigned int j = 0; j < guesses[i].size(); j++) {
            std::cout << feedbackToColor(feedback[i][j], guesses[i][j]);
        }
        std::cout << "\n";
    }
}