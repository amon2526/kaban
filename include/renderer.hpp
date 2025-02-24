#ifndef RENDERER_HPP
#define RENDERER_HPP

#include "layout_manager.hpp"
#include <GLFW/glfw3.h>
#include <board.hpp>
#include <game.hpp>
#include <glfw_wrapper.hpp>
#include <imgui_wrapper.hpp>
#include <unordered_map>

class Renderer {
public:
  Renderer() = default;
  ~Renderer() = default;

  bool init(int height, const char *title);
  void shutdown();
  void updateSectors(int width, int height);

  void render();
  void updateTime();
  void newFrame();
  void fillFrame(double r = 0, double g = 0, double b = 0, double a = 1);
  void finishFrame();

  void toggleDemoWindow();
  bool windowShouldClose();
  void hookUpGame(Game *game);
  
  LayoutManager* getLayoutManager();

  bool loadTextures();
  void drawGame(const GameState &gameState);
  void drawSquare(int x, int y, int width, int height, float r, float g, float b);
  void drawImage(int x, int y, int width, int height, GLuint texture);

private:
  LayoutManager m_layoutManager;

  Game *m_game;
  GLFWwindow* window;
  GLFWWrapper m_glfw;
  IMGUIWrapper m_imgui;

  std::unordered_map<char, GLuint> pieceTextures;

  int m_lastTime = 0;
  int m_deltaTime = 0;
  int m_currentTime = 0;
  int m_menuWidth = 200;
  bool m_showDemoWindow = false;
};

#endif