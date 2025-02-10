#ifndef BOARD_HPP
#define BOARD_HPP

#include <cstdint>
#include <cctype>
#include <cstring>
#include <sstream>
#include <iostream>
#include <unordered_map>
#include <cmath>
#include <userio.hpp>

enum Square : uint8_t
{
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

enum Piece : uint8_t
{
    EMPTY = 0,
    WPawn = 1, WKnight, WBishop, WRook, WQueen, WKing, 
    BPawn = 9, BKnight, BBishop, BRook, BQueen, BKing
};

enum BitboardIndex : uint8_t
{
    PAWNS = 0,
    KNIGHTS,
    BISHOPS,
    ROOKS,
    QUEENS,
    KINGS,
    OCCUPIED
};

static const std::unordered_map<char, Piece> FENtoPiece = {{'P', WPawn}, {'N', WKnight}, {'B', WBishop}, {'R', WRook}, {'Q', WQueen}, {'K', WKing}, {'p', BPawn}, {'n', BKnight}, {'b', BBishop}, {'r', BRook}, {'q', BQueen}, {'k', BKing}};
static const std::unordered_map<Piece, char> PieceToFEN = {{WPawn, 'P'}, {WKnight, 'N'}, {WBishop, 'B'}, {WRook, 'R'}, {WQueen, 'Q'}, {WKing, 'K'}, {BPawn, 'p'}, {BKnight, 'n'}, {BBishop, 'b'}, {BRook, 'r'}, {BQueen, 'q'}, {BKing, 'k'}};

class Bitboard
{
public:
    uint64_t _value;

    Bitboard() : _value(0ULL) {}
    Bitboard(uint64_t value) : _value(value) {}

    bool isSet(Square square) const;
    void set(Square square);
    void unset(Square square);
};

class Board
{
public:
    Board(){};
    ~Board(){};
    void loadFEN(std::string fen);
    void set(Square square, Piece piece);
    void unset(Square square);
    
    void setPlainBoard(char* board);
    char* getPlainBoard();

private:
    Bitboard _white_bitboards[7];
    Bitboard _black_bitboards[7];
    Bitboard _occupied;
    bool _white_to_move;
};

#endif