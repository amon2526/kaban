#ifndef TYPES_HPP
#define TYPES_HPP

#include <cstdint>
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
  WPAWN, WKNIGHT, WBISHOP, WROOK, WQUEEN, WKING, 
  BPAWN, BKNIGHT, BBISHOP, BROOK, BQUEEN, BKING,
  EMPTY
};
  
enum File : uint8_t {
  F_A, F_B, F_C, F_D, F_E, F_F, F_G, F_H, F_NONE
};
  
enum Rank : uint8_t {
  R_1, R_2, R_3, R_4, R_5, R_6, R_7, R_8, R_NONE
};
  
enum CastlingRights : uint8_t {
  NO_CASTLING,
  WHITE_OO,
  WHITE_OOO = WHITE_OO << 1,
  BLACK_OO = WHITE_OO << 2,
  BLACK_OOO = WHITE_OO << 3,

  KING_SIDE = WHITE_OO | BLACK_OO,
  QUEEN_SIDE = WHITE_OOO | BLACK_OOO,
  WHITE_CASTLING = WHITE_OO | WHITE_OOO,
  BLACK_CASTLING = BLACK_OO | BLACK_OOO,
  ANY_CASTLING = WHITE_CASTLING | BLACK_CASTLING
};
  
enum Turn : bool { WHITE, BLACK };
  
static const std::unordered_map<char, Piece> FENtoPiece = {
  {'P', WPAWN},   {'N', WKNIGHT}, {'B', WBISHOP}, {'R', WROOK},
  {'Q', WQUEEN},  {'K', WKING},   {'p', BPAWN},   {'n', BKNIGHT},
  {'b', BBISHOP}, {'r', BROOK},   {'q', BQUEEN},  {'k', BKING}};
static const std::unordered_map<Piece, char> PieceToFEN = {
  {WPAWN, 'P'},   {WKNIGHT, 'N'}, {WBISHOP, 'B'}, {WROOK, 'R'},
  {WQUEEN, 'Q'},  {WKING, 'K'},   {BPAWN, 'p'},   {BKNIGHT, 'n'},
  {BBISHOP, 'b'}, {BROOK, 'r'},   {BQUEEN, 'q'},  {BKING, 'k'}};

// clang-format on

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

#endif