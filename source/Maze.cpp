#include <vector>

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

Position Maze::getBeginPosition() const
{
    return beginPosition;
}

Position Maze::getFoodPosition() const
{
    return foodPosition;
}

size_t Maze::getRows() const
{
    return board.size();
}

size_t Maze::getColumns() const
{
    return board[0].size();
}

int Maze::getEatenFood() const
{
    return eatenFoods;
}

std::vector<Position> Maze::getFreePositions()
{
    std::vector<Position> freePositions;

    for (size_t i = 0; i < board.size(); i++)
    {
        for (size_t j = 0; j < board[0].size(); j++)
        {
            if (board[i][j] == ' ')
            {
                freePositions.push_back(Position {(int)i, (int)j});
            }
        }
    }

    return freePositions;
}

bool Maze::isCompleted() const
{
    return completed;
}

void Maze::markAsCompleted()
{
    completed = true;
}

void Maze::setFoodPosition(Position position)
{
    foodPosition = position;
}

void Maze::addEatenFood()
{
    eatenFoods++;
}

bool Maze::isFood(Position position) const
{
    if (!validPosition(position))
    {
        return false;
    }

    return (foodPosition == position);
}
bool Maze::isWall(Position position) const
{
    if (!validPosition(position))
    {
        return false;
    }

    return (board[position.row][position.column] == '#');
}

bool Maze::isInvisibleWall(Position position) const
{
    if (!validPosition(position))
    {
        return false;
    }

    return (board[position.row][position.column] == '.');
}

bool Maze::isBlank(Position position) const
{
    if (!validPosition(position))
    {
        return false;
    }

    return (board[position.row][position.column] == ' ' || board[position.row][position.column] == '&');
}

bool Maze::isOutOfBounds(Position position)
{
    bool up = position.row < 0;
    bool down = position.row >= getRows();
    bool left = position.column < 0;
    bool right = position.column >= getColumns();

    return (up || down || left || right);
}

bool Maze::validPosition(Position position) const
{
    bool validRow = position.row >= 0 && position.row < getRows();
    bool validColumn = position.column >= 0 && position.column < getColumns();

    return (validRow && validColumn);
}