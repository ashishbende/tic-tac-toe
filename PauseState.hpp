#pragma once

#include "Game.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>

namespace TicTacToe {
class PauseState : public State {
public:
  PauseState(GameDataRef Data);

  void Init();

  void HandleInput();
  void Update(float dt);
  void Draw(float dt);

private:
  GameDataRef _data;
  sf::Sprite _background;
  sf::Sprite _resumeButton;
  sf::Sprite _homeButton;
};
} // namespace TicTacToe