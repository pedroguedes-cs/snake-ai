#pragma once

#include <vector>

#include "Position.hpp"
#include "Direction.hpp"


class Snake
{
    std::vector<Position> body;

    public:
        Position getHeadPosition();

        bool isSnake(Position position);
        bool isSnakeHead(Position position);
        bool isSnakeBody(Position position);

        void move(Direction direction);

        void removeBody();
        void resetPosition(Position position);
};