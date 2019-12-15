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
  void InitGridPieces();
  void CheckAndPlacePiece();
  void CheckPlayerHasWon(int turn);
  /// TODO: refactor this method for less params
  void Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3, int y3, int pieceToCheck);


  GameDataRef _data;
  sf::Sprite _background;
  sf::Sprite _pauseButton;
  sf::Sprite _gridSprite;
  sf::Sprite _gridPieces[3][3];
  int turn;
  /// TODO: replace with enum
  int gameState; 
  int gridArray[3][3];

};
} // namespace TicTacToe