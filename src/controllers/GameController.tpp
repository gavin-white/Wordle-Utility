#pragma once

#include "controllers/GameController.hpp"

template<typename T>
GameController<T>::GameController(IWordleGame<T>& game, IWordleSolver<T>& solver, AbstractGameView<T>& view) 
    : game(game), solver(solver), view(view), numOptions(solver.numOptions()) {}

template<typename T>
void GameController<T>::playGame() {
    view.printWelcome(this->game.guessesRemaining());
    view.printGuesses(this->game.getGuesses(), this->game.getFeedback());
    view.printGuessesRemaining(this->game.guessesRemaining());
    view.printWordsRemaining(this->numOptions - solver.numOptions(), solver.numOptions());
    while (game.getGameState() == ONGOING) {
        view.promptCommand();
        std::string command;
        std::cin >> command;
        if (command == "guess") {
            std::string guess;
            std::cin >> guess;
            T feedback;
            try {
                feedback = game.makeGuess(guess);
            } catch (std::invalid_argument& e) {
                view.printInvalidGuess(e.what());
                continue;
            }
            view.clear();
            solver.takeGuess(guess, feedback);
            view.printGuesses(this->game.getGuesses(), this->game.getFeedback());
            view.printGuessesRemaining(this->game.guessesRemaining());
            view.printWordsRemaining(this->numOptions - solver.numOptions(), solver.numOptions());
        } else if (command == "recommend") {
            int num;
            std::cin >> num;
            std::vector<std::pair<std::string, bool>> recommendations = solver.recommendGuesses(num);
            view.printRecommendations(recommendations);
        } else if (command == "match") {
            std::string templateString;
            int num;
            std::cin >> templateString >> num;
            std::vector<std::pair<std::string, bool>> recommendations = solver.matchGuesses(templateString, num);
            view.printRecommendations(recommendations);
        } else if (command == "quit") {
            return;
        } else {
            view.printInvalidCommand("Invalid command.");
        }
    }
    if (game.getGameState() == WON) {
        view.printWin(game.getAnswer());
    } else {
        view.printLoss(game.getAnswer());
    }
}