#pragma once

#include <string>
#include <map>
#include <vector>
#include <unordered_map>

/**
 * 
 */
class PrefixTreeNode {
    private:
    char letter;
    std::unordered_map<char, PrefixTreeNode*> children;
    bool wordEnd;
    PrefixTreeNode* getLastNode(std::string sequence);
    void dfs(const std::string& prefix, std::vector<std::string>& words);
    void levenshteinDfs(const std::string& word, char letter, std::vector<int>& prevRow, std::unordered_map<int, int>& distances, std::unordered_map<std::string, int>& frequencies);

    public:
    PrefixTreeNode(char letter, bool isWordEnd);
    ~PrefixTreeNode();
    static PrefixTreeNode* buildTree(std::vector<std::string> words);
    bool isPrefix(std::string prefix);
    bool containsWord(std::string word);
    std::vector<std::string> getWordsWithPrefix(std::string prefix);
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
