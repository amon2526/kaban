#include "types.hpp"
#include <array>
#include <game.hpp>
#include <dynamic_array.hpp>

#include <string>

void Game::setFEN(std::string fen) { m_position.setFEN(fen); }

void Game::holdPiece(int index) {
  if (m_position.getPiece((Square)index) == EMPTY) {
    m_selectedPiece = SQ_NONE;
  } else {
    m_selectedPiece = (Square)index;
    m_isHoldingPiece = true;
  }
}

void Game::releasePiece(int index) { m_isHoldingPiece = false; }

const std::array<std::array<Piece, 8>, 8> &Game::getMatrixBoard() {
  return m_position.getMatrixBoard();
}

const std::vector<Move> &Game::getPossibleMoves() {
  return m_position.getPossibleMoves();
}


