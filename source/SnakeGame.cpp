#include <iostream>
#include <fstream>
#include <limits>

#include "SnakeGame.hpp"
#include "utils.hpp"

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

    algorithm = config.algorithm;
    lives = config.lives;
    foods = config.foods;
    fps = config.fps;
    score = 0;

    isRunning = true;
    currentMazeIndex = 0;
}


//=====[INFO]=====
void SnakeGame::printInfo()
{
    std::cout << "\n=====[GAME INFO]\n";

    std::cout << "\nAlgorithm: " << algorithm;
    std::cout << "\nLives: " << lives;
    std::cout << "\nFoods: " << foods;
    std::cout << "\nFPS: " << fps;
    std::cout << "\nScore: " << score;
    std::cout << "\n\nMazes loaded: " << mazes.size() << "\n";
}

void SnakeGame::printConfig()
{

}

void SnakeGame::printMazesInfo()
{
    for (size_t i = 0; i < mazes.size(); i++)
    {
        std::cout << "\nMaze " << i + 1 << " [ rows: " <<  mazes[i].getRows() << " | columns: " << mazes[i].getColumns() << " | begin: (" << mazes[i].getBeginPosition().row << "," << mazes[i].getBeginPosition().column << ")";
    }
}


//=====[LOAD GAME]=====
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
            mazes.push_back(currentMaze);
        }
    }

    /* At least 1 valid maze */
    if (mazes.size() == 0)
    {
        return false;
    }

    return true;
}


//=====[GAME LOOP]=====
void SnakeGame::runGame()
{
    while (isRunning)
    {
        processEvents();
        updateState();
        renderState();
    }
}

//=====[PROCESS]=====
void SnakeGame::changeState(GameState gameState)
{
    currentState = gameState;
}

void SnakeGame::processEvents()
{
    switch (currentState)
    {
        case GameState::START:
            std::cin.get();
            changeState(GameState::INIT);
            break;
        case GameState::INIT:
            std::cin.get();
            changeState(GameState::LOAD_MAZE);
            break;
        case GameState::LOAD_MAZE:
            std::cin.get();
            changeState(GameState::PLAY);
            break;
        case GameState::PLAY:
            if (snakeEat())
            {
                changeState(GameState::EAT);
            }
            else if (snakeHit())
            {
                changeState(GameState::HIT);
            }
            break;
        case GameState::EAT:
            std::cin.get();
            if (mazeCompleted())
            {
                changeState(GameState::MAZE_COMPLETED);
            }
            else 
            {
                changeState(GameState::LOAD_MAZE);
            }
            break;
        case GameState::HIT:
            std::cin.get();
            if (snakeLose())
            {
                changeState(GameState::LOSE);
            }
            else
            {
                changeState(GameState::LOAD_MAZE);
            }
            break;
        case GameState::MAZE_COMPLETED:
            std::cin.get();

            mazes.erase(mazes.begin());

            if (snakeWin())
            {
                changeState(GameState::WIN);
            }
            else
            {
                changeState(GameState::LOAD_MAZE);
            }
            break;
        case GameState::WIN:
            std::cin.get();
            isRunning = false;
            changeState(GameState::END);
            break;
        case GameState::LOSE:
            std::cin.get();
            isRunning = false;
            changeState(GameState::END);
            break;
        default:
            break;
    }
}


//=====[UPDATE]=====
void SnakeGame::updateState()
{
    switch (currentState)
    {
        case GameState::LOAD_MAZE:
            updateLoadMazeState();
            break;
        case GameState::MAZE_COMPLETED:
            updateMazeCompletedState();
            break;
        case GameState::PLAY:
            updatePlayState();
            break;
        default:
            break;    
    }
}

void SnakeGame::updateLoadMazeState()
{
    // Place snake
    // Place food
    // Find solution
}

void SnakeGame::updateMazeCompletedState()
{
    mazes[currentMazeIndex].markAsCompleted();
    currentMazeIndex++;
}

void SnakeGame::updatePlayState()
{
    // Pick next move
    // Snake.move()
}


//=====[RENDER]=====
void SnakeGame::renderState()
{
    switch (currentState)
    {
        case GameState::INIT:
            renderInitState();
            break;
        case GameState::PLAY:
            renderPlayState();
            break;
        case GameState::EAT:
            renderEatState();
            break;
        case GameState::HIT:
            renderHitState();
            break;
        case GameState::LOAD_MAZE:
            renderLoadMazeState();
            break;
        case GameState::MAZE_COMPLETED:
            renderMazeCompletedState();
            break;
        case GameState::WIN:
            renderWinState();
            break;
        case GameState::LOSE:
            renderLoseState();
            break;
        default:
            break;
    }
}

void SnakeGame::renderInitState()
{
    printTitle("INIT");
    printMessage("LET'S GET STARTED!");
    printConfig();
    printInputMessage();
}

void SnakeGame::renderLoadMazeState()
{
    printTitle("MAZE LOADED");
    printMessage("LET'S PLAY!");
    printInfo();
    printMaze();
    printInputMessage();
}

void SnakeGame::renderPlayState()
{
    printTitle("PLAY");
    printMessage("LET'S GO AI!");
    printInfo();
    printMaze();
    pause(fps);
}

void SnakeGame::renderEatState()
{
    printTitle("EAT");
    printMessage("GOOD JOB AI!");
    printInfo();
    printMaze();
    printInputMessage();
}

void SnakeGame::renderHitState()
{
    printTitle("HIT");
    printMessage("OHHH NO!");
    printInfo();
    printMaze();
    printInputMessage();
}

void SnakeGame::renderMazeCompletedState()
{
    printTitle("MAZE COMPLETED");
    printMessage("UHUU... NEW LEVEL!");
    printInputMessage();
}

void SnakeGame::renderWinState()
{
    printTitle("WIN");
    printMessage("CONGRATULATIONS AI!");
    printInputMessage();
}

void SnakeGame::renderLoseState()
{
    printTitle("LOSE");
    printMessage("TRY AGAIN AI!");
    printInputMessage();
}


//=====[CHECK EVENTS]=====
bool SnakeGame::snakeEat()
{
    return (mazes[currentMazeIndex].isFood(snake.getHeadPosition()));
}

bool SnakeGame::snakeHit()
{
    return (mazes[currentMazeIndex].isWall(snake.getHeadPosition()) || snake.isSnakeBody(snake.getHeadPosition()));
}

bool SnakeGame::mazeCompleted()
{
    return (mazes[currentMazeIndex].getEatenFood() == foods);
}

bool SnakeGame::snakeLose()
{
    return (lives == 0);
}

bool SnakeGame::snakeWin()
{
    return (mazes.size() == 0);
}