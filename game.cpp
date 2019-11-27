#include "game.hpp"

Game::Game() : window_(sf::VideoMode(window_x, window_y), "Snake"),
               field_(font_)
{
}

void Game::run()
{
  //runs the game
  sf::Clock clock;
  auto time_elapsed = sf::Time::Zero;
  while (window_.isOpen()) {
    time_elapsed += clock.restart();
    sf::Event event{};
    //handles events
    while (window_.pollEvent(event)) {
      if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        field_.finishGame();
        return;
      }
    }
    field_.tick();
    window_.clear();
    window_.draw(field_);
    window_.display();
  }
}

void Game::menu()
{
  //loads textures
  sf::Texture start_texture, exit_texture, about_texture, background_texture;
  if (!font_.loadFromFile("Media/Arial.ttf")) {
    throw std::exception("Can't load font file");
  }
  if (!start_texture.loadFromFile("Images/start.png")) {
    throw std::exception("Can't load picture");
  }
  if (!exit_texture.loadFromFile("Images/exit.png")) {
    throw std::exception("Can't load picture");
  }
  if (!about_texture.loadFromFile("Images/about.png")) {
    throw std::exception("Can't load picture");
  }
  if (!background_texture.loadFromFile("Images/menu-bg.jpg")) {
    throw std::exception("Can't load picture");
  }
  sf::Sprite start(start_texture), exit(exit_texture), about(about_texture), menu_bg(background_texture);
  auto is_menu = true;
  auto menu_num = 0;
  //sets menu objects
  start.setPosition(100, 30);
  about.setPosition(100, 100);
  exit.setPosition(100, 170);
  menu_bg.setPosition(0, 0);
  //creates menu
  while (is_menu) {
    start.setColor(sf::Color::White);
    about.setColor(sf::Color::White);
    exit.setColor(sf::Color::White);
    menu_num = 0;
    window_.clear();
    window_.draw(menu_bg);
    if (sf::IntRect(100, 30, 180, 50).contains(sf::Mouse::getPosition(window_))) {
      start.setColor(sf::Color::Black);
      menu_num = 1;
    }
    if (sf::IntRect(100, 100, 220, 50).contains(sf::Mouse::getPosition(window_))) {
      about.setColor(sf::Color::Black);
      menu_num = 2;
    }
    if (sf::IntRect(100, 170, 130, 50).contains(sf::Mouse::getPosition(window_))) {
      exit.setColor(sf::Color::Black);
      menu_num = 3;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
      //start game
      if (menu_num == 1) {
        window_.clear();
        run();
      }
      //about
      if (menu_num == 2) {
        std::string string = "Press up, down, right, left to move Snake\n";
        string.append("Each fruit gives you 10 points and gains snake size by 1\n");
        string.append("Crash into the wall or snake finishes the game\n");
        string.append("Press esc to exit\n");
        about_.setString(string);
        about_.setFont(font_);
        about_.setStyle(sf::Text::Bold);
        about_.setCharacterSize(40);
        about_.setFillColor(sf::Color::Black);
        about_.setPosition(100, 0.f);
        window_.draw(about_);
        window_.display();
        while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Escape));
      }
      //exit
      if (menu_num == 3) {
        window_.close();
        is_menu = false;
      }
    }
    window_.draw(menu_bg);
    window_.draw(start);
    window_.draw(about);
    window_.draw(exit);
    window_.display();
  }
}
