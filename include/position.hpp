#ifndef POSITION_HPP
#define POSITION_HPP

#include "buffer.hpp"
#include <array>
#include <cstdint>
#include <string>
#include <unordered_map>

// clang-format off

enum Square : uint8_t {
  A1 = 0, B1, C1, D1, E1, F1, G1, H1, 
  A2, B2, C2, D2, E2, F2, G2, H2, 
  A3, B3, C3, D3, E3, F3, G3, H3, 
  A4, B4, C4, D4, E4, F4, G4, H4, 
  A5, B5, C5, D5, E5, F5, G5, H5, 
  A6, B6, C6, D6, E6, F6, G6, H6, 
  A7, B7, C7, D7, E7, F7, G7, H7, 
  A8, B8, C8, D8, E8, F8, G8, H8,
  SQ_NONE = 64
};

enum Piece : uint8_t {
  WPawn, WKnight, WBishop, WRook, WQueen, WKing, 
  BPawn, BKnight, BBishop, BRook, BQueen, BKing,
  EMPTY
};

enum File : uint8_t {
  F_A, F_B, F_C, F_D, F_E, F_F, F_G, F_H, F_NONE
};

enum Rank : uint8_t {
  R_1, R_2, R_3, R_4, R_5, R_6, R_7, R_8, R_NONE
};

struct Move {
  uint8_t from : 6;
  uint8_t to : 6;
  uint8_t replaced : 4;
  uint8_t promotion : 3;
  uint8_t castling : 3;
  uint8_t enPassant : 1;

  Move()
      : from(0), to(0), replaced(0), promotion(0), castling(0), enPassant(0) {}
  Move(uint8_t from, uint8_t to, uint8_t replaced, uint8_t promotion = 0,
       uint8_t castling = 0, uint8_t enPassant = 0)
      : from(from), to(to), replaced(replaced), promotion(promotion),
        castling(castling), enPassant(enPassant) {}
};

enum CastlingRights : uint8_t {
  WhiteKingSide = 1,
  WhiteQueenSide = 2,
  BlackKingSide = 4,
  BlackQueenSide = 8
};

enum Turn : bool { White, Black };

// clang-format on


static const std::unordered_map<char, Piece> FENtoPiece = {
  {'P', WPawn},   {'N', WKnight}, {'B', WBishop}, {'R', WRook},
  {'Q', WQueen},  {'K', WKing},   {'p', BPawn},   {'n', BKnight},
  {'b', BBishop}, {'r', BRook},   {'q', BQueen},  {'k', BKing}};
static const std::unordered_map<Piece, char> PieceToFEN = {
  {WPawn, 'P'},   {WKnight, 'N'}, {WBishop, 'B'}, {WRook, 'R'},
  {WQueen, 'Q'},  {WKing, 'K'},   {BPawn, 'p'},   {BKnight, 'n'},
  {BBishop, 'b'}, {BRook, 'r'},   {BQueen, 'q'},  {BKing, 'k'}};

inline bool isWhite(Piece piece) {
  if ((uint8_t)piece <= 5)
    return true;
  return false;
}

struct GameState {
  Turn turn;
  CastlingRights castlingRights;
  bool enPassantPossibleFile;
};

class Bitboard {
public:
  uint64_t _value;

  Bitboard() : _value(0ULL) {}
  Bitboard(uint64_t value) : _value(value) {}

  bool isSet(uint8_t square) const;
  void set(uint8_t square);
  void unset(uint8_t square);
};

class Position {
public:
  void setFEN(std::string fen);

  void setPiece(uint8_t square, Piece piece);
  void unsetPiece(uint8_t square);
  Piece getPiece(uint8_t square) const;
  void makeMove(const Move &move);
  void unmakeMove();

  std::array<std::array<Piece, 8>, 8> getBoard() const;

private:
  Bitboard m_piece_bitboards[12];
  Bitboard m_white_occupied;
  Bitboard m_black_occupied;
  Bitboard m_occupied;
  
  Buffer<Move, 100> m_previousMoves;
};

#endif