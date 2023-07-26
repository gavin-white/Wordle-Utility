#pragma once

#include "AbstractGameView.hpp"
#include "../models/games/WordleGame.hpp"

class WordleGameView : public AbstractGameView<std::vector<WordleFeedback>> {
    private:
    std::string feedbackToColor(WordleFeedback feedback, char c) const;

    public:
    void printWelcome(int numGuesses) const override;
    void printGuesses(std::vector<std::string> guesses, std::vector<std::vector<WordleFeedback>> feedback) const override;
};
