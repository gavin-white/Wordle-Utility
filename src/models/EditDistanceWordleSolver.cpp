#include <chrono>
#include <iostream>
#include <algorithm>
#include <numeric>
#include "models/EditDistanceWordleSolver.hpp"
#include "models/EditDistanceWordle.hpp"

EditDistanceWordleSolver::EditDistanceWordleSolver() {

}

EditDistanceWordleSolver::EditDistanceWordleSolver(std::vector<std::string> allowedWords) {
    this->availableOptions = allowedWords;
}


void EditDistanceWordleSolver::takeGuess(std::string guess, const int feedback) {
    // Get the starting timepoint
    auto start = std::chrono::high_resolution_clock::now();
    
    std::vector<int> distances;

    for (std::string& word : availableOptions) {
        for (std::string& word2 : availableOptions) {
            distances.push_back(EditDistanceWordle::editDistance(word, word2));
            //std::cout << word << " " << word2 << "\n";
        }
    }
    
    // mean of distances values
    //int mean = std::accumulate(distances.begin(), distances.end(), 0) / distances.size();
    //std::cout << "Mean edit distance: " << mean << std::endl;

    // Get the ending timepoint
    auto end = std::chrono::high_resolution_clock::now();
    
    // Get duration. Subtracts two timepoints and returns a duration
    std::chrono::duration<double> elapsed = end - start;
    
    std::cout << "Time taken by function: " << elapsed.count() << " seconds" << std::endl;
}