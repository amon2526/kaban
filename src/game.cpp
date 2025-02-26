#include <game.hpp>

#include <string>

void Game::setFEN(std::string fen) { m_board.setFEN(fen); }

std::array<std::array<Piece, 8>, 8> Game::getBoard() const {
  return m_board.getBoard();
}

void Game::holdPiece(int index) {
  if (m_board.getPiece((Square)index) == EMPTY) {
    m_selectedPiece = SQ_NONE;
  } else {
    m_selectedPiece = (Square)index;
    m_isHoldingPiece = true;
  }
}

void Game::releasePiece(int index) { m_isHoldingPiece = false; }
