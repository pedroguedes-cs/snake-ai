#include "PlayerAI.hpp"


void PlayerAI::clearDirections()
{
    directions.clear();
}

Direction PlayerAI::nextMove()
{
    return Direction::UP;
}

bool PlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    return true;
}

bool BFSPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    return true;
}

bool DFSPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    return true;
}

bool RandomPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    return true;
}