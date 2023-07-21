#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <exception>
#include <iostream>
#include <string>
#include "models/EditDistanceWordle.hpp"

int EditDistanceWordle::editDistance(std::string str1, std::string str2) {
    char** array = new char*[str1.size() + 1];
    for(unsigned int i = 0; i < str1.size() + 1; i++)
        array[i] = new char[str2.size() + 1];

    for(unsigned int i = 0; i <= str1.size(); i++)
        array[i][0] = i;
    for(unsigned int i = 0; i <= str2.size(); i++)
        array[0][i] = i;
    for(unsigned int i = 1; i <= str1.size(); i++)
        for(unsigned int j = 1; j <= str2.size(); j++)
            if(str1[i - 1] == str2[j - 1])
                array[i][j] = array[i - 1][j - 1];
            else
                array[i][j] = std::min(std::min(array[i - 1][j - 1], array[i - 1][j]), array[i][j - 1]) + 1;
    
    int result = array[str1.size()][str2.size()];

    for(unsigned int i = 0; i < str1.size() + 1; i++)
        delete [] array[i];
    delete [] array;

    return result;
}

EditDistanceWordle::EditDistanceWordle(const std::vector<std::string> allowedWords, const IWordProvider &wordProvider) {
    this->allowedWords = allowedWords;
    this->word = wordProvider.provideWord(allowedWords);
}

int EditDistanceWordle::guess(std::string guess) {
    this->usedWords.push_back(guess);
    return editDistance(guess, this->word);
}
    