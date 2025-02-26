#ifndef GAME_HPP
#define GAME_HPP

#include <array>
#include <board.hpp>
#include <imgui.h>
#include <string>

enum Turn { WHITE, BLACK };

class Game {
public:
  void setFEN(std::string fen);
  void test() { m_turn = (Turn)((m_turn + 1) % 2); }

  std::array<std::array<Piece, 8>, 8> getBoard() const;
  Turn getTurn() const { return m_turn; }
  bool getIsHoldingPiece() const { return m_isHoldingPiece; }
  Square getSelectedPiece() const { return m_selectedPiece; }

  void holdPiece(int index);
  void releasePiece(int index);

private:
  std::string m_plainBoard;
  bool m_isPlainBoardDirty = true;

  Board m_board;

  Turn m_turn = WHITE;
  bool m_isHoldingPiece = false;
  Square m_selectedPiece = SQ_NONE;
};

#endif