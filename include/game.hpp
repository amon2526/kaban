#ifndef GAME_HPP
#define GAME_HPP

#include <buffer.hpp>
#include <array>
#include <position.hpp>
#include <cstdint>
#include <imgui.h>
#include <string>


class Game {
public:
  void setFEN(std::string fen);
  void test() { m_turn = (Turn)((m_turn + 1) % 2); }

  std::array<std::array<Piece, 8>, 8> getBoard() const;
  Turn getTurn() const { return m_turn; }
  bool getIsHoldingPiece() const { return m_isHoldingPiece; }
  Square getSelectedPiece() const { return m_selectedPiece; }

  int countMoves(uint8_t depth);

  void holdPiece(int index);
  void releasePiece(int index);

private:
  std::string m_plainBoard;
  bool m_isPlainBoardDirty = true;

  Position m_position;
  Buffer<Move, 10000> m_moveMap;
  
  Turn m_turn = White;
  
  bool m_isHoldingPiece = false;
  Square m_selectedPiece = SQ_NONE;
};

#endif