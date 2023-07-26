#include <string>
#include <vector>
#include <ctime>
#include "models/RandomWordProvider.hpp"

RandomWordProvider::RandomWordProvider(std::vector<std::string> wordsToChooseFrom) {
    this->wordsToChoseFrom = wordsToChooseFrom;
}

std::string RandomWordProvider::provideWord(std::vector<std::string> allowedWords) const {
    std::srand(std::time(0));
    return wordsToChoseFrom[std::rand() % wordsToChoseFrom.size()];
}