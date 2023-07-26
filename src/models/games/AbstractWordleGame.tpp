#pragma once

#include "models/games/AbstractWordleGame.hpp"

template <typename T>
AbstractWordleGame<T>::AbstractWordleGame(const std::vector<std::string> allowedWords, const IWordProvider &wordProvider, int maxGuesses) {
    this->guessesLeft = maxGuesses;
    this->allowedWords = std::unordered_set<std::string>(allowedWords.begin(), allowedWords.end());
    this->word = wordProvider.provideWord(allowedWords);
}

template <typename T>
T AbstractWordleGame<T>::makeGuess(std::string guess) {
    if (this->usedWords.find(guess) != this->usedWords.end()) {
        throw std::invalid_argument("Word already guessed.");
    }
    if (this->allowedWords.find(guess) == this->allowedWords.end()) {
        throw std::invalid_argument("Invalid word.");
    }
    this->usedWords.emplace(guess);
    return this->calculateFeedback(guess);
}

template <typename T>
std::string AbstractWordleGame<T>::getAnswer() const {
    return this->word;
}

template <typename T>
WordleGameState AbstractWordleGame<T>::getGameState() const {
    if (this->usedWords.find(this->word) != this->usedWords.end()) {
        return WordleGameState::WON;
    }
    if (this->guessesLeft == 0) {
        return WordleGameState::LOST;
    }
    return WordleGameState::ONGOING;
}
