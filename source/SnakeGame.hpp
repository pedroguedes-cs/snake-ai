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

    int lives;
    int foods;
    int fps;
    int score;

    public:
        SnakeGame(GameConfig config);

        bool loadGame(std::string filePath);
        void runGame();
};