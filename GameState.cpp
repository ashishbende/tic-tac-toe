#include "GameState.hpp"
#include "Definitions.hpp"
#include <iostream>
#include <sstream>

namespace TicTacToe {
GameState::GameState(GameDataRef data) : _data(data) {}

void GameState::Init() {
  gameState = STATE_PLAYING;
  turn = PLAYER_PIECE;

  _data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
  _background.setTexture(_data->assets.GetTexture("Background"));
 _pauseButton.setTexture(_data->assets.GetTexture("Pause Button"));
 _pauseButton.setPosition(  (_data->window.getSize().x)-_pauseButton.getLocalBounds().width, 
                            (_data->window.getSize().y));
}

void GameState::HandleInput() {
  sf::Event event;
  while (_data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      _data->window.close();
    }

    if (_data->input.IsSpriteClicked(_pauseButton, sf::Mouse::Left,
                                     _data->window)) {
      std::cout << "Pause the game!" << std::endl;
    }
  }
}

void GameState::Update(float dt) {
  // need to add some animation
}

void GameState::Draw(float dt) {
  _data->window.clear();
  _data->window.draw(_background);
  _data->window.draw(_pauseButton);
  _data->window.display();
}
} // namespace TicTacToe