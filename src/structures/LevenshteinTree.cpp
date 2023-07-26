#include <LevenshteinTree.hpp>

void LevenshteinTree::levenshteinDfs(PrefixTreeNode* node, const std::string& word, char letter, std::vector<int>& prevRow, std::unordered_map<int, int>& distances, std::unordered_map<std::string, int>& frequencies) {
    std::vector<int> currRow(word.size() + 1);
    currRow[0] = prevRow[0] + 1;
    for (unsigned int i = 1; i < word.size() + 1; i++) {
        int insertCost = currRow[i - 1] + 1;
        int deleteCost = prevRow[i] + 1;
        int replaceCost = prevRow[i - 1] + (word[i - 1] == letter ? 0 : 1);
        currRow[i] = std::min(std::min(insertCost, deleteCost), replaceCost);
    }

    if (node->wordEnd != "") {
        int levenshteinDistance = currRow.back();
        distances[levenshteinDistance]++;
        frequencies[node->wordEnd] = levenshteinDistance;
    }

    for (auto &child : node->children) {
        levenshteinDfs(child.second, word, child.first, currRow, distances, frequencies);
    }
}

LevenshteinTree::LevenshteinTuple LevenshteinTree::levenshteinDistance(std::string word) {
    std::unordered_map<int, int> frequencies;
    std::unordered_map<std::string, int> distances;
    std::vector<int> firstRow(word.size() + 1);

    for (unsigned int i = 0; i < word.size() + 1; i++) {
        firstRow[i] = i;
    }

    for (auto& child : this->children) {
        levenshteinDfs(child.second, word, child.first, firstRow, frequencies, distances);
    }

    return LevenshteinTuple(frequencies, distances);
}