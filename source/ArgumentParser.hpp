#pragma once 

#include "GameConfig.hpp"

class ArgumentParser
{
    public: 
        ArgumentParser();
        ~ArgumentParser();

        GameConfig parseArguments(int argc, char* argv[]);
};