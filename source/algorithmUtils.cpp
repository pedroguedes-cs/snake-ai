#include <vector>
#include <deque>

#include "algorithmUtils.hpp"
#include "Position.hpp"
#include "Node.hpp"
#include "Direction.hpp"
#include "Maze.hpp"

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
            simulation.push_front({simulation[0].row - 1, simulation[0].column});
            simulation.pop_back();
            break;
        case Direction::DOWN:
            simulation.push_front({simulation[0].row + 1, simulation[0].column});
            simulation.pop_back();
            break;
        case Direction::LEFT:
            simulation.push_front({simulation[0].row, simulation[0].column - 1});
            simulation.pop_back();
            break;
        case Direction::RIGHT:
            simulation.push_front({simulation[0].row, simulation[0].column + 1});
            simulation.pop_back();
            break;
        default:
            break;
    }

    return simulation;
}

Position simulateNeighbor(Position position, Direction direction)
{
    Position neighbor = position;

    switch (direction)
    {
        case Direction::UP:
            neighbor.row--;
            break;
        case Direction::DOWN:
            neighbor.row++;
            break;
        case Direction::LEFT:
            neighbor.column--;
            break;
        case Direction::RIGHT:
            neighbor.column++;
            break;
        default:
            break;
    }

    return neighbor;
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
        if (head == snakeProjection[i])
        {
            hit = true;
            break;
        }
    }

    return hit;
}

bool moveOverItself(std::deque<Position> current, std::deque<Position> projection)
{
    if (current.size() != projection.size())
    {
        return false;
    }

    if (current.size() != 2)
    {
        return false;
    }

    return (current[0] == projection[1] && current[1] == projection[0]);
}

void insertLastNodeInSorted(std::vector<InformedNode>& storage, std::vector<size_t>& candidates)
{
    size_t storageIndex = storage.size() - 1;
    candidates.push_back(storageIndex);
    size_t candidatesIndex = candidates.size() - 1;

    while (candidatesIndex > 0 && storage[candidates[candidatesIndex]].cost > storage[candidates[candidatesIndex - 1]].cost)
    {
        std::swap(candidates[candidatesIndex], candidates[candidatesIndex - 1]);
        candidatesIndex--;
    }
}

size_t indexAtMaze(Position position, Maze maze)
{
    size_t rows = maze.getRows();
    size_t columns = maze.getColumns();

    size_t index = (columns * position.row) + position.column;

    return index;
}
