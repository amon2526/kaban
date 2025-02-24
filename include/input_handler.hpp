#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <game.hpp>
#include <renderer.hpp>
#include <GLFW/glfw3.h>

class InputHandler {
public:
  InputHandler(Renderer* renderer, Game* game) : m_renderer(renderer), m_game(game) {};
  void update();
  void handleInput();
private:
Renderer* m_renderer;
Game* m_game;

bool m_prevLMB = false;
bool m_prevRMB = false;
};

#endif
