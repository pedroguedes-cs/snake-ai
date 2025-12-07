#pragma once

#include <deque>

#include "Direction.hpp"
#include "Position.hpp"

struct Node
{
    Direction move;
    std::deque<Position> snakeProjection;
    size_t parent;
};