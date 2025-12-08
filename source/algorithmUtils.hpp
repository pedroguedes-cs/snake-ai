#pragma once

#include <deque>

#include "Position.hpp"
#include "Direction.hpp"
#include "Maze.hpp"

std::deque<Position> simulateMove(std::deque<Position> snakeProjection, Direction direction);
Position simulateNeighbor(Position position, Direction direction);
bool isValidInMaze(Position position, const Maze& maze);
bool hitItself(std::deque<Position> snakeProjection);
bool moveOverItself(std::deque<Position> current, std::deque<Position> projection);