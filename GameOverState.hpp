#pragma once

#include "Game.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>

namespace TicTacToe {
class GameOverState : public State {
public:
  GameOverState(GameDataRef Data);

  void Init();

  void HandleInput();
  void Update(float dt);
  void Draw(float dt);

private:
  GameDataRef _data;
  sf::Sprite _retryButton;
  sf::Sprite _homeButton;
};
} // namespace TicTacToe