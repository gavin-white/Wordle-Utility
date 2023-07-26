#pragma once

#include <algorithm>
#include "models/games/AbstractWordleGame.hpp"

template <typename T>
int AbstractWordleGame<T>::guessesRemaining() const {
    return this->guessesLeft;
}

template <typename T>
std::vector<std::string> AbstractWordleGame<T>::getGuesses() const {
    return this->usedWords;
}

template <typename T>
std::vector<T> AbstractWordleGame<T>::getFeedback() const {
    return this->feedback;
}

template <typename T>
AbstractWordleGame<T>::AbstractWordleGame(const std::vector<std::string> allowedWords, const IWordProvider &wordProvider, int maxGuesses) {
    this->guessesLeft = maxGuesses;
    this->allowedWords = std::unordered_set<std::string>(allowedWords.begin(), allowedWords.end());
    this->word = wordProvider.provideWord(allowedWords);
}

template <typename T>
T AbstractWordleGame<T>::makeGuess(std::string guess) {
    if (std::find(this->usedWords.begin(), this->usedWords.end(), guess) != this->usedWords.end()) {
        throw std::invalid_argument("Word already guessed.");
    }
    if (this->allowedWords.find(guess) == this->allowedWords.end()) {
        throw std::invalid_argument("Invalid word.");
    }
    this->guessesLeft--;
    this->usedWords.push_back(guess);
    this->feedback.push_back(this->calculateFeedback(guess));
    return this->feedback.back();
}

template <typename T>
std::string AbstractWordleGame<T>::getAnswer() const {
    return this->word;
}

template <typename T>
WordleGameState AbstractWordleGame<T>::getGameState() const {
    if (std::find(this->usedWords.begin(), this->usedWords.end(), this->word) != this->usedWords.end()) {
        return WordleGameState::WON;
    }
    if (this->guessesLeft == 0) {
        return WordleGameState::LOST;
    }
    return WordleGameState::ONGOING;
}
