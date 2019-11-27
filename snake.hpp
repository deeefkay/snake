#ifndef SNAKE_HPP
#define SNAKE_HPP

#include <SFML/Graphics.hpp>

class Snake final : public sf::Drawable {
public:
  enum class Direction {
    None,
    Up,
    Down,
    Left,
    Right
  };

  explicit Snake();
  void restart();
  void setDirection(Direction dir);
  bool isGameOver() const;
  void finishGame();
  void extendSnakeBody();
  void tick();
  sf::FloatRect getSnakeHeadBounds() const;
  bool isSnakeIntersectFruit(const sf::CircleShape& shape) const;

private:
  std::vector<sf::RectangleShape> snake_body_;
  Direction direction_;
  bool game_over_;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
