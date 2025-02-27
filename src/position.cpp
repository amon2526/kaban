#include <position.hpp>

#include <array>
#include <cstdint>
#include <error_handler.hpp>
#include <sstream>
#include <string>

bool Bitboard::isSet(uint8_t square) const {
  return (_value & (1ULL << square)) != 0;
};

void Bitboard::set(uint8_t square) { _value |= (1ULL << square); }

void Bitboard::unset(uint8_t square) { _value &= (1ULL << square); }

void Position::setFEN(std::string fen) {
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
          setPiece((Square)(boardSquarePosition.first * 8 +
                            boardSquarePosition.second),
                   FENtoPiece.at(c));
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

void Position::setPiece(uint8_t destination, Piece piece) {
  if (piece == EMPTY)
    return;
  m_piece_bitboards[piece].set(destination);
  if (isWhite(piece))
    m_white_occupied.set(destination);
  else
    m_black_occupied.set(destination);
}

void Position::unsetPiece(uint8_t square) {
  if (square == SQ_NONE)
    return;
  const uint64_t mask = ~(1ULL << square);
  for (uint8_t i = 0; i < 12; i++) {
    m_piece_bitboards[i]._value &= mask;
  }
  m_white_occupied._value &= mask;
  m_black_occupied._value &= mask;
  m_occupied._value &= mask;
}

Piece Position::getPiece(uint8_t source) const {
  if (source == SQ_NONE)
    return EMPTY;
  const uint64_t mask = (1ULL << source);
  for (uint8_t i = 0; i < 12; i++) {
    if ((m_piece_bitboards[i]._value & mask) != 0)
      return (Piece)i;
  }
  return EMPTY;
}

std::array<std::array<Piece, 8>, 8> Position::getBoard() const {
  std::array<std::array<Piece, 8>, 8> board;
  for (uint8_t row = 0; row < 8; row++) {
    for (uint8_t col = 0; col < 8; col++) {
      board[row][col] = getPiece((Square)(row * 8 + col));
    }
  }
  return board;
}

void Position::makeMove(const Move &move) {
  setPiece(move.to, getPiece(move.from));
  unsetPiece(move.from);
  //m_Turn = !m_Turn;
}

void Position::unmakeMove() {}