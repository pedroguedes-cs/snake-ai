#pragma once

#include <vector>
#include <string>

#include "Position.hpp"

class Maze
{
    std::vector<std::vector<char>> board;
    Position foodPosition;
    Position beginPosition;

    int eatenFoods;
    bool completed;

    public:
        Maze(const std::vector<std::string>& lines);

        Position getBeginPosition();
        size_t getRows();
        size_t getColumns();
        int getEatenFood();

        bool isCompleted();
        bool markAsCompleted();
        
        void setFoodPosition(Position position);
        std::vector<Position> getEmptyPositions();
        bool isFood(Position position);
        bool isWall(Position position);
};