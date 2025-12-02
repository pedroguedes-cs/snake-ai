#include <iostream>

#include "ArgumentParser.hpp"
#include "GameConfig.hpp"


int main(int argc, char* argv[])
{
  ArgumentParser parser;

  std::optional<GameConfig> config = parser.parseArguments(argc, argv);

  if (config.has_value())
  {

    GameConfig validatedConfig = *config;

    std::cout << "\n\nSUCCESS\n\n";

    std::cout << "Foods: "<< validatedConfig.foods << "\n\n";
    std::cout << "Lives: "<< validatedConfig.lives << "\n\n";
    std::cout << "FPS: "<< validatedConfig.fps << "\n\n";
    std::cout << "Algorithm: "<< validatedConfig.algorithm << "\n\n";
    std::cout << "File path: "<< validatedConfig.filePath << "\n\n";
  }
  else 
  {
    std::cout << "\n\nFAIL\n\n";
  }

  return 0;
}
