#include <string>
#include <vector>
#include "models/BasicWordProvider.hpp"

BasicWordProvider::BasicWordProvider(std::string word) {
    this->word = word;
}

std::string BasicWordProvider::provideWord(std::vector<std::string> allowedWords) const {
    return this->word;
}