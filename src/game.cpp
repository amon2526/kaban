#include <game.hpp>

Game::Game() {};
Game::~Game() {};

void Game::loadFEN(std::string fen) { _board.loadFEN(fen); }

char *Game::getPlainBoard() { return _board.getPlainBoard(); }

void Game::setPlainBoard(char *board) { _board.setPlainBoard(board); }

void Game::processMouseButtonDown(ImGuiMouseButton button) {}
void Game::processMouseButtonUp(ImGuiMouseButton button) {}