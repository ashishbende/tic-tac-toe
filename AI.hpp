#pragma once

#include "Game.hpp"
#include <SFML/Graphics.hpp>
#include <array>
#include <vector>

namespace TicTacToe {
class AI {
public:
  AI(int playerPiece, GameDataRef data);

  void PlacePiece(int (*gridArray)[3][3], sf::Sprite gridPieces[3][3],
                  int *gameState);

private:
  // decides what third piece to place, based on other two piece
  void CheckSection(int x1, int y1, int x2, int y2, int X, int Y,
                    int pieceToCheck, int (*gridArray)[3][3],
                    sf::Sprite gridPieces[3][3]);

  void CheckIfPieceIsEmpty(int X, int Y, int (*gridArray)[3][3],
                           sf::Sprite gridPieces[3][3]);
  int aiPiece;
  int playerPiece;

  std::vector<std::array<int, 6>> checkMatchVector;
  GameDataRef _data;
};
} // namespace TicTacToe