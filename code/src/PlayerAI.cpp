#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>

#include "../include/PlayerAI.hpp"
#include "../include/Node.hpp"
#include "../include/algorithmUtils.hpp"
#include "../include/utils.hpp"


void PlayerAI::clearPath()
{
    path.clear();
}

void PlayerAI::clearVisitedPositions()
{
    visitedPositions.clear();
}

std::deque<Direction> PlayerAI::getPath()
{
    return path;
}

std::unordered_map<size_t, bool> PlayerAI::getVisitedPositions()
{
    return visitedPositions;
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
    clearPath();
    clearVisitedPositions();
    return true;
}

bool BFSPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    clearPath();
    clearVisitedPositions();

    bool hasSolution = false;
    size_t goal = 0;

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
    std::unordered_map<size_t, bool> visitedPositionsMap;
    std::set<std::deque<Position>> visited;
    std::vector<Node> storage;
    std::queue<size_t> candidates;

    storage.push_back({Direction::NONE, snake.getBody(), 0});
    candidates.push(0);
    visited.insert(snake.getBody());

    while (!candidates.empty())
    {
        
        size_t currentIndex = candidates.front();
        visitedPositionsMap[indexAtMaze(storage[currentIndex].snakeProjection[0], maze)] = true;
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
            bool moveOverSnake = moveOverItself(storage[currentIndex].snakeProjection, snakeProjection);
            bool wasVisited = (visited.find(snakeProjection) != visited.end());

            if (validInMaze && !hitSnake && !moveOverSnake && !wasVisited)
            {
                visited.insert(snakeProjection);
                storage.push_back(Node {d, snakeProjection, currentIndex});
                candidates.push(storage.size() - 1);
            }
        }
    }

    visitedPositions = visitedPositionsMap;

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

        moves.push_back(NONE);

        std::reverse(moves.begin(), moves.end());

        this->path = moves;
    }

    return hasSolution;
}

bool DFSPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    clearPath();
    clearVisitedPositions();

    bool hasSolution = false;
    size_t goal = 0;

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
    std::unordered_map<size_t, bool> visitedPositionsMap;
    std::set<std::deque<Position>> visited;
    std::vector<Node> storage;
    std::stack<size_t> candidates;

    storage.push_back({Direction::NONE, snake.getBody(), 0});
    candidates.push(0);
    visited.insert(snake.getBody());

    while (!candidates.empty())
    {
        size_t currentIndex = candidates.top();
        visitedPositionsMap[indexAtMaze(storage[currentIndex].snakeProjection[0], maze)] = true;
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
            bool moveOverSnake = moveOverItself(storage[currentIndex].snakeProjection, snakeProjection);
            bool wasVisited = (visited.find(snakeProjection) != visited.end());

            if (validInMaze && !hitSnake && !moveOverSnake && !wasVisited)
            {
                visited.insert(snakeProjection);
                storage.push_back(Node {d, snakeProjection, currentIndex});
                candidates.push(storage.size() - 1);
            }
        }
    }

    visitedPositions = visitedPositionsMap;

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

        moves.push_back(NONE);

        std::reverse(moves.begin(), moves.end());

        this->path = moves;
    }

    return hasSolution;
}

