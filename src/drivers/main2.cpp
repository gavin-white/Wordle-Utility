#include <iostream>
#include "models/games/EditDistanceWordleGame.hpp"
#include "utilities/FileReader.hpp"
#include "models/IWordProvider.hpp"
#include "models/BasicWordProvider.hpp"
#include "models/RandomWordProvider.hpp"
#include "models/solvers/EditDistanceWordleSolver.hpp"

void wordleUtilController(std::string filename);

/*
 * Entry point for Wordle solver program.
 * Starts up by calling the controller with the filename given on the
 * commandline. If the wrong number of arguments are given prints a usage message.
 */
int main (int argc, char * argv[]) {
    if (argc != 2) {
        std::cout << "Usage: ./wordle-util <filename>\n";
        return 1;
    }

    auto v = FileReader::readWords(argv[1], '\n');
    EditDistanceWordleGame wordle = EditDistanceWordleGame(v, RandomWordProvider(), 10);
    EditDistanceWordleSolver solver = EditDistanceWordleSolver(v);
    while(1) {
        std::cout << "Guess a word:\n";
        std::string line;
        getline(std::cin, line);
        std::cout << "Edit distance from answer: " << wordle.makeGuess(line) << std::endl;
        solver.takeGuess(line, 0);

    }
}