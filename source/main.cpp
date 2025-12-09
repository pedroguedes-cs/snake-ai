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
    return 1;
  }

  printSubtitle("CLI: success");


  // Load
  GameConfig validatedConfig = *config;
  SnakeGame game(validatedConfig);
  bool loadSuccess = game.loadGame(validatedConfig.filePath);

  if (!loadSuccess)
  {
    printSubtitle("Load: fail");
    breakLine(3);
    return 1;
  }

  printSubtitle("Load: success");

  // Run game
  game.runGame();

  return 0;
}
