#ifndef GAME_HPP
#define GAME_HPP

#include <board.hpp>
#include <imgui.h>

class Game {
public:
  Game();
  ~Game();
  void loadFEN(std::string fen);
  char *getPlainBoard();
  void setPlainBoard(char *board);
  void processMouseButtonDown(ImGuiMouseButton button);
  void processMouseButtonUp(ImGuiMouseButton button);
private:
  Board _board;
};

#endif