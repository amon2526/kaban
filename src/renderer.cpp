#include "layout_manager.hpp"
#include <GLFW/glfw3.h>
#include <error_handler.hpp>
#include <game.hpp>
#include <gl/gl.h>
#include <imgui.h>
#include <renderer.hpp>
#include <string>
#include <texture_loader.hpp>

bool Renderer::init(int height, const char *title) {
  int width = (float)5 * height / 3;

  m_layoutManager.defineSector("interface", 0, 0, ((float)2 / 5) * width,
                               height);
  m_layoutManager.defineSector("game", ((float)2 / 5) * width, 0,
                               ((float)3 / 5) * width, height);

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

  GameState gameState = m_game->getGameState();

  updateTime();

  newFrame();
  fillFrame();

  glClear(GL_COLOR_BUFFER_BIT);

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  glOrtho(0, 1000, 0, 600, -1, 1);

  ImGui::SetNextWindowSize(
      ImVec2(m_layoutManager.getSector("interface").width,
             m_layoutManager.getSector("interface").height));
  ImGui::SetNextWindowPos(ImVec2(m_layoutManager.getSector("interface").x,
                                 m_layoutManager.getSector("interface").y));
  ImGui::Begin("Game", nullptr,
               ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
                   ImGuiWindowFlags_NoCollapse);
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  ImGui::Text("Hello, welcome to the Kaban!");
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  if (ImGui::Button("Start a new game")) {
    if (m_game) {
      m_game->loadFEN(
          "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }
  }
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  ImGui::Separator();
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  ImGui::Text("Current turn: %s", gameState.turn == WHITE ? "White" : "Black");
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  std::string selectedPieceStr = "None";
  if (gameState.selectedPiece != SQ_NONE) {
    std::string ranks[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    int row = gameState.selectedPiece / 8;
    int col = gameState.selectedPiece % 8;
    selectedPieceStr = ranks[col] + std::to_string(8 - row);
  }
  ImGui::Text("Selected piece: %s", selectedPieceStr.c_str());
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  std::string attachedPieceStr = "None";
  if (gameState.attachedPiece != SQ_NONE) {
    std::string ranks[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    int row = gameState.attachedPiece / 8;
    int col = gameState.attachedPiece % 8;
    attachedPieceStr = ranks[col] + std::to_string(8 - row);
  }
  ImGui::Text("Attached piece: %s", attachedPieceStr.c_str());
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  ImGui::End();

  if (m_game) {
    drawGame(gameState);
  }

  if (m_showDemoWindow) {
    m_imgui.showDemoWindow();
    m_imgui.keepWindowInBounds("Dear ImGui Demo");
  }

  finishFrame();
}

void Renderer::shutdown() {
  m_imgui.shutdown();
  m_glfw.shutdown();
}

bool Renderer::windowShouldClose() { return m_glfw.windowShouldClose(); }

void Renderer::toggleDemoWindow() { m_showDemoWindow = !m_showDemoWindow; }

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

void Renderer::drawGame(const GameState &gameState) {
  glClear(GL_COLOR_BUFFER_BIT);

  Sector boardSector = m_layoutManager.getSector("game");
  int squareSize = boardSector.width / 8;

  for (int boardRow = 0; boardRow < 8; boardRow++) {
    for (int boardCol = 0; boardCol < 8; boardCol++) {
      int turnRow = (gameState.turn == WHITE) ? boardRow : 7 - boardRow;
      int turnCol = (gameState.turn == WHITE) ? boardCol : 7 - boardCol;

      bool isDark = ((turnRow + turnCol) % 2 == 0);

      int xPos = boardSector.x + turnCol * squareSize;
      int yPos = boardSector.y + turnRow * squareSize;

      float colorValue = isDark ? 0.2f : 0.8f;
      drawSquare(xPos, yPos, squareSize, squareSize, colorValue, colorValue,
                 colorValue);

      if ((7 -turnRow) * 8 + turnCol == gameState.selectedPiece) {
        drawSquare(xPos, yPos, squareSize, squareSize, 0, 1, 0);
      }

      int index = (7 - boardRow) * 8 + boardCol;
      char piece = gameState.plainBoard[index];

      if (piece != ' ') {
        drawImage(xPos, yPos, squareSize, squareSize, pieceTextures[piece]);
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

LayoutManager *Renderer::getLayoutManager() { return &m_layoutManager; }