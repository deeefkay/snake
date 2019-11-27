#include "field.hpp"
#include "game.hpp"

Field::Field(const sf::Font& font) : score_(),
                                     walls_(4)
{
  //spawns fruit
  fruit_.spawn(snake_);
  //sets walls
  for (size_t i = 0; i < walls_.size(); ++i) {
    if (i % 2 == 0) {
      walls_.at(i).setSize({Game::window_x, Game::block_size});
    } else {
      walls_.at(i).setSize({Game::block_size, Game::window_y});
    }
    if (i == 1) {
      walls_.at(i).setPosition(Game::window_x - Game::block_size, 2 * Game::block_size);
    } else if (i == 2) {
      walls_.at(i).setPosition(0, Game::window_y - Game::block_size);
    } else {
      walls_.at(i).setPosition(0, 2 * Game::block_size);
    }
    walls_.at(i).setFillColor(sf::Color::Green);
  }
  //sets score line
  score_text_.setString("Score: " + std::to_string(score_));
  score_text_.setFont(font);
  score_text_.setStyle(sf::Text::Bold);
  score_text_.setCharacterSize(40);
  score_text_.setFillColor(sf::Color::Yellow);
  score_text_.setPosition(Game::window_x / 2.f - 100, 0.f);
}

void Field::tick()
{
  //user input
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
    snake_.setDirection(Snake::Direction::Up);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
    snake_.setDirection(Snake::Direction::Down);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
    snake_.setDirection(Snake::Direction::Left);
  } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
    snake_.setDirection(Snake::Direction::Right);
  }
  //checks if game is over
  if (snake_.isGameOver()) {
    score_ = 0;
    score_text_.setString("Score: " + std::to_string(score_));
    snake_.restart();
    snake_.tick();
  }
  //checks if snake ate fruit
  if (fruit_.getGlobalBounds().intersects(snake_.getSnakeHeadBounds())) {
    snake_.extendSnakeBody();
    score_text_.setString("Score: " + std::to_string(score_ += 10));
    fruit_.spawn(snake_);
  }
  //checks if snake collided into the wall
  for (const auto& side : walls_) {
    if (side.getGlobalBounds().intersects(snake_.getSnakeHeadBounds())) {
      score_ = 0;
      score_text_.setString("Score: " + std::to_string(score_));
      snake_.finishGame();
    }
  }
  //sets delay
  sleep(sf::seconds(0.1f));
  //moves snake
  snake_.tick();
}

void Field::finishGame()
{
  snake_.finishGame();
}


void Field::draw(sf::RenderTarget& target, const sf::RenderStates states) const
{
  //draws walls< snake, fruit and score line
  for (const auto& side : walls_) {
    target.draw(side, states);
  }
  target.draw(fruit_, states);
  target.draw(snake_, states);
  target.draw(score_text_, states);
}
