#pragma once

#include "PrefixTree.hpp"

/**
 * @brief A tree structure that can be used to efficiently find words that contain a given suffix.
 * This is simply a wrapper around a PrefixTree, inserting and searching for prefixes backwards.
 */
class SuffixTree {
    private:
    PrefixTree* delegate;

    /**
     * @brief Construct a new Suffix Tree.
     * 
     * @param delegate the PrefixTree that this SuffixTree should delegate to.
     */
    SuffixTree(PrefixTree* delegate);

    public:
    /**
     * @brief Destroy the Suffix Tree object.
     */
    ~SuffixTree();

    /**
     * @brief Builds a SuffixTree from a list of words.
     * 
     * @param words the words to store in the tree
     * @return SuffixTree* a pointer to the tree
     */
    static SuffixTree* buildTree(std::vector<std::string> words);

    /**
     * @brief Checks if a given suffix is contained in the tree.
     * 
     * @param suffix the suffix to check
     * @return true if the suffix is contained in the tree
     * @return false if not
     */
    bool isSuffix(std::string suffix);

    /**
     * @brief Checks if a given word is contained in the tree.
     * 
     * @param word a word to check for
     * @return true if the word is present
     * @return false if not
     */
    bool containsWord(std::string word);

    /**
     * @brief Produces a list of all words in the tree that end with a given suffix.
     * 
     * @param suffix the suffix
     * @return std::vector<std::string> the list of all words with the given suffix
     */
    std::vector<std::string> getWordsWithSuffix(std::string suffix);
};
