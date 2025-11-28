#pragma once

#include <string>

#include "Algorithm.hpp"

struct GameConfig
{
    bool help = false;
    int lives = 5;
    int food = 10;
    int fps = 2;
    Algorithm algorithm = Algorithm::BFS;
    std::string filePath = "";
};