#include "GameState.hpp"
#include "Definitions.hpp"
#include "GameOverState.hpp"
#include "PauseState.hpp"
#include <iostream>
#include <sstream>

namespace TicTacToe {
GameState::GameState(GameDataRef data) : _data(data) {}

void GameState::Init() {
  gameState = STATE_PLAYING;
  turn = PLAYER_PIECE;
  ai = new AI(turn, _data);

  _data->assets.LoadTexture("Pause Button", PAUSE_BUTTON);
  _data->assets.LoadTexture("Grid Sprite", GRID_SPRITE_FILEPATH);
  _data->assets.LoadTexture("X Piece", X_PIECE_FILEPATH);
  _data->assets.LoadTexture("O Piece", O_PIECE_FILEPATH);
  _data->assets.LoadTexture("X Winning Piece", X_WINNING_PIECE_FILEPATH);
  _data->assets.LoadTexture("O Winning Piece", O_WINNING_PIECE_FILEPATH);

  _background.setTexture(_data->assets.GetTexture("Background"));
  _pauseButton.setTexture(_data->assets.GetTexture("Pause Button"));
  _gridSprite.setTexture(_data->assets.GetTexture("Grid Sprite"));

  _pauseButton.setPosition((_data->window.getSize().x) -
                               _pauseButton.getLocalBounds().width,
                           (_data->window.getSize().y));
  _gridSprite.setPosition(
      (SCREEN_WIDTH / 2) - (_gridSprite.getGlobalBounds().width / 2),
      (SCREEN_HEIGHT / 2) - (_gridSprite.getGlobalBounds().height / 2));

  InitGridPieces();

  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      gridArray[x][y] = EMPTY_PIECE;
    }
  }
}

void GameState::HandleInput() {
  sf::Event event;
  while (_data->window.pollEvent(event)) {
    if (sf::Event::Closed == event.type) {
      _data->window.close();
    }

    if (_data->input.IsSpriteClicked(_pauseButton, sf::Mouse::Left,
                                     _data->window)) {
      _data->machine.AddState(StateRef(new PauseState(_data)), false);
      std::cout << "Pause the game!" << std::endl;
    } else if (_data->input.IsSpriteClicked(_gridSprite, sf::Mouse::Left,
                                            _data->window)) {
      if (STATE_PLAYING == gameState) {
        CheckAndPlacePiece();
      }
    }
  }
}

void GameState::Update(float dt) {
  // need to add some animation
}

void GameState::Draw(float dt) {
  _data->window.clear(sf::Color::Red);
  _data->window.draw(_background);
  _data->window.draw(_pauseButton);
  _data->window.draw(_gridSprite);

  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      _data->window.draw(_gridPieces[x][y]);
    }
  }

  _data->window.display();
}

void GameState::InitGridPieces() {
  sf::Vector2u tempSpriteSize = _data->assets.GetTexture("X Piece").getSize();

  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      _gridPieces[x][y].setTexture(_data->assets.GetTexture("X Piece"));
      _gridPieces[x][y].setPosition(
          _gridSprite.getPosition().x + (tempSpriteSize.x * x) - 7,
          _gridSprite.getPosition().y + (tempSpriteSize.y * y) - 7);
      _gridPieces[x][y].setColor(sf::Color(255, 255, 255, 0));
    }
  }
}

void GameState::CheckAndPlacePiece() {
  sf::Vector2i touchPoint = _data->input.GetMousePosition(_data->window);
  sf::FloatRect gridSize = _gridSprite.getGlobalBounds();
  sf::Vector2f gapOutsideOfGrid =
      sf::Vector2f((SCREEN_WIDTH - gridSize.width) / 2,
                   (SCREEN_HEIGHT - gridSize.height) / 2);

  sf::Vector2f gridLocalTouchPos = sf::Vector2f(
      touchPoint.x - gapOutsideOfGrid.x, touchPoint.y - gapOutsideOfGrid.y);
  sf::Vector2f gridSectionSize =
      sf::Vector2f(gridSize.width / 3, gridSize.height / 3);

  // determine row & colum clicked
  int column, row;

  // first column
  if (gridLocalTouchPos.x < gridSectionSize.x)
    column = 1;
  else if (gridLocalTouchPos.x < gridSectionSize.x * 2)
    column = 2;
  else if (gridLocalTouchPos.x < gridSize.width)
    column = 3;

  // then row
  if (gridLocalTouchPos.y < gridSectionSize.y)
    row = 1;
  else if (gridLocalTouchPos.y < gridSectionSize.y * 2)
    row = 2;
  else if (gridLocalTouchPos.y < gridSize.height)
    row = 3;

  if (gridArray[column - 1][row - 1] == EMPTY_PIECE) {
    gridArray[column - 1][row - 1] = turn;
    if (PLAYER_PIECE == turn)
      _gridPieces[column - 1][row - 1].setTexture(
          _data->assets.GetTexture("X Piece"));
    CheckPlayerHasWon(turn);
  }
  _gridPieces[column - 1][row - 1].setColor(sf::Color(255, 255, 255, 255));
}

