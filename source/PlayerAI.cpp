#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <stack>

#include "PlayerAI.hpp"
#include "Node.hpp"
#include "algorithmUtils.hpp"


void PlayerAI::clearPath()
{
    path.clear();
}

std::deque<Direction> PlayerAI::getPath()
{
    return path;
}

Direction PlayerAI::nextMove()
{
    if (path.empty())
    {
        return Direction::UP;
    }

    Direction direction = path[0];
    path.pop_front();
    
    return direction;
}

bool PlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    return true;
}

bool BFSPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    bool hasSolution = false;
    size_t goal = 0;

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
    std::set<std::deque<Position>> visited;
    std::vector<Node> storage;
    std::queue<size_t> candidates;

    storage.push_back({Direction::NONE, snake.getBody(), 0});
    candidates.push(0);
    visited.insert(snake.getBody());

    while (!candidates.empty())
    {
        size_t currentIndex = candidates.front();
        candidates.pop();

        // Found
        if (maze.isFood(storage[currentIndex].snakeProjection[0]))
        {
            hasSolution = true;
            goal = currentIndex;
            break;
        }

        // Add neighbors
        for (auto d : directions)
        {
            std::deque<Position> snakeProjection = simulateMove(storage[currentIndex].snakeProjection, d);

            bool validInMaze = isValidInMaze(snakeProjection[0], maze);
            bool hitSnake = hitItself(snakeProjection);
            bool wasVisited = (visited.find(snakeProjection) != visited.end());

            if (validInMaze && !hitSnake && !wasVisited)
            {
                visited.insert(snakeProjection);
                storage.push_back(Node {d, snakeProjection, currentIndex});
                candidates.push(storage.size() - 1);
            }
        }
    }

    if (hasSolution)
    {
        // Rebuild path
        size_t nodeIndex = goal;
        std::deque<Direction> moves;

        while (storage[nodeIndex].move != NONE)
        {
            moves.push_back(storage[nodeIndex].move);
            nodeIndex = storage[nodeIndex].parent;
        }

        std::reverse(moves.begin(), moves.end());

        this->path = moves;
    }

    return hasSolution;
}

bool DFSPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    bool hasSolution = false;
    size_t goal = 0;

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
    std::set<std::deque<Position>> visited;
    std::vector<Node> storage;
    std::stack<size_t> candidates;

    storage.push_back({Direction::NONE, snake.getBody(), 0});
    candidates.push(0);
    visited.insert(snake.getBody());

    while (!candidates.empty())
    {
        size_t currentIndex = candidates.top();
        candidates.pop();

        // Found
        if (maze.isFood(storage[currentIndex].snakeProjection[0]))
        {
            hasSolution = true;
            goal = currentIndex;
            break;
        }

        // Add neighbors
        for (auto d : directions)
        {
            std::deque<Position> snakeProjection = simulateMove(storage[currentIndex].snakeProjection, d);

            bool validInMaze = isValidInMaze(snakeProjection[0], maze);
            bool hitSnake = hitItself(snakeProjection);
            bool wasVisited = (visited.find(snakeProjection) != visited.end());

            if (validInMaze && !hitSnake && !wasVisited)
            {
                visited.insert(snakeProjection);
                storage.push_back(Node {d, snakeProjection, currentIndex});
                candidates.push(storage.size() - 1);
            }
        }
    }

    if (hasSolution)
    {
        // Rebuild path
        size_t nodeIndex = goal;
        std::deque<Direction> moves;

        while (storage[nodeIndex].move != NONE)
        {
            moves.push_back(storage[nodeIndex].move);
            nodeIndex = storage[nodeIndex].parent;
        }

        std::reverse(moves.begin(), moves.end());

        this->path = moves;
    }

    return hasSolution;
}

bool RandomPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    return true;
}
