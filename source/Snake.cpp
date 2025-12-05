#include "Snake.hpp"


Position Snake::getHeadPosition()
{
    if (body.empty())
    {
        return {-1, -1};
    }

    return body[0];
}

bool Snake::isSnake(Position position)
{
    for (size_t i = 0; i < body.size(); i++)
    {
        if (position.row == body[i].row && position.column == body[i].column)
        {
            return true;
        }
    }

    return false;
}

bool Snake::isSnakeHead(Position position)
{
    return (position.row == body[0].row && position.column == body[0].column);
}

bool Snake::isSnakeBody(Position position)
{
    for (size_t i = 1; i < body.size(); i++)
    {
        if (position.row == body[i].row && position.column == body[i].column)
        {
            return true;
        }
    }

    return false;
}

void Snake::move(Direction direction)
{
    switch (direction)
    {
        case Direction::UP:
            for (size_t i = 0; i < body.size(); i++)
            {
                body[i].column--;
            }
            break;
        case Direction::DOWN:
            for (size_t i = 0; i < body.size(); i++)
            {
                body[i].column++;
            }
            break;
        case Direction::LEFT:
            for (size_t i = 0; i < body.size(); i++)
            {
                body[i].row--;
            }
            break;
        case Direction::RIGHT:
            for (size_t i = 0; i < body.size(); i++)
            {
                body[i].row++;
            }
            break;
        default:
            break;
    }
}