#include "Maze.hpp"

Maze::Maze(const std::vector<std::string>& lines)
{
    for (size_t i = 0; i < lines.size(); i++)
    {
        std::vector<char> row;

        for (size_t j = 0; j < lines[i].size(); j++)
        {
            char value = lines[i][j];

            row.push_back(value);

            if (value == '&')
            {
                this->beginPosition.row = i;
                this->beginPosition.column = j;
            }
        }

        this->board.push_back(row);
    }
}