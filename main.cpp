#include "Definitions.hpp"
#include "Game.hpp"
#include <iostream>

int main() {
  TicTacToe::Game(SCREEN_WIDTH,SCREEN_HEIGHT,std::string("TicTacToe"));
  return EXIT_SUCCESS;
}