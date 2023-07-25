#include <string>
#include <vector>
#include "models/games/EditDistanceWordleGame.hpp"

int EditDistanceWordleGame::editDistance(const std::string& str1, const std::string& str2) {
    char** matrix = new char*[str1.size() + 1];
    for(unsigned int i = 0; i < str1.size() + 1; i++) {
        matrix[i] = new char[str2.size() + 1];
    }   

    for(unsigned int i = 0; i <= str1.size(); i++) {
        matrix[i][0] = i;
    }
    for(unsigned int i = 0; i <= str2.size(); i++) {
        matrix[0][i] = i;
    }
    for(unsigned int i = 1; i <= str1.size(); i++) {
        for(unsigned int j = 1; j <= str2.size(); j++) {
            if(str1[i - 1] == str2[j - 1])
                matrix[i][j] = matrix[i - 1][j - 1];
            else
                matrix[i][j] = std::min(std::min(matrix[i - 1][j - 1], matrix[i - 1][j]), matrix[i][j - 1]) + 1;
        }
    }

    for (unsigned int i = 0; i <= str1.size(); i++) {
        delete[] matrix[i];
    }
    delete[] matrix;
    
    return matrix[str1.size()][str2.size()];
}

int EditDistanceWordleGame::calculateFeedback(std::string guess) const {
    return this->editDistance(this->word, guess);
}