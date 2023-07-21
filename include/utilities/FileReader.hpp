#pragma once

#include <string>
#include <vector>

/**
 * @brief A namespace that contains functions for reading words from a file.
 */
namespace FileReader {
    /**
     * @brief Reads words from a file and returns them in a vector.
     * 
     * @throws std::invalid_argument if the file could not be opened
     * @throws std::invalid_argument if the file contains words that are not the correct length
     * @param filename the name of the file
     * @param delim delimeter separating the words in the file
     * @param minLength the minimum length of words that should be accepted
     * @param maxLength the maximum length of words that should be accepted
     * @returns list of words
     */
    std::vector<std::string> readWords(std::string filename, char delim, unsigned int minLength, unsigned int maxLength);

    /**
     * @brief Reads words from a file and returns them in a vector.
     * 
     * @throws std::invalid_argument if the file could not be opened
     * @throws std::invalid_argument if the file contains words that are not the correct length
     * @param filename the name of the file
     * @param delim delimeter separating the words in the file
     * @param requiredLength the length of words that should be accepted
     * @returns list of words
     */
    std::vector<std::string> readWords(std::string filename, char delim, unsigned int requiredLength);

    /**
     * @brief Reads words from a file and returns them in a vector.
     * 
     * @throws std::invalid_argument if the file could not be opened
     * @throws std::invalid_argument if the file contains words that are not the correct length
     * @param filename the name of the file
     * @param delim delimeter separating the words in the file
     * @returns list of words
     */
    std::vector<std::string> readWords(std::string filename, char delim);
}
