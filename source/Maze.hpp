#pragma once

#include <vector>
#include <string>

#include "Position.hpp"

class Maze
{
    std::vector<std::vector<int>> board;
    Position foodPosition;
    Position beginPosition;
    int rowsCount;
    int columnsCount;

    public:
        Maze(const std::vector<std::string>& lines);
        ~Maze();
        
        void setFoodPosition(Position position);
        std::vector<Position> getEmptyPositions();
        bool isFood(Position position);
        bool isWall(Position position);
};