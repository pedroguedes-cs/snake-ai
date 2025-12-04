#pragma once

#include <vector>

#include "Position.hpp"
#include "Direction.hpp"


class Snake
{
    std::vector<Position> body;

    public:
        bool isSnake(Position position);
        bool isSnakeHead(Position position);

        void move(Direction direction);
};