bool AStarPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    clearPath();
    clearVisitedPositions();

    bool hasSolution = false;
    Position food = maze.getFoodPosition();
    size_t goal = 0;

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
    std::unordered_map<size_t, bool> visitedPositionsMap;
    std::set<std::deque<Position>> visited;
    std::vector<InformedNode> storage;
    std::vector<size_t> candidates;

    std::deque<Position> firstState = snake.getBody();
    int firstDistance = manhattanDistance(firstState[0], food);
    int firstSteps = 0;

    storage.push_back({Direction::NONE, firstState, 0, firstDistance, firstSteps, firstDistance + firstSteps});
    candidates.push_back(0);
    visited.insert(firstState);

    while (!candidates.empty())
    {
        size_t currentIndex = candidates.back();
        visitedPositionsMap[indexAtMaze(storage[currentIndex].snakeProjection[0], maze)] = true;
        candidates.pop_back();

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
            bool moveOverSnake = moveOverItself(storage[currentIndex].snakeProjection, snakeProjection);
            bool wasVisited = (visited.find(snakeProjection) != visited.end());

            if (validInMaze && !hitSnake && !moveOverSnake && !wasVisited)
            {
                visited.insert(snakeProjection);

                int distance = manhattanDistance(snakeProjection[0], food);
                int steps = storage[currentIndex].stepsFromOrigin + 1;

                storage.push_back(InformedNode {d, snakeProjection, currentIndex, distance, steps, distance + steps});

                insertLastNodeInSorted(storage, candidates);
            }
        }
    }

    visitedPositions = visitedPositionsMap;

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

        moves.push_back(NONE);

        std::reverse(moves.begin(), moves.end());

        this->path = moves;
    }

    return hasSolution;
}

bool GBFSPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    clearPath();
    clearVisitedPositions();

    bool hasSolution = false;
    Position food = maze.getFoodPosition();
    size_t goal = 0;

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
    std::unordered_map<size_t, bool> visitedPositionsMap;
    std::set<std::deque<Position>> visited;
    std::vector<InformedNode> storage;
    std::vector<size_t> candidates;

    std::deque<Position> firstState = snake.getBody();
    int firstDistance = manhattanDistance(firstState[0], food);

    storage.push_back({Direction::NONE, firstState, 0, firstDistance, 0, firstDistance});
    candidates.push_back(0);
    visited.insert(firstState);

    while (!candidates.empty())
    {
        size_t currentIndex = candidates.back();
        visitedPositionsMap[indexAtMaze(storage[currentIndex].snakeProjection[0], maze)] = true;
        candidates.pop_back();

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
            bool moveOverSnake = moveOverItself(storage[currentIndex].snakeProjection, snakeProjection);
            bool wasVisited = (visited.find(snakeProjection) != visited.end());

            if (validInMaze && !hitSnake && !moveOverSnake && !wasVisited)
            {
                visited.insert(snakeProjection);

                int distance = manhattanDistance(snakeProjection[0], food);

                storage.push_back(InformedNode {d, snakeProjection, currentIndex, distance, 0, distance});

                insertLastNodeInSorted(storage, candidates);
            }
        }
    }

    visitedPositions = visitedPositionsMap;

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

        moves.push_back(NONE);

        std::reverse(moves.begin(), moves.end());

        this->path = moves;
    }

    return hasSolution;
}


bool RandomPlayerAI::findSolution(const Maze& maze, const Snake& snake)
{
    clearPath();
    clearVisitedPositions();

    bool find = false;
    size_t maxSteps = std::min(maze.getRows() * maze.getColumns() * 2, (size_t)1000);

    std::vector<Direction> directions = {UP, DOWN, LEFT, RIGHT};
    std::deque<Direction> moves;
    std::deque<Position> currentSnake = snake.getBody();

    for (size_t i = 0; i < maxSteps; i++)
    {
        if (maze.isFood(currentSnake[0]))
        {
            find = true;
            break;
        }

        std::vector<Direction> validMoves;

        for (auto d : directions)
        {
            std::deque<Position> snakeProjection = simulateMove(currentSnake, d);

            bool validInMaze = isValidInMaze(snakeProjection[0], maze);
            bool hitSnake = hitItself(snakeProjection);
            bool moveOverSnake = moveOverItself(currentSnake, snakeProjection);

            if (validInMaze && !hitSnake && !moveOverSnake)
            {
                validMoves.push_back(d);
            } 
        }

        if (validMoves.empty())
        {
            moves.push_back(UP);
            break;
        }

        Direction randomMove = validMoves[random(0, validMoves.size() - 1)];
        currentSnake = simulateMove(currentSnake, randomMove);
        moves.push_back(randomMove);
    }

    path = moves;

    return find;
}
