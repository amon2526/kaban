#include <game.hpp>

Game::Game() {};
Game::~Game() {};

void Game::loadFEN(char *fen) {
    _board.loadFEN(fen);
}

char* Game::getPlainBoard() {
    return _board.getPlainBoard();
}