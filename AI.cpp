#include "AI.hpp"
#include "Definitions.hpp"
#include <iostream>

using namespace std;

namespace TicTacToe {
AI::AI(int playerPiece, GameDataRef data) {
  _data = data;
  playerPiece = playerPiece;
  if (O_PIECE == playerPiece) {
    aiPiece = X_PIECE;
  } else {
    aiPiece = O_PIECE;
  }
  /// TODO: refactor in a diff method with population logic
  checkMatchVector.push_back({0, 2, 1, 2, 2, 2});
  checkMatchVector.push_back({0, 2, 0, 1, 0, 0});
  checkMatchVector.push_back({0, 2, 1, 1, 2, 0});
  checkMatchVector.push_back({2, 2, 1, 2, 0, 2});
  checkMatchVector.push_back({2, 2, 2, 1, 2, 0});
  checkMatchVector.push_back({2, 2, 1, 1, 0, 0});
  checkMatchVector.push_back({0, 0, 0, 1, 0, 2});
  checkMatchVector.push_back({0, 0, 1, 0, 2, 0});
  checkMatchVector.push_back({0, 0, 1, 1, 2, 2});
  checkMatchVector.push_back({2, 0, 2, 1, 2, 2});
  checkMatchVector.push_back({2, 0, 1, 0, 0, 0});
  checkMatchVector.push_back({2, 0, 1, 1, 0, 2});
  checkMatchVector.push_back({0, 1, 1, 1, 2, 1});
  checkMatchVector.push_back({1, 2, 1, 1, 1, 0});
  checkMatchVector.push_back({2, 1, 1, 1, 0, 1});
  checkMatchVector.push_back({1, 0, 1, 1, 1, 2});
  checkMatchVector.push_back({0, 1, 2, 1, 1, 1});
  checkMatchVector.push_back({1, 2, 1, 0, 1, 1});
  checkMatchVector.push_back({0, 2, 2, 0, 1, 1});
  checkMatchVector.push_back({2, 2, 0, 0, 1, 1});
  checkMatchVector.push_back({0, 2, 2, 2, 1, 2});
  checkMatchVector.push_back({0, 0, 2, 0, 1, 0});
  checkMatchVector.push_back({0, 2, 0, 0, 0, 1});
  checkMatchVector.push_back({2, 2, 2, 0, 2, 1});
}

void AI::PlacePiece(int (*gridArray)[3][3], sf::Sprite gridPieces[3][3],
                    int *gameState) {

  try {
    for (int i = 0; i < checkMatchVector.size(); i++) {
      CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], // x1,y1
                   checkMatchVector[i][2], checkMatchVector[i][3], // x2, y2
                   checkMatchVector[i][4], checkMatchVector[i][5],
                   AI_PIECE, // X, Y
                   gridArray, gridPieces);
    }

    for (int i = 0; i < checkMatchVector.size(); i++) {
      CheckSection(checkMatchVector[i][0], checkMatchVector[i][1], // x1,y1
                   checkMatchVector[i][2], checkMatchVector[i][3], // x2, y2
                   checkMatchVector[i][4], checkMatchVector[i][5],
                   PLAYER_PIECE, // X, Y
                   gridArray, gridPieces);
    }

    // center empty?
    CheckIfPieceIsEmpty(1, 1, gridArray, gridPieces);

    // corner empty?
    CheckIfPieceIsEmpty(0, 2, gridArray, gridPieces);
    CheckIfPieceIsEmpty(2, 2, gridArray, gridPieces);
    CheckIfPieceIsEmpty(0, 0, gridArray, gridPieces);
    CheckIfPieceIsEmpty(2, 0, gridArray, gridPieces);

    // other empty piece?
    CheckIfPieceIsEmpty(1, 2, gridArray, gridPieces);
    CheckIfPieceIsEmpty(0, 1, gridArray, gridPieces);
    CheckIfPieceIsEmpty(2, 1, gridArray, gridPieces);
    CheckIfPieceIsEmpty(1, 0, gridArray, gridPieces);

  } catch (int error) {
  }

  *gameState = STATE_PLAYING;
}

void AI::CheckSection(int x1, int y1, int x2, int y2, int X, int Y,
                      int pieceToCheck, int (*gridArray)[3][3],
                      sf::Sprite gridPieces[3][3]) {

  // check if 2 pieces match
  if ((*gridArray)[x1][y1] == pieceToCheck &&
      (*gridArray)[x2][y2] == pieceToCheck) {
    // third piece ?
    if (EMPTY_PIECE == (*gridArray)[X][Y]) {
      (*gridArray)[X][Y] = AI_PIECE;
      gridPieces[X][Y].setTexture(this->_data->assets.GetTexture("O Piece"));
      gridPieces[X][Y].setColor(sf::Color(255, 255, 255, 255));
      // break out of loop
      throw -1;
    }
  }
}

void AI::CheckIfPieceIsEmpty(int X, int Y, int (*gridArray)[3][3],
                             sf::Sprite gridPieces[3][3]) {
  if (EMPTY_PIECE == (*gridArray)[X][Y]) {
    (*gridArray)[X][Y] = AI_PIECE;
    gridPieces[X][Y].setTexture(this->_data->assets.GetTexture("O Piece"));
    gridPieces[X][Y].setColor(sf::Color(255, 255, 255, 255));
    throw -2;
  }
}
}; // namespace TicTacToe