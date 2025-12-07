#pragma once

#include <deque>

#include "Position.hpp"
#include "Direction.hpp"


class Snake
{
    std::deque<Position> body {{-1, -1}};
    Position lastTail {-1, -1};

    public:
        Position getHeadPosition();
        std::deque<Position> getBody() const;

        bool isSnake(Position position);
        bool isSnakeHead(Position position);
        bool isSnakeBody(Position position);

        void move(Direction direction);
        void grow();

        void reset(Position position);
        void removeBody();
        void resetPosition(Position position);
};