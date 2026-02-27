#pragma once 

#include <deque>
#include <unordered_map>

#include "Algorithm.hpp"
#include "Direction.hpp"
#include "Maze.hpp"
#include "Snake.hpp"


class PlayerAI
{
    protected:
        std::deque<Direction> path;
        std::unordered_map<size_t, bool> visitedPositions;

    public:
        virtual ~PlayerAI() = default;

        void clearPath();
        void clearVisitedPositions();
        std::deque<Direction> getPath();
        std::unordered_map<size_t, bool> getVisitedPositions();
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

class AStarPlayerAI : public PlayerAI
{
    public:
        bool findSolution(const Maze& maze, const Snake& snake) override;
};

class GBFSPlayerAI : public PlayerAI
{
    public:
        bool findSolution(const Maze& maze, const Snake& snake) override;
};

class RandomPlayerAI : public PlayerAI
{
    public:
        bool findSolution(const Maze& maze, const Snake& snake) override;
};
