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

Direction PlayerAI::nextMove()
{
    if (path.empty())
    {
        return Direction::UP;
    }

    return path[0];
    path.pop_front();
}

bool PlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    return true;
}

bool BFSPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    bool hasSolution = false;
    Node* goal = nullptr;

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
    std::set<std::deque<Position>> visited;
    std::vector<Node> storage;
    std::queue<Node*> candidates;

    storage.push_back({Direction::NONE, snake.getBody(), nullptr});
    candidates.push(&storage[0]);
    visited.insert(snake.getBody());

    while (!candidates.empty())
    {
        Node* currentPtr = candidates.front();
        candidates.pop();

        // Found
        if (maze.isFood(currentPtr->snakeProjection[0]))
        {
            hasSolution = true;
            goal = currentPtr;
            break;
        }

        // Add neighbors
        for (auto d : directions)
        {
            std::deque<Position> snakeProjection = simulateMove(currentPtr->snakeProjection, d);

            bool validInMaze = isValidInMaze(snakeProjection[0], maze);
            bool hitSnake = hitItself(snakeProjection);
            bool wasVisited = (visited.find(snakeProjection) != visited.end());

            if (validInMaze && !hitSnake && !wasVisited)
            {
                visited.insert(snakeProjection);
                storage.push_back(Node {d, snakeProjection, currentPtr});
                candidates.push(&storage.back());
            }
        }
    }

    if (hasSolution)
    {
        // Rebuild path
        Node* node = goal;
        std::deque<Direction> moves;

        while (node->parent != nullptr)
        {
            moves.push_back(node->move);
            node = node->parent;
        }

        std::reverse(moves.begin(), moves.end());

        this->path = moves;
    }

    return hasSolution;
}

bool DFSPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    bool hasSolution = false;
    Node* goal = nullptr;

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
    std::set<std::deque<Position>> visited;
    std::vector<Node> storage;
    std::stack<Node*> candidates;

    storage.push_back({Direction::NONE, snake.getBody(), nullptr});
    candidates.push(&storage[0]);
    visited.insert(snake.getBody());

    while (!candidates.empty())
    {
        Node* currentPtr = candidates.top();
        candidates.pop();

        // Found
        if (maze.isFood(currentPtr->snakeProjection[0]))
        {
            hasSolution = true;
            goal = currentPtr;
            break;
        }

        // Add neighbors
        for (auto d : directions)
        {
            std::deque<Position> snakeProjection = simulateMove(currentPtr->snakeProjection, d);

            bool validInMaze = isValidInMaze(snakeProjection[0], maze);
            bool hitSnake = hitItself(snakeProjection);
            bool wasVisited = (visited.find(snakeProjection) != visited.end());

            if (validInMaze && !hitSnake && !wasVisited)
            {
                visited.insert(snakeProjection);
                storage.push_back(Node {d, snakeProjection, currentPtr});
                candidates.push(&storage.back());
            }
        }
    }

    if (hasSolution)
    {
        // Rebuild path
        Node* node = goal;
        std::deque<Direction> moves;

        while (node->parent != nullptr)
        {
            moves.push_back(node->move);
            node = node->parent;
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
