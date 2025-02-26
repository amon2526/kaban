#include <array>
#include <board.hpp>
#include <cstdint>
#include <cstring>
#include <error_handler.hpp>
#include <sstream>
#include <string>

bool Bitboard::isSet(Square square) const {
  return (_value & (1ULL << square)) != 0;
};

void Bitboard::set(Square square) { _value |= (1ULL << square); }

void Bitboard::unset(Square square) { _value &= (1ULL << square); }

void Board::setFEN(std::string fen) {
  std::stringstream ss(fen);
  std::string argument;
  size_t argument_index = 0;
  while (std::getline(ss, argument, ' ')) {
    switch (argument_index) {
    case 0: {
      std::pair<uint8_t, uint8_t> boardSquarePosition = {7, 0};
      for (char c : argument) {
        if (c == '/') {
          boardSquarePosition.first--;
          boardSquarePosition.second = 0;
        } else if (isdigit(c)) {
          boardSquarePosition.second = boardSquarePosition.second + (c - '0');
        } else {
          setPiece((Square)(boardSquarePosition.first*8+boardSquarePosition.second), FENtoPiece.at(c));
          boardSquarePosition.second++;
        }
      }
      break;
    }

    default:
      break;
    }
    argument_index++;
  }
}

void Board::setPiece(Square square, Piece piece) {
  if (piece == EMPTY)
    return;

  if (piece / 8 == 0) {
    m_white_bitboards[(piece - 1)].set(square);
    m_white_bitboards[OCCUPIED].set(square);
  } else {
    m_black_bitboards[(piece - 9)].set(square);
    m_black_bitboards[OCCUPIED].set(square);
  }
  m_occupied.set(square);
}

void Board::unsetPiece(Square square) {
  for (int i = 0; i < 7; i++) {
    m_white_bitboards[i].unset(square);
    m_black_bitboards[i].unset(square);
  }
  m_occupied.unset(square);
}

Piece Board::getPiece(Square square) const {
  if (square != SQ_NONE) {
    if (m_white_bitboards[PAWNS].isSet(square))
      return WPawn;
    else if (m_white_bitboards[KNIGHTS].isSet(square))
      return WKnight;
    else if (m_white_bitboards[BISHOPS].isSet(square))
      return WBishop;
    else if (m_white_bitboards[ROOKS].isSet(square))
      return WRook;
    else if (m_white_bitboards[QUEENS].isSet(square))
      return WQueen;
    else if (m_white_bitboards[KINGS].isSet(square))
      return WKing;
    else if (m_black_bitboards[PAWNS].isSet(square))
      return BPawn;
    else if (m_black_bitboards[KNIGHTS].isSet(square))
      return BKnight;
    else if (m_black_bitboards[BISHOPS].isSet(square))
      return BBishop;
    else if (m_black_bitboards[ROOKS].isSet(square))
      return BRook;
    else if (m_black_bitboards[QUEENS].isSet(square))
      return BQueen;
    else if (m_black_bitboards[KINGS].isSet(square))
      return BKing;
  }
  return EMPTY;
}

std::array<std::array<Piece, 8>, 8> Board::getBoard() const {
  std::array<std::array<Piece, 8>, 8> board;
  for (uint8_t row = 0; row < 8; row++) {
    for (uint8_t col = 0; col < 8; col++) {
      board[row][col] = getPiece((Square)(row*8+col));
    }
  }
  return board;
}