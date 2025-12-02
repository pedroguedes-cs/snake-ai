#include <iostream>
#include <fstream>
#include <limits>

#include "SnakeGame.hpp"

SnakeGame::SnakeGame(GameConfig config)
{

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

        for (auto l : lines)
        {
            for (auto c : l)
            {
                if (c == '&')
                {
                    validBegin = true;
                    break;
                }
            }

            if (validBegin)
            {
                break;
            }
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