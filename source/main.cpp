#include <iostream>

#include "ArgumentParser.hpp"
#include "GameConfig.hpp"
#include "SnakeGame.hpp"
#include "utils.hpp"


int main(int argc, char* argv[])
{
  printTitle("SNAKE GAME - PEDRO GUEDES");

  // CLI
  ArgumentParser parser;
  std::optional<GameConfig> config = parser.parseArguments(argc, argv);
  bool cliSuccess = config.has_value();

  if (!cliSuccess)
  {
    std::cout << "\n\n=====[CLI: fail]\n\n";
    return 1;
  }

  std::cout << "\n\n=====[CLI: success]\n\n";


  // Load
  GameConfig validatedConfig = *config;
  SnakeGame game(validatedConfig);
  bool loadSuccess = game.loadGame(validatedConfig.filePath);

  if (!loadSuccess)
  {
    std::cout << "\n\n=====[LOAD: fail]\n\n";
    return 1;
  }

  std::cout << "\n\n=====[LOAD: success]\n\n";

  // Run game
  game.runGame();

  return 0;
}
