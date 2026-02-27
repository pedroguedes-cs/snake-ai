#pragma once

struct Position 
{
    int row = 0;
    int column = 0;

    bool operator<(const Position& other) const
    {
        if (row != other.row)
        {
            return (row < other.row);
        }

        return (column < other.column);
    }

    bool operator==(const Position& other) const
    {
        return (row == other.row && column == other.column);
    }
};