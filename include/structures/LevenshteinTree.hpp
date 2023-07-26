#pragma once

#include "PrefixTree.hpp"

/**
 * @brief A Prefix Tree that can calculate the Levenshtein distance of a word to all words in the tree.
 */
class LevenshteinTree {
    private:
    PrefixTree* delegate;

    /**
     * @brief Construct a new Levenshtein Tree.
     * 
     * @param delegate the PrefixTree that this LevenshteinTree should delegate to.
     */
    LevenshteinTree(PrefixTree* delegate);

    /**
     * @brief Performs a depth-first search on the tree, calculating the Levenshtein distance of each word in the tree.
     * 
     * @param node the current node in the traversal
     * @param word the word to calculate the Levenshtein distance to
     * @param letter the letter of the current node
     * @param prevRow the previous row of the levenshtein distance calculation
     * @param frequencies the frequency of each Levenshtein distance to update
     * @param distances the Levenshtein distance of each word to update
     */
    static void levenshteinDfs(PrefixTreeNode* node, const std::string& word, char letter, std::vector<int>& prevRow,
     std::unordered_map<int, int>& frequencies, std::unordered_map<std::string, int>& distances);

    public:
    /**
     * @brief Destroy the LevenshteinTree Tree object.
     */
    ~LevenshteinTree();

    /**
     * @brief Constructs a PrefixTree from a list of words.
     * 
     * @param words the words to add to the tree
     * @return PrefixTreeNode* a pointer to the tree
     */
    static LevenshteinTree* buildTree(std::vector<std::string> words);

    /**
     * @brief Represents the combination of a mapping of Levenshtein distances and their frequencies, and a mapping
     * of words and their Levenshtein distances. This is used in order to simultaneously calculate the Levenshtein
     * distances of all words in a list of words, and also to calculate the frequencies of each Levenshtein distance.
     */
    typedef std::pair<std::unordered_map<int, int>, std::unordered_map<std::string, int>> LevenshteinTuple;

    /**
     * @brief Calculates the Levenshtein distance of a word to all words in the tree.
     * 
     * @param word the word to calculate the Levenshtein distance to
     * @return LevenshteinTuple containing a mapping from every word to its Levenshtein distance to the given word,
     * and a mapping from every Levenshtein distance to its frequency.
     */
    LevenshteinTuple levenshteinDistance(std::string word);
};
