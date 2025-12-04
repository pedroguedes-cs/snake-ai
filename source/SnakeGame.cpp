#include <iostream>
#include <fstream>
#include <limits>

#include "SnakeGame.hpp"

SnakeGame::SnakeGame(GameConfig config)
{
    this->currentState = GameState::INIT;

    if (config.algorithm == BFS)
    {
        this->playerAIPtr = std::make_unique<BFSPlayerAI>();
    }
    else if (config.algorithm == DFS)
    {
        this->playerAIPtr = std::make_unique<DFSPlayerAI>();
    }
    else
    {
        this->playerAIPtr = std::make_unique<RandomPlayerAI>();
    }

    this->algorithm = config.algorithm;
    this->lives = config.lives;
    this->foods = config.foods;
    this->fps = config.fps;
    this->score = 0;

    this->isRunning = true;
}

void SnakeGame::printInfo()
{
    std::cout << "\n=====[GAME INFO]\n";

    std::cout << "\nAlgorithm: " << this->algorithm;
    std::cout << "\nLives: " << this->lives;
    std::cout << "\nFoods: " << this->foods;
    std::cout << "\nFPS: " << this->fps;
    std::cout << "\nScore: " << this->score;
    std::cout << "\n\nMazes loaded: " << this->mazes.size() << "\n";
}

void SnakeGame::printMazesInfo()
{
    std::cout << "\n\n=====[MAZES INFO]";

    for (size_t i = 0; i < this->mazes.size(); i++)
    {
        std::cout << "\n\nMaze " << i << ":";
        std::cout << "\nRows = " << this->mazes[i].getRows();
        std::cout << "\nColumns = " << this->mazes[i].getColumns();
        std::cout << "\nBegin = (" << this->mazes[i].getBeginPosition().row << ", " << this->mazes[i].getBeginPosition().column << ")\n";
    }
}

bool SnakeGame::loadGame(std::string filePath)
{
    std::cout << "\n=====[Loading = '" << filePath << "']\n";
    std::ifstream File(filePath);

    /* Invalid file path */
    if (!File.is_open())
    {
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

    return true;
}

void SnakeGame::runGame()
{
    while (isRunning)
    {
        this->processEvents();
        this->updateState();
        this->renderState();
    }
}

void SnakeGame::changeState(GameState gameState)
{
    this->currentState = gameState;
}

void processEvents()
{
    // cin.get()
    // Check positions
    // Check lives
    // Check eaten foods
    // Check remaining mazes
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
    // Pick next move + snake.move()
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
        case GameState::LOAD_MAZE:
            this->renderLoadMazeState();
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
    // Info
}

void SnakeGame::renderPlayState()
{
    // Fps delay + Show next move
}

void SnakeGame::renderEatState()
{
    // Show message
}

void SnakeGame::renderHitState()
{
    // Show message
}

void SnakeGame::renderLoadMazeState()
{
    // Show message
}

void SnakeGame::renderWinState()
{
    // Show message
}

void SnakeGame::renderLoseState()
{
    // Show message
}