#include <vector>
#include <string>

#include "structures/PrefixTree.hpp"
#include "structures/PrefixTreeNode.hpp"


PrefixTree::~PrefixTree() {
    delete this->root;
}

PrefixTree::PrefixTree(std::vector<std::string> words) {
    this->root = PrefixTreeNode::buildTree(words);
}

bool PrefixTree::containsPrefix(std::string prefix) {
    return this->root->containsWord(prefix);
}

std::vector<std::string> PrefixTree::getWords() {
    return this->root->getWordsWithPrefix("");
}

std::vector<std::string> PrefixTree::getWordsWithPrefix(std::string prefix) {
    return this->root->getWordsWithPrefix(prefix);
}

bool PrefixTree::containsWord(std::string word) {
    return this->root->containsWord(word);
}

PrefixTree::LevenshteinTuple PrefixTree::levenshteinDistance(std::string word) {
    return this->root->levenshteinDistance(word);
}
