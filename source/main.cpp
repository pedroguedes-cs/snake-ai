#include <iostream>

#include "ArgumentParser.hpp"
#include "GameConfig.hpp"
#include "SnakeGame.hpp"


int main(int argc, char* argv[])
{
  // CLI
  ArgumentParser parser;
  std::optional<GameConfig> config = parser.parseArguments(argc, argv);
  bool cliSuccess = config.has_value();

  if (!cliSuccess)
  {
    std::cout << "\n\n=====[CLI: fail]\n\n";
    return 1;
  }

  std::cout << "\n=====[CLI: success]\n";


  // LOAD
  GameConfig validatedConfig = *config;
  SnakeGame game(validatedConfig);
  bool loadSuccess = game.loadGame(validatedConfig.filePath);

  if (loadSuccess)
  {
    std::cout << "\n=====[LOAD: success]\n";
    game.printInfo();
    game.printMazesInfo();
  }
  else 
  {
    std::cout << "\n=====[LOAD: fail]\n\n";
    return 1;
  }


  // RUN
  std::cin.get();
  std::cout << "\n=====[RUN GAME]\n";

  return 0;
}
