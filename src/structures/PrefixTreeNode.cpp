#include <vector>
#include <string>
#include "structures/PrefixTreeNode.hpp"

PrefixTreeNode::PrefixTreeNode(char letter, bool isWordEnd) {
    this->letter = letter;
    this->wordEnd = isWordEnd;
}

PrefixTreeNode::~PrefixTreeNode() {
    for (auto& child : this->children) {
        delete child.second;
    }
}

PrefixTreeNode* PrefixTreeNode::buildTree(std::vector<std::string> words) {
    PrefixTreeNode* root = new PrefixTreeNode('\0', false);

    for (std::string& word : words) {
        PrefixTreeNode* parent = root;
        for (char letter : word) {
            if (parent->children.find(letter) == parent->children.end()) {
                parent->children[letter] = new PrefixTreeNode(letter, false);
            }
            parent = parent->children[letter];
        }
        parent->wordEnd = true;
    }

    return root;
}

PrefixTreeNode* PrefixTreeNode::getLastNode(std::string sequence) {
    if (sequence.size() == 0)
        return this;

    if (this->children.find(sequence[0]) == this->children.end())
        return nullptr;
    else
        return this->children[sequence[0]]->getLastNode(sequence.substr(1));
}

bool PrefixTreeNode::isPrefix(std::string prefix) {
    return this->getLastNode(prefix);
}

bool PrefixTreeNode::containsWord(std::string word) {
    return this->getLastNode(word) && this->getLastNode(word)->wordEnd;
}

void PrefixTreeNode::dfs(const std::string& prefix, std::vector<std::string>& words) {
    if (this->wordEnd) {
        words.push_back(prefix);
    }
    for (auto &child : this->children) {
        child.second->dfs(prefix + child.first, words);
    }
}

void PrefixTreeNode::levenshteinDfs(const std::string& word, char letter, std::vector<int>& prevRow, std::unordered_map<int, int>& frequencies, std::unordered_map<std::string, int>& distances) {
    std::vector<int> currRow(word.size() + 1);
    currRow[0] = prevRow[0] + 1;
    for (unsigned int i = 1; i < word.size() + 1; i++) {
        int insertCost = currRow[i - 1] + 1;
        int deleteCost = prevRow[i] + 1;
        int replaceCost = prevRow[i - 1] + (word[i - 1] == letter ? 0 : 1);
        currRow[i] = std::min(std::min(insertCost, deleteCost), replaceCost);
    }

    if (this->wordEnd) {
        int levenshteinDistance = currRow.back();
        frequencies[levenshteinDistance]++;
        distances[word] = levenshteinDistance;
    }

    for (auto &child : this->children) {
        child.second->levenshteinDfs(word, child.first, currRow, frequencies, distances);
    }
}

PrefixTreeNode::LevenshteinTuple PrefixTreeNode::levenshteinDistance(std::string word) {
    std::unordered_map<int, int> distances;
    std::unordered_map<std::string, int> frequencies;
    std::vector<int> firstRow(word.size() + 1);

    for (unsigned int i = 0; i < word.size() + 1; i++) {
        firstRow[i] = i;
    }

    for (auto& child : this->children) {
        child.second->levenshteinDfs(word, child.first, firstRow, distances, frequencies);
    }

    return LevenshteinTuple(distances, frequencies);
}

std::vector<std::string> PrefixTreeNode::getWordsWithPrefix(std::string prefix) {
    std::vector<std::string> words;
    PrefixTreeNode* prefixEnd = getLastNode(prefix);
    if (prefixEnd) {
        prefixEnd->dfs(prefix, words);
    }
    return words;
}
