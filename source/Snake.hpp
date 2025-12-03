#pragma once

#include <vector>

#include "Position.hpp"


class Snake
{
    std::vector<Position> body;

    public:
        bool isSnake(Position position);
        bool isSnakeHead(Position position);
};