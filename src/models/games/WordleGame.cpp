#include <string>
#include <vector>
#include "models/games/WordleGame.hpp"

std::vector<WordleFeedback> WordleGame::calculateFeedback(std::string guess) const {
    std::vector<WordleFeedback> feedback;
    for (unsigned int i = 0; i < this->word.size(); i++) {
        if (guess[i] == this->word[i]) {
            feedback.push_back(WordleFeedback::GREEN);
        } else if (this->word.find(guess[i]) != std::string::npos) {
            feedback.push_back(WordleFeedback::YELLOW);
        } else {
            feedback.push_back(WordleFeedback::BLACK);
        }
    }
    return feedback;
}

WordleGame::WordleGame(const std::vector<std::string> allowedWords, const IWordProvider& wordProvider, int maxGuesses) : AbstractWordleGame(allowedWords, wordProvider, maxGuesses) {
    for (std::string word : allowedWords) {
        if (word.size() != this->word.size()) {
            throw std::invalid_argument("All words must be the same length.");
        }
    }
}