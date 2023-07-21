#include <string>
#include <vector>
#include "models/RandomWordProvider.hpp"

RandomWordProvider::RandomWordProvider() {}

std::string RandomWordProvider::provideWord(std::vector<std::string> allowedWords) const {
    return allowedWords[rand() % allowedWords.size()];
}