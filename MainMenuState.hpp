#pragma once

#include "Game.hpp"
#include "State.hpp"
#include <SFML/Graphics.hpp>

namespace TicTacToe {
class MainMenuState : public State {
public:
  MainMenuState(GameDataRef Data);

  void Init();

  void HandleInput();
  void Update(float dt);
  void Draw(float dt);

private:
  GameDataRef _data;
  sf::Sprite _background;
  sf::Sprite _playButton;
  sf::Sprite _playButtonOuter;
  sf::Sprite _title;
};
} // namespace TicTacToe