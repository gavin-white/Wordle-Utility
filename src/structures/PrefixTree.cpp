#include <vector>
#include <string>
#include "structures/PrefixTree.hpp"

PrefixTreeNode::PrefixTreeNode(std::string wordEnd) {
    this->wordEnd = wordEnd;
}

PrefixTreeNode::~PrefixTreeNode() {
    for (auto& child : this->children) {
        delete child.second;
    }
}

PrefixTreeNode* PrefixTreeNode::buildTree(std::vector<std::string> words) {
    PrefixTreeNode* root = new PrefixTreeNode("");

    for (std::string& word : words) {
        PrefixTreeNode* parent = root;
        for (char letter : word) {
            if (parent->children.find(letter) == parent->children.end()) {
                parent->children[letter] = new PrefixTreeNode("");
            }
            parent = parent->children[letter];
        }
        parent->wordEnd = word;
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
    return this->getLastNode(word) && this->getLastNode(word)->wordEnd != "";
}

void PrefixTreeNode::dfs(std::vector<std::string>& words) {
    if (this->wordEnd != "") {
        words.push_back(this->wordEnd);
    }
    for (auto &child : this->children) {
        child.second->dfs(words);
    }
}

std::vector<std::string> PrefixTreeNode::getWordsWithPrefix(std::string prefix) {
    std::vector<std::string> words;
    PrefixTreeNode* prefixEnd = getLastNode(prefix);
    if (prefixEnd) {
        prefixEnd->dfs(prefix, words);
    }
    return words;
}
