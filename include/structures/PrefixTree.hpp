#pragma once

#include <string>
#include <map>
#include <vector>
#include <unordered_map>

/**
 * @brief A tree structure that can be used to efficiently find words that contain a given suffix.
 */
class PrefixTreeNode {
    protected:
    std::unordered_map<char, PrefixTreeNode*> children;
    std::string wordEnd;

    /**
     * @brief Construct a new Prefix Tree Node object
     * 
     * @param wordEnd the word that ends at this node or "" if no word ends at this node
     */
    PrefixTreeNode(std::string wordEnd);

    /**
     * @brief Retrievs the node in the tree that corresponds with the final letter in the given sequence.
     * 
     * @param sequence a sequence to search for
     * @return PrefixTreeNode* the node
     */
    PrefixTreeNode* getLastNode(std::string sequence);

    /**
     * @brief Performs a depth-first search on the tree, adding all words that end at this node to the given vector.
     * 
     * @param words the vector to add words to
     */
    void dfs(std::vector<std::string>& words);

    public:
    /**
     * @brief Destroy the Prefix Tree Node object.
     */
    ~PrefixTreeNode();

    /**
     * @brief Constructs a PrefixTree from a list of words.
     * 
     * @param words the words to add to the tree
     * @return PrefixTreeNode* a pointer to the tree
     */
    static PrefixTreeNode* buildTree(std::vector<std::string> words);

    /**
     * @brief Determines if the given prefix is contained in the tree.
     * 
     * @param prefix the prefix to check
     * @return true if the prefix is present in the tree
     * @return false if not
     */
    bool isPrefix(std::string prefix);

    /**
     * @brief Determines if the given word is contained in the tree.
     * 
     * @param word the word to check
     * @return true if the word is present in the tree
     * @return false if not
     */
    bool containsWord(std::string word);

    /**
     * @brief Produces a list of all words in the tree that begin with a given prefix.
     * 
     * @param prefix the prefix
     * @return std::vector<std::string> a list of all words with the given prefix
     */
    std::vector<std::string> getWordsWithPrefix(std::string prefix);

    // LevenshteinTree needs to access the private members of PrefixTreeNode
    friend class LevenshteinTree;
};

/**
 * @brief The public interface of PrefixTreeNode assumes that the client
 * is interacting with the root. As such, we can refer to PrefixTreeNode
 * as simply a PrefixTree.
 */
typedef PrefixTreeNode PrefixTree;
