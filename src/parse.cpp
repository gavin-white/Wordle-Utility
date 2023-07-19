#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

int main() {
    std::string line;
    std::ifstream in = std::ifstream("wordle.txt");
    std::ofstream out = std::ofstream("new_words.txt");
    std::vector<std::string> words;
    while(getline(in, line)) {
        std::stringstream ss = std::stringstream(line);
        std::string word;
        ss >> word;
        ss >> word;
        ss >> word;
        words.push_back(word);
    }

    std::sort(words.begin(), words.end());
    for (std::string word : words) {
        out << word << "\n";
    }

}