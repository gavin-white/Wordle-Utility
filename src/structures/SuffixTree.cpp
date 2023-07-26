#include <algorithm>
#include "structures/SuffixTree.hpp"
#include "structures/PrefixTree.hpp"

SuffixTree::SuffixTree(PrefixTree* delegate) {
    this->delegate = delegate;
}

SuffixTree::~SuffixTree() {
    delete delegate;
}

SuffixTree* SuffixTree::buildTree(std::vector<std::string> words) {
    std::vector<std::string> reversedWords;
    for (std::string word : words) {
        std::reverse(word.begin(), word.end());
        reversedWords.push_back(word);
    }
    PrefixTree* delegate = PrefixTree::buildTree(reversedWords);
}

bool SuffixTree::isSuffix(std::string suffix) {
    std::reverse(suffix.begin(), suffix.end());
    return delegate->isPrefix(suffix);
}

bool SuffixTree::containsWord(std::string word) {
    std::reverse(word.begin(), word.end());
    return delegate->containsWord(word);
}

std::vector<std::string> SuffixTree::getWordsWithSuffix(std::string suffix) {
    std::reverse(suffix.begin(), suffix.end());
    std::vector<std::string> words = delegate->getWordsWithPrefix(suffix);
    for (std::string& word : words) {
        std::reverse(word.begin(), word.end());
    }
    return words;
}