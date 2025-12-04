#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#include "ArgumentParser.hpp"

std::optional<GameConfig> ArgumentParser::parseArguments(int argc, char* argv[])
{
    // Search help tag
    for (int i = 1; i < argc; i++)
    {
        std::string currentArgument = argv[i];

        if (currentArgument == "--help")
        {
            this->printHelpMessage();
            return std::nullopt;
        }
    }

    // Find tags
    GameConfig config;
    std::vector<std::string> tags = {"--fps", "--lives", "--foods", "--playertype"};
    std::vector<std::string> playertypes = {"bfs", "dfs", "random"};

    for (int i = 1; i < argc; i++)
    {
        std::string currentArgument = argv[i];

        bool isTag = std::find(tags.begin(), tags.end(), currentArgument) != tags.end();
        bool isLastArgument = (i == argc - 1);

        if (isTag)
        {
            if (isLastArgument)
            {
                printHelpMessage("Missing arguments");
                return std::nullopt;
            }

            if (currentArgument == "--playertype")
            {
                std::string nextArgument = argv[i+1];
                i++;

                bool isValidType = std::find(playertypes.begin(), playertypes.end(), nextArgument) != playertypes.end();

                if (!isValidType)
                {
                    printHelpMessage("Invalid playertype");
                    return std::nullopt;
                }

                if (nextArgument == "dfs")
                {
                    config.algorithm = DFS;
                }
                else if (nextArgument == "bfs")
                {
                    config.algorithm = BFS;
                }
                else if (nextArgument == "random")
                {
                    config.algorithm = RANDOM;
                }
            }
            else
            {
                std::string nextArgument = argv[i+1];
                i++;

                size_t pos;
                int nextArgumentInt;

                /* Validate int */
                try 
                {
                    nextArgumentInt = std::stoi(nextArgument, &pos);
                }
                catch (const std::invalid_argument& e)
                {
                    printHelpMessage("Invalid value");
                    return std::nullopt;
                }
                catch (const std::out_of_range& e)
                {
                    printHelpMessage("Value out of range");
                    return std::nullopt;
                }
                if (pos != nextArgument.size())
                {
                    printHelpMessage("Invalid value");
                    return std::nullopt;
                }
                if (nextArgumentInt <= 0)
                {
                    printHelpMessage("Invalid value");
                    return std::nullopt;
                }

                /* Assign value */
                if (currentArgument == "--fps")
                {
                    config.fps = nextArgumentInt;
                }
                else if (currentArgument == "--foods")
                {
                    config.foods = nextArgumentInt;
                }
                else if (currentArgument == "--lives")
                {
                    config.lives = nextArgumentInt;
                }
            }
        }
        else
        {
            if (config.filePath.empty())
            {
                config.filePath = currentArgument;
            }
            else 
            {
                printHelpMessage("Invalid argument");
                return std::nullopt;
            }
        }
    }

    if (config.filePath.empty())
    {
        printHelpMessage("Missing file path");
        return std::nullopt;
    }

    return config;
}

void ArgumentParser::printHelpMessage(std::string error)
{
    std::cout << "\n\nUsage: snaze [<options>] <input_level_file>";

    if (!error.empty())
    {
        std::cout << "\n\nError: " << error << "\n";
    }

    std::cout << "\n    Game simulation options:";
    std::cout << "\n        --help                  Print this help text.";
    std::cout << "\n        --fps <num>             Number of frames (boards) presented per second. Default = 2";
    std::cout << "\n        --lives <num>           Number of lives the snake shall have. Default = 5.";
    std::cout << "\n        --foods <num>           Number of food pallets for the entire simulation. Default = 10.";
    std::cout << "\n        --playertype <type>     Type of snake intelligence: bfs, dfs, random. Default = bfs";
}