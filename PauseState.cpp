#include "PauseState.hpp"
#include "Definitions.hpp"
#include "GameState.hpp"
#include "MainMenuState.hpp"
#include <iostream>
#include <sstream>

namespace TicTacToe {
PauseState::PauseState(GameDataRef data) : _data(data) {}

void PauseState::Init() {
  _data->assets.LoadTexture("Pause Background", PAUSE_BACKGROUND_FILEPATH);
  _data->assets.LoadTexture("Resume Button", RESUME_BUTTON);
  _data->assets.LoadTexture("Home Button", HOME_BUTTON);

  _background.setTexture(_data->assets.GetTexture("Pause Background"));
  _background.setTexture(_data->assets.GetTexture("Resume Button"));
  _background.setTexture(_data->assets.GetTexture("Home Button"));

  auto windowX = _data->window.getSize().x;
  auto windowY = _data->window.getSize().y;
  // 3 == number of buttoms need to place vertically n+1 (3 gaps)
  _resumeButton.setPosition(
      (windowX - _resumeButton.getLocalBounds().width) / 2,
      (windowY / 3 - _resumeButton.getLocalBounds().height) / 2);

  _homeButton.setPosition(
      (windowX - _homeButton.getLocalBounds().width) / 2,
      (windowY / 3 * 2 - _homeButton.getLocalBounds().height) / 2);
}

void PauseState::HandleInput() {
  sf::Event event;
  while (_data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      _data->window.close();
    }

    if (_data->input.IsSpriteClicked(_resumeButton, sf::Mouse::Left,
                                     _data->window)) {
      std::cout << "Go to game screen!" << std::endl;
      _data->machine.RemoveState();
    }

    if (_data->input.IsSpriteClicked(_homeButton, sf::Mouse::Left,
                                     _data->window)) {
      // remove pause state
      _data->machine.RemoveState();
      // replace with main menu state
      _data->machine.AddState(StateRef(new MainMenuState(_data)), true);
    }
  }
}

void PauseState::Update(float dt) {
  // need to add some animation
}

void PauseState::Draw(float dt) {
    _data->window.clear();
    _data->window.draw(_background);
    _data->window.draw(_homeButton);
    _data->window.draw(_resumeButton);

    _data->window.display();
}
} // namespace TicTacToe