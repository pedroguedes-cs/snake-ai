#pragma once 

#include <vector>

#include "Algorithm.hpp"
#include "Direction.hpp"
#include "Maze.hpp"
#include "Snake.hpp"


class PlayerAI
{
    protected:
        std::vector<Direction> directions;

    public:
        PlayerAI();
        virtual ~PlayerAI() = default;

        void clearDirections();
        virtual bool findSolution(const Maze& maze, const Snake& snake);
        Direction nextMove();
};

class BFSPlayerAI : public PlayerAI
{
    public:
        bool findSolution(const Maze& maze, const Snake& snake) override;
};

class DFSPlayerAI : public PlayerAI
{
    public:
        bool findSolution(const Maze& maze, const Snake& snake) override;
};

class RandomPlayerAI : public PlayerAI
{
    public:
        bool findSolution(const Maze& maze, const Snake& snake) override;
};