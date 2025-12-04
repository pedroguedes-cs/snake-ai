#pragma once

#include <memory>

#include "Algorithm.hpp"
#include "ArgumentParser.hpp"
#include "GameConfig.hpp"
#include "GameState.hpp"
#include "Maze.hpp"
#include "PlayerAI.hpp"
#include "Position.hpp"
#include "Snake.hpp"

class SnakeGame 
{
    std::vector<Maze> mazes;
    GameState currentState;
    std::unique_ptr<PlayerAI> playerAIPtr;
    Snake snake;

    Algorithm algorithm;
    int lives;
    int foods;
    int fps;
    int score;

    bool isRunning;

    public:
        SnakeGame(GameConfig config);

        void printInfo();
        void printMazesInfo();

        bool loadGame(std::string filePath);
        void runGame();

        void changeState(GameState gameState);

        void processEvents();  // Game loop 1

        void updateState(); // Game loop 2
        void updatePlayState();

        void renderState(); // Game loop 3
        void renderInitState();
        void renderPlayState();
        void renderEatState();
        void renderHitState();
        void renderLoadMazeState();
        void renderWinState();
        void renderLoseState();
};