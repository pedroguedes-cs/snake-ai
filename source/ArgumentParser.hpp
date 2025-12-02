#pragma once 

#include <string>
#include <optional>

#include "GameConfig.hpp"

class ArgumentParser
{
    public: 
        std::optional<GameConfig> parseArguments(int argc, char* argv[]);
        void printHelpMessage(std::string error = "");
};