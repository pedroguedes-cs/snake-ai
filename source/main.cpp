#include <iostream>

#include "ArgumentParser.hpp"
#include "GameConfig.hpp"
#include "SnakeGame.hpp"


int main(int argc, char* argv[])
{
  ArgumentParser parser;

  std::optional<GameConfig> config = parser.parseArguments(argc, argv);

  if (config.has_value())
  {

    GameConfig validatedConfig = *config;

    std::cout << "\n\nCLI: success\n\n";

    std::cout << "Foods: "<< validatedConfig.foods << "\n\n";
    std::cout << "Lives: "<< validatedConfig.lives << "\n\n";
    std::cout << "FPS: "<< validatedConfig.fps << "\n\n";
    std::cout << "Algorithm: "<< validatedConfig.algorithm << "\n\n";
    std::cout << "File path: "<< validatedConfig.filePath << "\n\n";
  }
  else 
  {
    std::cout << "\n\nCLI: fail\n\n";
    return 1;
  }

  GameConfig validatedConfig = *config;

  SnakeGame game(validatedConfig);

  if (game.loadGame(validatedConfig.filePath))
  {
    std::cout << "\nLoad: success\n";
  }
  else 
  {
    std::cout << "\nLoad: fail\n";
  }

  return 0;
}
