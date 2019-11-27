#include "snake.hpp"
#include "game.hpp"

Snake::Snake() : direction_(Direction::None),
                 game_over_(false)
{
  //sets snake body
  sf::RectangleShape rectangle_shape({Game::block_size - 1, Game::block_size - 1});
  rectangle_shape.setPosition(100 + Game::block_size, 100 + 2 * Game::block_size);
  rectangle_shape.setFillColor(sf::Color::Red);
  snake_body_.push_back(rectangle_shape);
  rectangle_shape.setPosition(100 + Game::block_size, 100 + Game::block_size);
  snake_body_.push_back(rectangle_shape);
}

void Snake::restart()
{
  //restarts game
  snake_body_.erase(snake_body_.begin() + 2, snake_body_.end());
  for (size_t i = 2; i > 0; --i) {
    snake_body_.at(i - 1).setPosition(70 + Game::block_size, 70 + i * Game::block_size);
  }
  game_over_ = false;
  direction_ = Direction::None;
}

void Snake::setDirection(const Direction dir)
{
  //changes snake direction
  if (direction_ == Direction::None && dir == Direction::Up) {
    return;
  }
  if (direction_ == Direction::Up && dir == Direction::Down) {
    return;
  }
  if (direction_ == Direction::Down && dir == Direction::Up) {
    return;
  }
  if (direction_ == Direction::Left && dir == Direction::Right) {
    return;
  }
  if (direction_ == Direction::Right && dir == Direction::Left) {
    return;
  }
  direction_ = dir;
}

bool Snake::isGameOver() const
{
  return game_over_;
}

void Snake::finishGame()
{
  game_over_ = true;
}

void Snake::extendSnakeBody()
{
  //adds one segment to snake body
  sf::RectangleShape shape({Game::block_size - 1, Game::block_size - 1});
  if (direction_ == Direction::Up) {
    shape.setPosition(snake_body_.back().getPosition().x, snake_body_.back().getPosition().y + Game::block_size);
  } else if (direction_ == Direction::Down) {
    shape.setPosition(snake_body_.back().getPosition().x, snake_body_.back().getPosition().y - Game::block_size);
  } else if (direction_ == Direction::Left) {
    shape.setPosition(snake_body_.back().getPosition().x + Game::block_size, snake_body_.back().getPosition().y);
  } else if (direction_ == Direction::Right) {
    shape.setPosition(snake_body_.back().getPosition().x - Game::block_size, snake_body_.back().getPosition().y);
  }
  shape.setFillColor(sf::Color::Red);
  snake_body_.push_back(shape);
}

void Snake::tick()
{
  if (direction_ == Direction::None) {
    return;
  }
  //moves snake
  std::copy_backward(snake_body_.begin(), snake_body_.end() - 1, snake_body_.end());
  if (direction_ == Direction::Left) {
    snake_body_.front().move(-Game::block_size, 0);
  } else if (direction_ == Direction::Right) {
    snake_body_.front().move(Game::block_size, 0);
  } else if (direction_ == Direction::Up) {
    snake_body_.front().move(0, -Game::block_size);
  } else if (direction_ == Direction::Down) {
    snake_body_.front().move(0, Game::block_size);
  }
  //checks if snake collided into herself
  for (size_t i = 1; i < snake_body_.size() - 1; ++i) {
    if (snake_body_.at(i).getPosition() == snake_body_.at(0).getPosition()) {
      game_over_ = true;
      break;
    }
  }
}

sf::FloatRect Snake::getSnakeHeadBounds() const
{
  return snake_body_.front().getGlobalBounds();
}

bool Snake::isSnakeIntersectFruit(const sf::CircleShape& shape) const
{
  //checks if snake get fruit
  for (const auto& part : snake_body_) {
    if (part.getGlobalBounds().intersects(shape.getGlobalBounds())) {
      return true;
    }
  }
  return false;
}

void Snake::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
  //draws snake
  for (const auto& part : snake_body_) {
    target.draw(part, states);
  }
}
