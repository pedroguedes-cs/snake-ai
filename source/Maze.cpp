#include "Maze.hpp"

Maze::Maze(const std::vector<std::string>& lines)
{
    for (size_t i = 0; i < lines.size(); i++)
    {
        std::vector<char> row;

        for (size_t j = 0; j < lines[i].size(); j++)
        {
            char value = lines[i][j];

            row.push_back(value);

            if (value == '&')
            {
                beginPosition.row = i;
                beginPosition.column = j;
            }
        }

        board.push_back(row);
    }

    eatenFoods = 0;
    completed = false;
}

Position Maze::getBeginPosition()
{
    return beginPosition;
}

size_t Maze::getRows()
{
    return board.size();
}

size_t Maze::getColumns()
{
    return board[0].size();
}

bool Maze::isCompleted()
{
    return completed;
}

bool Maze::markAsCompleted()
{
    completed = true;
}