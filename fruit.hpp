#ifndef FRUIT_HPP
#define FRUIT_HPP

#include "snake.hpp"

class Fruit final : public sf::Drawable {
public:
  explicit Fruit();
  void spawn(const Snake& snake);
  sf::FloatRect getGlobalBounds() const;

private:
  sf::CircleShape fruit_;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
