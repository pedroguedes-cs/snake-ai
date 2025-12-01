#pragma once

#include <vector>

#include "Position.hpp"


class Snake
{
    std::vector<Position> body;

    public:
        Snake();
        ~Snake();

        bool isSnake(Position position);
        bool isSnakeHead(Position position);
};