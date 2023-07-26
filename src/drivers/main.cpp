#include <iostream>
#include "models/games/EditDistanceWordleGame.hpp"
#include "views/EditDistanceWordleGameView.hpp"
#include "models/games/WordleGame.hpp"
#include "utilities/FileReader.hpp"
#include "models/IWordProvider.hpp"
#include "models/BasicWordProvider.hpp"
#include "models/RandomWordProvider.hpp"
#include "models/solvers/EditDistanceWordleSolver.hpp"
#include "models/solvers/WordleSolver.hpp"
#include "views/WordleGameView.hpp"
#include "controllers/GameController.hpp"

/*
 * Entry point for Wordle solver program.
 * Starts up by calling the controller with the filename given on the
 * commandline. If the wrong number of arguments are given prints a usage message.
 */
int main (int argc, char * argv[]) {
    if (argc != 5) {
        std::cout << "Usage: ./wordle-utility <wordle | edwordle> <file-of-wordlist> <file-of-answer-list> <number-of-guesses>\n";
        return 1;
    }

    std::vector<std::string> allowedWords;
    std::vector<std::string> allowedAnswers;
    try {
        allowedWords = FileReader::readWords(argv[2], '\n');
        allowedAnswers = FileReader::readWords(argv[3], '\n');
    } catch (std::invalid_argument& e) {
        std::cout << "Could not read from provides files.\n";
        std::cout << "Usage: ./wordle-utility <wordle | edwordle> <file-of-wordlist> <file-of-answer-list> <number-of-guesses>\n";
        return 1;
    }

    int numGuesses = std::stoi(argv[4]);

    if (std::string(argv[1]) == "wordle") {
        WordleGameView view = WordleGameView();
        WordleSolver solver = WordleSolver(allowedWords);
        WordleGame game = WordleGame(allowedWords, RandomWordProvider(allowedAnswers), numGuesses);
        GameController<std::vector<WordleFeedback>> controller = GameController<std::vector<WordleFeedback>>(game, solver, view);
        controller.playGame();
    } else if (std::string(argv[1]) == "edwordle") {
        EditDistanceWordleGameView view = EditDistanceWordleGameView();
        EditDistanceWordleSolver solver = EditDistanceWordleSolver(allowedWords);
        EditDistanceWordleGame game = EditDistanceWordleGame(allowedWords, RandomWordProvider(allowedAnswers), numGuesses);
        GameController<int> controller = GameController<int>(game, solver, view);
        controller.playGame();
    } else {
        std::cout << "Usage: ./wordle-utility <wordle | edwordle> <file-of-wordlist> <file-of-answer-list> <number-of-guesses>\n";
        return 1;
    }    
}
