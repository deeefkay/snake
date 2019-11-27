#ifndef FIELD_HPP
#define FIELD_HPP

#include "snake.hpp"
#include "fruit.hpp"

class Field final : public sf::Drawable {
public:
  explicit Field(const sf::Font& font);
  void tick();
  void finishGame();

private:
  Snake snake_;
  Fruit fruit_;
  size_t score_;
  sf::Text score_text_;
  std::vector<sf::RectangleShape> walls_;
  void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
