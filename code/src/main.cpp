#include <iostream>

#include "../include/ArgumentParser.hpp"
#include "../include/GameConfig.hpp"
#include "../include/SnakeGame.hpp"
#include "../include/utils.hpp"


int main(int argc, char* argv[])
{
  printTitle("SNAKE AI - PEDRO GUEDES");

  // CLI
  ArgumentParser parser;
  std::optional<GameConfig> config = parser.parseArguments(argc, argv);
  bool cliSuccess = config.has_value();

  if (!cliSuccess)
  {
    return 1;
  }

  sleep(2);
  printSubtitle("CLI: success");


  // Load
  sleep(2);
  GameConfig validatedConfig = *config;
  SnakeGame game(validatedConfig);
  bool loadSuccess = game.loadGame(validatedConfig.filePath);
  
  sleep(2);
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
