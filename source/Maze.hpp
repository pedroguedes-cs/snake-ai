#pragma once

#include <vector>
#include <string>

#include "Position.hpp"

class Maze
{
    std::vector<std::vector<char>> board;
    Position foodPosition;
    Position beginPosition;

    public:
        Maze(const std::vector<std::string>& lines);
        
        void setFoodPosition(Position position);
        std::vector<Position> getEmptyPositions();
        bool isFood(Position position);
        bool isWall(Position position);
};