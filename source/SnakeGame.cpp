#include <iostream>
#include <fstream>

#include "SnakeGame.hpp"

SnakeGame::SnakeGame()
{

}

bool SnakeGame::loadGame(std::string filePath)
{
    std::cout << "Load game: " << filePath << "\n\n";
    std::ifstream File(filePath);

    /* Handle file closed */
    if (!File.is_open())
    {
        std::cout << "Couldn't open: " << filePath << "\n\n";
        return false;
    }

    /* Read file */



    return true;
}