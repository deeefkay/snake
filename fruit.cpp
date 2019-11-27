#include "fruit.hpp"
#include "game.hpp"
#include <random>

Fruit::Fruit()
{
  fruit_.setFillColor(sf::Color::Yellow);
  fruit_.setRadius(Game::block_size / 2.f);
}

void Fruit::spawn(const Snake& snake)
{
  //randomly spawns fruit on the field
  std::random_device random_device;
  std::mt19937 generator(random_device());
  const std::uniform_real_distribution<float> distribution_x(Game::block_size * 2,
                                                             Game::window_x - 2 * Game::block_size);
  const std::uniform_real_distribution<float> distribution_y(Game::block_size * 3,
                                                             Game::window_y - 3 * Game::block_size);
  fruit_.setPosition(distribution_x(generator), distribution_y(generator));
  //checks if fruit isn't intersected by snake 
  while (snake.isSnakeIntersectFruit(fruit_)) {
    fruit_.setPosition(distribution_x(generator), distribution_y(generator));
  }
}

sf::FloatRect Fruit::getGlobalBounds() const
{
  return fruit_.getGlobalBounds();
}

void Fruit::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
  //draws fruit
  target.draw(fruit_, states);
}
