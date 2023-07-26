#pragma once

#include <string>
#include <vector>

template<typename T>
class IWordleSolver {
    public:
    virtual int numOptions() const = 0;
    virtual std::vector<std::pair<std::string, bool>> recommendGuesses(unsigned int num) = 0;
    virtual std::vector<std::pair<std::string, bool>> matchGuesses(std::string temp, unsigned int num) = 0;
    virtual void takeGuess(std::string guess, T feedback) = 0;
};
