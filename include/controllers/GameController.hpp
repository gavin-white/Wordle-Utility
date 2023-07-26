#pragma once

#include "../views/AbstractGameView.hpp"
#include "../models/games/IWordleGame.hpp"
#include "../models/solvers/IWordleSolver.hpp"

template<typename T>
class GameController {
    private:
    IWordleGame<T>& game;
    IWordleSolver<T>& solver;
    AbstractGameView<T>& view;
    int numOptions;
    
    public:
    GameController(IWordleGame<T>& game, IWordleSolver<T>& solver, AbstractGameView<T>& view);
    void playGame();
};

#include "../../src/controllers/GameController.tpp"
