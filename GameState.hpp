#pragma once

#include "Game.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>

namespace TicTacToe {
class GameState : public State {
public:
  GameState(GameDataRef Data);

  void Init();

  void HandleInput();
  void Update(float dt);
  void Draw(float dt);

private:
  GameDataRef _data;
  sf::Sprite _background;
  sf::Sprite _pauseButton;
  int turn;
  int gameState; // replace with enum
};
} // namespace TicTacToe