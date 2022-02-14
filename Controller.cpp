#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <exception>
#include <sstream>
#include "WordleSolver.h"

/*
 * Controller for the Wordle Utility. Handles the command-line
 * interface, passing input as appropriate to the Wordle Solver
 * and prompting the user.
 */
void wordleUtilController(std::string filename) {
    WordleSolver solver;
    try {
        solver.init(filename);
    } catch (std::exception& e) {
        std::cout << "Issue loading wordlist file: " << e.what() << std::endl;
        return;
    }

    do {
        std::cout << "There are: " << solver.numOptions() << " remaining.\n";
        std::cout << "How many options for guesses would you like to see?\n";   

        std::string line;
        std::cout << "-----\n";
        getline(std::cin, line);
        std::cout << "-----\n";
        std::stringstream ss = std::stringstream(line);
        int n; 
        if (!(ss >> n)) {
            std::cout << "Error: expected an integer number for the number of guesses\n";
            continue;
        }

        std::map<std::string, bool> options = solver.getAllOptions(n);
        for (auto it = options.begin(); it != options.end(); it++) {
            std::cout << it->first << (it->second ? " (valid)" : " (invalid") << std::endl;
        }

    } while (true);
}