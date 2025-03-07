#ifndef GAME_HPP
#define GAME_HPP

#include <position.hpp>
#include <cstdint>
#include <imgui.h>
#include <string>
#include <vector>

// Extracted constant for the default FEN string
constexpr auto DEFAULT_FEN = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

class Game {
public:
    // Pass FEN string by const reference to avoid unnecessary copies
    void setFEN(const std::string &fen);

    // Improved method names for better clarity
    Turn getTurn() const { return m_position.getTurn(); }
    bool isHoldingPiece() const { return m_holdingPiece; }
    Square getSelectedSquare() const { return m_selectedSquare; }

    const std::array<std::array<Piece, 8>, 8> &getBoardMatrix();

    const std::vector<Move> &getPossibleMoves();

    int countMoves(uint8_t depth);

    void holdPiece(int index);

    void releasePiecee(int index);

private:
    Position m_position;

    // Renamed variables to make them more descriptive
    bool m_holdingPiece = false;
    Square m_selectedSquare = SQ_NONE;
};

#endif