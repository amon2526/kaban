
#include "game.hpp"
#include <GLFW/glfw3.h>
#include <error_handler.hpp>
#include <gl/gl.h>
#include <imgui.h>
#include <renderer.hpp>
#include <string>
#include <texture_loader.hpp>

bool Renderer::init(int height, const char *title) {
  int width = (float)5 * height / 3;

  updateSectors(width, height);

  if (!m_glfw.init(width, height, title) || !m_imgui.init(m_glfw.getWindow()) ||
      !loadTextures()) {
    shutdown();
    handleError(1, "Failed to init graphics");
    return false;
  }

  updateTime();

  return true;
};

void Renderer::render() {
  
  updateTime();
  
  newFrame();
  fillFrame();

  glClear(GL_COLOR_BUFFER_BIT);

  // Set up an orthographic projection
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1000, 0, 600, -1, 1);

  drawSquare(100, 100, 200, 200, 1, 1, 1);
  
  if (m_showDemoWindow) {
    m_imgui.showDemoWindow();
    m_imgui.keepWindowInBounds("Dear ImGui Demo");
  }

  if (m_game) {
    char *board = m_game->getPlainBoard();

    drawBoard(std::string(board), sectorDivision[1]);
  }

  finishFrame();
}

void Renderer::shutdown() {
  m_imgui.shutdown();
  m_glfw.shutdown();
}

bool Renderer::windowShouldClose() { return m_glfw.windowShouldClose(); }

void Renderer::toggleDemoWindow() { m_showDemoWindow = !m_showDemoWindow; }

void Renderer::updateSectors(int width, int height) {
  sectorDivision[0].x = 0;
  sectorDivision[0].y = 0;
  sectorDivision[0].width = ((float)2 / 5) * width;
  sectorDivision[0].height = height;

  sectorDivision[1].x = ((float)2 / 5) * width;
  sectorDivision[1].y = 0;
  sectorDivision[1].width = ((float)3 / 5) * width;
  sectorDivision[1].height = height;
}

void Renderer::newFrame() {
  m_glfw.newFrame();
  m_imgui.newFrame();
}

void Renderer::finishFrame() {
  m_imgui.finishFrame();
  m_glfw.finishFrame();
}

void Renderer::updateTime() {
  m_currentTime = m_glfw.getTime();
  m_deltaTime = m_currentTime - m_lastTime;
  m_lastTime = m_currentTime;
}

void Renderer::fillFrame(double r, double g, double b, double a) {
  m_glfw.fillFrame(r, g, b, a);
}

void Renderer::hookUpGame(Game *game) { m_game = game; }

bool Renderer::loadTextures() {
  std::string path = "resources/";
  const char pieces[] = {'p', 'P', 'n', 'N', 'b', 'B',
                         'r', 'R', 'q', 'Q', 'k', 'K'};
  for (int i = 0; i < sizeof(pieces) / sizeof(pieces[0]); i += 2) {
    GLuint texture = TextureLoader::loadTexture(path + pieces[i] + "b.png");
    if (texture == 0) {
      return false;
    }
    pieceTextures[pieces[i]] = texture;
    texture = TextureLoader::loadTexture(path + pieces[i] + "w.png");
    if (texture == 0) {
      return false;
    }
    pieceTextures[pieces[i + 1]] = texture;
  }

  return true;
}

void Renderer::drawBoard(const std::string &board, const Sector &sector) {
  glClear(GL_COLOR_BUFFER_BIT);

  int squareSize = sector.width / 8;

  drawSquare(100, 100, 200, 200, 1, 1, 1);

  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      bool isDark = (row + col) % 2 != 0;
      drawSquare(row * squareSize + sector.x, col * squareSize, squareSize,
                 squareSize, isDark ? 0.2 : 0.8, isDark ? 0.2 : 0.8,
                 isDark ? 0.2 : 0.8);
      char piece = board[row * 8 + col];
      if (piece != ' ') {
        drawImage(row * squareSize + sector.x, col * squareSize, squareSize,
                  squareSize, pieceTextures[piece]);
      }
    }
  }
}

void Renderer::drawSquare(int x, int y, int width, int height, float r, float g,
                          float b) {
  glColor3f(r, g, b); // Ensure values are in [0.0, 1.0]
  glBegin(GL_QUADS);
  glVertex2f(x, y);
  glVertex2f(x + width, y);
  glVertex2f(x + width, y + height);
  glVertex2f(x, y + height);
  glEnd();
}

void Renderer::drawImage(int x, int y, int width, int height, GLuint texture) {
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  glColor3f(1, 1, 1);
  glBegin(GL_QUADS);
  glTexCoord2f(0, 0);
  glVertex2f(x, y);
  glTexCoord2f(1, 0);
  glVertex2f(x + width, y);
  glTexCoord2f(1, 1);
  glVertex2f(x + width, y + height);
  glTexCoord2f(0, 1);
  glVertex2f(x, y + height);
  glEnd();
  glDisable(GL_TEXTURE_2D);
}
