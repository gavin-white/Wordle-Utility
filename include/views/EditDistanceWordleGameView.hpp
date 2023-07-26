#pragma once

#include "AbstractGameView.hpp"

class EditDistanceWordleGameView : public AbstractGameView<int> {
    public:
    void printWelcome(int numGuesses) const override;
    void printGuesses(std::vector<std::string> guesses, std::vector<int> feedback) const override;
};
