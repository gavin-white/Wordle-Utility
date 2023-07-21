#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <limits>
#include "utilities/FileReader.hpp"

std::vector<std::string> FileReader::readWords(std::string filename, char delim, unsigned int requiredLength) {
    return FileReader::readWords(filename, delim, requiredLength, requiredLength);
}

std::vector<std::string> FileReader::readWords(std::string filename, char delim) {
    return FileReader::readWords(filename, delim, 0, std::numeric_limits<unsigned int>::max());
}

std::vector<std::string> FileReader::readWords(std::string filename, char delim, unsigned int minLength, unsigned int maxLength) {
    std::ifstream stream = std::ifstream(filename);
    std::vector<std::string> words;
    if (!stream.good()) {
        throw std::invalid_argument("File could not be opened.");
    }

    std::string nextWord;
    while (getline(stream, nextWord)) {
        if (nextWord.size() >= minLength && nextWord.size() <= maxLength) {
            std::transform(nextWord.begin(), nextWord.end(), nextWord.begin(),
                [](unsigned char c){ return std::tolower(c); }); // map to lower on each letter
                                                                 // to make string lowercase
            words.push_back(nextWord);
        } else {
            throw std::invalid_argument("File contains words outside of the specified length range.");
        }
    }

    return words;
}