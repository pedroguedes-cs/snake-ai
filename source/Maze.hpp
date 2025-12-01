#pragma once

#include <vector>

#include "Position.hpp"

class Maze
{
    std::vector<std::vector<int>> board;
    Position food;
    Position begin;

    public:
        Maze();
        ~Maze();

        void setFoodPosition(Position position);

        std::vector<Position> getEmptyPositions();

        bool isFood(Position position);
        bool isWall(Position position);
};