void GameState::CheckPlayerHasWon(int player) {
  Check3PiecesForMatch(0, 0, 1, 0, 2, 0, player);
  Check3PiecesForMatch(0, 1, 1, 1, 2, 1, player);
  Check3PiecesForMatch(0, 2, 1, 2, 2, 2, player);
  Check3PiecesForMatch(0, 0, 0, 1, 0, 2, player);
  Check3PiecesForMatch(1, 0, 1, 1, 1, 2, player);
  Check3PiecesForMatch(2, 0, 2, 1, 2, 2, player);
  Check3PiecesForMatch(0, 0, 1, 1, 2, 2, player);
  Check3PiecesForMatch(0, 2, 1, 1, 2, 0, player);

  // if above methods hasn't retured true
  if (STATE_WON != gameState) {
    gameState = STATE_AI_PLAYING;
    ai->PlacePiece(&gridArray, _gridPieces, &gameState);

    Check3PiecesForMatch(0, 0, 1, 0, 2, 0, AI_PIECE);
    Check3PiecesForMatch(0, 1, 1, 1, 2, 1, AI_PIECE);
    Check3PiecesForMatch(0, 2, 1, 2, 2, 2, AI_PIECE);
    Check3PiecesForMatch(0, 0, 0, 1, 0, 2, AI_PIECE);
    Check3PiecesForMatch(1, 0, 1, 1, 1, 2, AI_PIECE);
    Check3PiecesForMatch(2, 0, 2, 1, 2, 2, AI_PIECE);
    Check3PiecesForMatch(0, 0, 1, 1, 2, 2, AI_PIECE);
    Check3PiecesForMatch(0, 2, 1, 1, 2, 0, AI_PIECE);
  }

  int emptyNum = 9;
  for (int x = 0; x < 3; x++) {
    for (int y = 0; y < 3; y++) {
      if (EMPTY_PIECE != gridArray[x][y])
        emptyNum--;
    }
  }

  if (emptyNum == 0) {
    if (STATE_WON != gameState && STATE_LOSE != gameState) {
      gameState = STATE_DRAW;
    }
  }

  // show gameover state
  if (STATE_DRAW == gameState || STATE_LOSE == gameState ||
      STATE_WON == gameState) {
    // show gameover!
  }

  std::cout << gameState << std::endl;
}

void GameState::Check3PiecesForMatch(int x1, int y1, int x2, int y2, int x3,
                                     int y3, int pieceToCheck) {
  // if (STATE_LOSE != gameState && STATE_WON != gameState &&
  //   STATE_DRAW != gameState) {
  if (pieceToCheck == gridArray[x1][y1] && pieceToCheck == gridArray[x2][y2] &&
      pieceToCheck == gridArray[x3][y3]) {
    std::string winningPieceStr;

    if (O_PIECE == pieceToCheck) {
      winningPieceStr = "O Winning Piece";
    } else {
      winningPieceStr = "X Winning Piece";
    }

    _gridPieces[x1][y1].setTexture(_data->assets.GetTexture(winningPieceStr));
    _gridPieces[x2][y2].setTexture(_data->assets.GetTexture(winningPieceStr));
    _gridPieces[x3][y3].setTexture(_data->assets.GetTexture(winningPieceStr));

    if (PLAYER_PIECE == pieceToCheck) {
      gameState = STATE_WON;
    } else {
      gameState == STATE_LOSE;
    }
  }
  //}
}

} // namespace TicTacToe