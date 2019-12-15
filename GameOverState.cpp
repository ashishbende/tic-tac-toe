#include "GameOverState.hpp"
#include "Definitions.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include <iostream>
#include <sstream>

namespace TicTacToe {
GameOverState::GameOverState(GameDataRef data) : _data(data) {}

void GameOverState::Init() {
  _data->assets.LoadTexture("Retry Button", RETRY_BUTTON);
  _data->assets.LoadTexture("Home Button", HOME_BUTTON);

  _retryButton.setTexture(_data->assets.GetTexture("Retry Button"));
  _homeButton.setTexture(_data->assets.GetTexture("Home Button"));

  auto windowX = _data->window.getSize().x;
  auto windowY = _data->window.getSize().y;
  // 3 == number of buttoms need to place vertically n+1 (3 gaps)
  _retryButton.setPosition(
      (windowX - _retryButton.getLocalBounds().width) / 2,
      (windowY / 3 - _retryButton.getLocalBounds().height) / 2);

  _homeButton.setPosition(
      (windowX - _homeButton.getLocalBounds().width) / 2,
      (windowY / 3 * 2 - _homeButton.getLocalBounds().height) / 2);
}

void GameOverState::HandleInput() {
  sf::Event event;
  while (_data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      _data->window.close();
    }

    if (_data->input.IsSpriteClicked(_retryButton, sf::Mouse::Left,
                                     _data->window)) {
      std::cout << "Go to game screen!" << std::endl;
      _data->machine.AddState(StateRef(new GameState(_data)), true);
    }

    if (_data->input.IsSpriteClicked(_homeButton, sf::Mouse::Left,
                                     _data->window)) {
      _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
    }
  }
}

void GameOverState::Update(float dt) {
  // need to add some animation
}

void GameOverState::Draw(float dt) {
  _data->window.clear();
  _data->window.draw(_retryButton);
  _data->window.draw(_homeButton);
  _data->window.display();
}
} // namespace TicTacToe