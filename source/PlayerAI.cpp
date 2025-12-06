#include <algorithm>
#include <set>
#include <queue>
#include <stack>

#include "PlayerAI.hpp"
#include "Node.hpp"


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


//=====[PLAYER AI UTILS]=====
std::deque<Position> simulateMove(std::deque<Position> snakeProjection, Direction direction)
{

    if (snakeProjection.empty())
    {
        return snakeProjection;
    }

    std::deque<Position> simulation = snakeProjection;

    switch (direction)
    {
        case Direction::UP:
            simulation.push_front({simulation[0].row--, simulation[0].column});
            simulation.pop_back();
            break;
        case Direction::DOWN:
            simulation.push_front({simulation[0].row++, simulation[0].column});
            simulation.pop_back();
            break;
        case Direction::LEFT:
            simulation.push_front({simulation[0].row, simulation[0].column--});
            simulation.pop_back();
            break;
        case Direction::RIGHT:
            simulation.push_front({simulation[0].row, simulation[0].column++});
            simulation.pop_back();
            break;
        default:
            break;
    }

    return simulation;
}

bool isValidInMaze(Position position, const Maze& maze)
{
    bool isValidRow = position.row >= 0 && position.row < maze.getRows();
    bool isValidColumn = position.column >= 0 && position.column < maze.getColumns();

    if (!(isValidRow && isValidColumn))
    {
        return false;
    }

    return maze.isBlank(position);
}

bool hitItself(std::deque<Position> snakeProjection)
{
    if (snakeProjection.empty())
    {
        return false;
    }

    bool hit = false;

    Position head = snakeProjection[0];

    for (size_t i = 1; i < snakeProjection.size(); i++)
    {
        if (snakeProjection[i].row == head.row && snakeProjection[i].column == head.column)
        {
            hit = true;
            break;
        }
    }

    return hit;
}