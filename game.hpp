#ifndef GAME_HPP
#define GAME_HPP

#include "field.hpp"

class Game {
public:
  static constexpr float block_size = 25.f;
  static constexpr size_t window_x = 1280;
  static constexpr size_t window_y = 720;
  Game();
  void menu();

private:
  sf::RenderWindow window_;
  Field field_;
  sf::Font font_;
  sf::Text about_;
  void run();
};

#endif
