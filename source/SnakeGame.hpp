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
    Snake snake;
    std::unique_ptr<PlayerAI> playerAIPtr;
    int lives;
    int foods;
    int score;
    int fps;
    GameState currentState;

    public:
        SnakeGame(GameConfig config);
        ~SnakeGame();

        bool loadGame(std::string filePath);
        void runGame();
};