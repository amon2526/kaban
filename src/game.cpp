#include <cstdint>
#include <game.hpp>
#include <buffer.hpp>

#include <string>

void Game::setFEN(std::string fen) { m_position.setFEN(fen); }

std::array<std::array<Piece, 8>, 8> Game::getBoard() const {
  return m_position.getBoard();
}

void Game::holdPiece(int index) {
  if (m_position.getPiece((Square)index) == EMPTY) {
    m_selectedPiece = SQ_NONE;
  } else {
    m_selectedPiece = (Square)index;
    m_isHoldingPiece = true;
  }
}

void Game::releasePiece(int index) { m_isHoldingPiece = false; }

int Game::countMoves(uint8_t depth) {
  if (!depth) return 1;
  int totalMoves = 0;
  m_moveMap.AddArray();
  int numberOfMoves = 0;//GenerateMoveMap();
  if (depth == 1) {
    m_moveMap.PopArray();
    return numberOfMoves;
  }
  for (int i = 0; i < numberOfMoves; i++) {
    m_position.makeMove(m_moveMap[i]);
    totalMoves += countMoves(depth - 1);
    m_position.unmakeMove();
  }
  m_moveMap.PopArray();
  return totalMoves;
};