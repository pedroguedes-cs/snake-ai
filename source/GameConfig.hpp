#pragma once

#include <string>

#include "Algorithm.hpp"

struct GameConfig
{
    bool help = false;
    int fps = 2;
    int lives = 5;
    int foods = 10;
    Algorithm algorithm = Algorithm::BFS;
    std::string filePath;
};