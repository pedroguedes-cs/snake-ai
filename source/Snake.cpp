#include "Snake.hpp"


Position Snake::getHeadPosition()
{
    if (body.empty())
    {
        return {-1, -1};
    }

    return body[0];
}

std::deque<Position> Snake::getBody() const
{
    return body;
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

    if (body.empty())
    {
        return;
    }

    lastTail = body[body.size() - 1];

    switch (direction)
    {
        case Direction::UP:
            body.push_front({body[0].row - 1, body[0].column});
            body.pop_back();
            break;
        case Direction::DOWN:
            body.push_front({body[0].row + 1, body[0].column});
            body.pop_back();
            break;
        case Direction::LEFT:
            body.push_front({body[0].row, body[0].column - 1});
            body.pop_back();
            break;
        case Direction::RIGHT:
            body.push_front({body[0].row, body[0].column + 1});
            body.pop_back();
            break;
        default:
            break;
    }
}

void Snake::grow()
{
    if (lastTail.row != -1 || lastTail.column != -1)
    {
        body.push_back(lastTail);
    }

    lastTail = {-1, -1};
}

void Snake::reset(Position position)
{
    removeBody();
    resetPosition(position);

    lastTail = {-1, -1};
}

void Snake::removeBody()
{
    while(body.size() > 1)
    {
        body.pop_back();
    }
}

void Snake::resetPosition(Position position)
{
    if (!body.empty())
    {
        body[0].row = position.row;
        body[0].column = position.column;
    }
}