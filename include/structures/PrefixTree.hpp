#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "PrefixTreeNode.hpp"

/**
 * 
 */
class PrefixTree {
    private:
    PrefixTreeNode* root;

    public:
    PrefixTree(std::vector<std::string> words);
    ~PrefixTree();
    bool containsPrefix(std::string prefix);
    std::vector<std::string> getWords();
    std::vector<std::string> getWordsWithPrefix(std::string prefix);
    bool containsWord(std::string word);

    /**
     * @brief Represents the combination of a mapping of Levenshtein distances and their frequencies, and a mapping
     * of words and their Levenshtein distances. This is used in order to simultaneously calculate the Levenshtein
     * distances of all words in a list of words, and also to calculate the frequencies of each Levenshtein distance.
     */
    typedef std::pair<std::unordered_map<int, int>, std::unordered_map<std::string, int>> LevenshteinTuple;

    /**
     * @brief 
     * 
     * @param word 
     * @return LevenshteinTuple 
     */
    LevenshteinTuple levenshteinDistance(std::string word);
};
