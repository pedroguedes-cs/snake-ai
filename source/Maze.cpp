#include "Maze.hpp"

Maze::Maze(const std::vector<std::string>& lines)
{
    for (size_t i = 0; i < lines.size(); i++)
    {
        std::vector<char> row;

        for (size_t j = 0; j < lines[i].size(); j++)
        {
            char value = lines[i][j];

            if (value == '&')
            {
                beginPosition.row = i;
                beginPosition.column = j;
            }

            row.push_back(value);
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

int Maze::getEatenFood()
{
    return eatenFoods;
}

bool Maze::isCompleted()
{
    return completed;
}

bool Maze::markAsCompleted()
{
    completed = true;
}

bool Maze::isFood(Position position)
{
    if (!validPosition(position))
    {
        return false;
    }

    return (position.row == foodPosition.row && position.column == foodPosition.column);
}
bool Maze::isWall(Position position)
{
    if (!validPosition(position))
    {
        return false;
    }

    return (board[position.row][position.column] == '#');
}

bool Maze::isInvisibleWall(Position position)
{
    if (!validPosition(position))
    {
        return false;
    }

    return (board[position.row][position.column] == '.');
}

bool Maze::isBlank(Position position)
{
    if (!validPosition(position))
    {
        return false;
    }

    return (board[position.row][position.column] == ' ' || board[position.row][position.column] == '&');
}


bool Maze::validPosition(Position position)
{
    bool validRow = position.row >= 0 && position.row < getRows();
    bool validColumn = position.column >= 0 && position.column < getColumns();

    return (validRow && validColumn);
}