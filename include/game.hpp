#ifndef GAME_HPP
#define GAME_HPP

#include <board.hpp>
#include <imgui.h>

enum Turn { WHITE, BLACK };

struct GameState {
  Turn turn;
  Square selectedPiece;
  Square attachedPiece;
  char *plainBoard;
};

class Game {
public:
  Game();
  ~Game();

  const GameState &getGameState();

  void loadFEN(std::string fen);
  void updateGameState();
  void test() {
    m_turn = (Turn)((m_turn + 1) % 2);
  }
  void holdPiece(Square square);
  void releasePiece(Square square);

private:
  Turn getTurn();
  char *getPlainBoard();
  void setPlainBoard(char *board);
  GameState m_gameState;
  Board m_board;
  Turn m_turn = WHITE;
  Square m_attachedPiece = SQ_NONE;
  Square m_selectedPiece = SQ_NONE;
};

#endif