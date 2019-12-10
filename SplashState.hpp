#pragma once

#include "Game.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>

namespace TicTacToe {
class SplashState : public State {
public:
  SplashState(GameDataRef data);
  void Init();
  void HandleInput();
  void Update(float dt);
  void Draw(float dt);

private:
  GameDataRef _data;
  sf::Clock _clock;
  sf::Sprite _background;
};
} // namespace TicTacToe