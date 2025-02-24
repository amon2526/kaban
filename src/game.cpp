#include "board.hpp"
#include <game.hpp>


Game::Game() {};
Game::~Game() {};

void Game::loadFEN(std::string fen) { m_board.loadFEN(fen); }

char *Game::getPlainBoard() { return m_board.getPlainBoard(); }

void Game::setPlainBoard(char *board) { m_board.setPlainBoard(board); }

void Game::holdPiece(Square square) {
    if (m_board.getPiece(square) == EMPTY) {
        m_selectedPiece = SQ_NONE;
    }
    else {
    m_selectedPiece = square;
    m_attachedPiece = square;
    }
}
void Game::releasePiece(Square square) {
    m_attachedPiece = SQ_NONE;
}

Turn Game::getTurn() {
    return m_turn;
}

void Game::updateGameState() {
    m_gameState.turn = getTurn();
    m_gameState.attachedPiece = m_attachedPiece;
    m_gameState.selectedPiece = m_selectedPiece;
    m_gameState.plainBoard = getPlainBoard();
}

const GameState& Game::getGameState() {
    updateGameState();
    return m_gameState;
}