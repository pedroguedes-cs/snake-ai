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

        Position getBeginPosition() const;
        Position getFoodPosition() const;
        size_t getRows() const;
        size_t getColumns() const;
        int getEatenFood() const;

        bool isCompleted() const;
        void markAsCompleted();
        
        void setFoodPosition(Position position);
        void addEatenFood();

        bool isFood(Position position) const;
        bool isWall(Position position) const;
        bool isInvisibleWall(Position position) const;
        bool isBlank(Position position) const;

        bool validPosition(Position position) const;
};