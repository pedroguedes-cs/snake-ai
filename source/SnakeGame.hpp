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

    bool isRunning;

    public:
        SnakeGame(GameConfig config);

        bool loadGame(std::string filePath);
        void runGame();

        void changeState(GameState gameState);

        void enterState();
        void enterPlayState();

        void updateState();
        void updatePlayState();

        void renderState();
        void renderInitState();
        void renderPlayState();
        void renderEatState();
        void renderHitState();
        void renderLevelDoneState();
        void renderWinState();
        void renderLoseState();
};