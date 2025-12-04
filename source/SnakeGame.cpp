#include <iostream>
#include <fstream>
#include <limits>

#include "SnakeGame.hpp"

SnakeGame::SnakeGame(GameConfig config)
{
    currentState = GameState::INIT;

    if (config.algorithm == BFS)
    {
        playerAIPtr = std::make_unique<BFSPlayerAI>();
    }
    else if (config.algorithm == DFS)
    {
        playerAIPtr = std::make_unique<DFSPlayerAI>();
    }
    else
    {
        playerAIPtr = std::make_unique<RandomPlayerAI>();
    }

    lives = config.lives;
    foods = config.foods;
    fps = config.fps;
    score = 0;

    isRunning = true;
}

bool SnakeGame::loadGame(std::string filePath)
{
    std::cout << "\n\nLoad game. file = " << filePath << "\n\n";
    std::ifstream File(filePath);

    /* Invalid file path */
    if (!File.is_open())
    {
        std::cout << "Couldn't open: " << filePath << "\n\n";
        return false;
    }

    /* Read file */
    while (true)
    {   
        bool incompleteMaze = false;
        int currentRowsCount;
        int currentColumnsCount;
        std::vector<std::string> lines;
        std::string currentLine;

        if (!(File >> currentRowsCount >> currentColumnsCount))
        {
            break;
        }

        /* Getline bug */
        File.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        lines.reserve(currentRowsCount);

        for (int i = 0; i < currentRowsCount; i++)
        {
            if (!std::getline(File, currentLine))
            {
                incompleteMaze = true;
                break;
            }

            lines.push_back(currentLine);
        }

        if (incompleteMaze)
        {
            break;
        }

        /* Valid Maze = valid rows, valid columns, no unexpected char, begin */
        bool validRowsCount = lines.size() == currentRowsCount;
        bool validColumnsCount = true;
        bool validChars = true;
        bool validBegin = false;

        for (auto l : lines)
        {
            if (l.size() != currentColumnsCount)
            {
                validColumnsCount = false;
                break;
            }
        }

        for (auto l : lines)
        {
            for (auto c : l)
            {
                if (c != '.' && c != '&' && c != '#' && c != ' ')
                {
                    validChars = false;
                    break;
                }
            }

            if (!validChars)
            {
                break;
            }
        }

        int beginFlagCount = 0;
        for (auto l : lines)
        {
            for (auto c : l)
            {
                if (c == '&')
                {
                    beginFlagCount++;
                }
            }
        }
        if (beginFlagCount == 1)
        {
            validBegin = true;
        }

        if (validBegin && validRowsCount && validColumnsCount && validChars)
        {
            Maze currentMaze(lines);
            this->mazes.push_back(currentMaze);
        }
    }

    /* At least 1 valid maze */
    if (this->mazes.size() == 0)
    {
        return false;
    }

    std::cout << "\nLoad status: success. Valid Mazes = " << this->mazes.size() << "\n\n";
    return true;
}

void SnakeGame::runGame()
{
    while (isRunning)
    {
        this->updateState();
        this->renderState();
    }
}

void SnakeGame::changeState(GameState gameState)
{
    this->currentState = gameState;
    this->enterState();
}

void SnakeGame::enterState()
{
    if (this->currentState == GameState::PLAY)
    {
        this->enterPlayState();
    }
}

void SnakeGame::enterPlayState()
{

}

void SnakeGame::updateState()
{
    if (this->currentState == GameState::PLAY)
    {
        this->updatePlayState();
    }
}

void SnakeGame::updatePlayState()
{
    
}

void SnakeGame::renderState()
{
    switch (this->currentState)
    {
        case GameState::INIT:
            this->renderInitState();
            break;
        case GameState::PLAY:
            this->renderPlayState();
            break;
        case GameState::EAT:
            this->renderEatState();
            break;
        case GameState::HIT:
            this->renderHitState();
            break;
        case GameState::LEVEL_DONE:
            this->renderLevelDoneState();
            break;
        case GameState::WIN:
            this->renderWinState();
            break;
        case GameState::LOSE:
            this->renderLoseState();
            break;
        default:
            break;
    }
}

void SnakeGame::renderInitState()
{

}

void SnakeGame::renderPlayState()
{

}

void SnakeGame::renderEatState()
{

}

void SnakeGame::renderHitState()
{

}

void SnakeGame::renderLevelDoneState()
{

}

void SnakeGame::renderWinState()
{

}

void SnakeGame::renderLoseState()
{

}