#include <iostream>
#include "game.hpp"

int main()
{
  try {
    Game game;
    game.menu();
  } catch (const std::exception& exception) {
    std::cout << exception.what() << std::endl;
    return 1;
  }
  return EXIT_SUCCESS;
}
