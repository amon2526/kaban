#include <cmath>
#include <iterator>
#include <renderer.hpp>

#include "position.hpp"
#include "types.hpp"
#include <GLFW/glfw3.h>
#include <cstdint>
#include <error_handler.hpp>
#include <game.hpp>
#include <gl/gl.h>
#include <imgui.h>
#include <iostream>
#include <layout_manager.hpp>
#include <navigation.hpp>
#include <string>
#include <texture_loader.hpp>
#include <utility>
#include <windows.h>

bool Renderer::init(int height, const char *title) {
  int width = (float)5 * height / 3;

  m_layoutManager.defineSector("interface", 0, 0, ((float)2 / 5) * width,
                               height);
  m_layoutManager.defineSector("game", ((float)2 / 5) * width, 0,
                               ((float)3 / 5) * width, height);

  if (!m_glfw.init(width, height, title, true) ||
      !m_imgui.init(m_glfw.getWindow()) || !loadTextures()) {
    shutdown();
    handleError(1, "Failed to init graphics");
    return false;
  }

  updateTime();

  return true;
};

void Renderer::render() {

  updateTime();
  updateMousePosition();

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
      m_game->setFEN(
          "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    }
  }
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  ImGui::Separator();
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  ImGui::Text("Current turn: %s",
              m_game->getTurn() == WHITE ? "White" : "Black");
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  std::string selectedPieceStr = "None";
  if (m_game->getSelectedPiece() != SQ_NONE) {
    std::string ranks[] = {"A", "B", "C", "D", "E", "F", "G", "H"};
    int row = m_game->getSelectedPiece() / 8;
    int col = m_game->getSelectedPiece() % 8;
    selectedPieceStr = ranks[col] + std::to_string(8 - row);
  }
  ImGui::Text("Selected piece: %s", selectedPieceStr.c_str());
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  std::string isHoldingPieceText = "";
  if (m_game->getIsHoldingPiece()) {
    isHoldingPieceText = "true";
  } else {
    isHoldingPieceText = "false";
  }
  ImGui::Text("Is holding a piece: %s", isHoldingPieceText.c_str());
  ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 10);
  ImGui::End();

  if (m_game) {
    drawGame();
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
  for (uint8_t i = 0; i < 12; i++) {
    char name = PieceToFEN.at((Piece)i);
    GLuint texture;
    if (isWhite((Piece)i)) {
      texture = TextureLoader::loadTexture(path + name + "b.png");
    } else {
      texture = TextureLoader::loadTexture(path + name + "w.png");
    }
    if (texture == 0)
      return false;
    pieceTextures[(Piece)i] = texture;
  }
  return true;
}

double euclidean_distance(const std::pair<double, double>& a, const std::pair<double, double>& b) {
  return std::sqrt((a.first - b.first) * (a.first - b.first) + (a.second - b.second) * (a.second - b.second));
}

void Renderer::drawGame() {
  glClear(GL_COLOR_BUFFER_BIT);

  const Sector &boardSector = m_layoutManager.getSector("game");
  int squareSize = boardSector.width >> 3;
  auto board = m_game->getMatrixBoard();

  for (uint8_t square = 0; square < 64; square++) {

    int yPos = boardSector.y + (square >> 3) * squareSize;
    int xPos = boardSector.x + (square % 8) * squareSize;

    uint8_t relativeSquare = getTurnSquare((Square)square, m_game->getTurn());

    bool isDark = ((square >> 3) + (square % 8)) % 2 == 0;

    float colorValue = isDark ? 0.3f : 0.7f;

    drawSquare(xPos, yPos, squareSize, squareSize, colorValue, colorValue,
               colorValue);

    if (relativeSquare == m_game->getSelectedPiece()) {
      drawSquare(xPos, yPos, squareSize, squareSize, 0.7, 0.3, 0.3);
    }

    Piece piece = board[(relativeSquare >> 3)][(relativeSquare % 8)];

    if (piece != EMPTY && !((relativeSquare == m_game->getSelectedPiece() &&
                             m_game->getIsHoldingPiece()))) {
      drawPiece(xPos, yPos, squareSize, squareSize, 4, pieceTextures[piece]);
    }
    if (m_game->getIsHoldingPiece()) {
      std::pair<double, double> holdingPiecePos;
      double lerpSpeed = 0.5f * m_deltaTime;
      int halfSquareSize = squareSize >> 1;

      if (!m_wasHoldingPiece) {
        m_wasHoldingPiece = true;
        holdingPiecePos.first = m_mousePos.first - halfSquareSize;
        holdingPiecePos.second =
            (m_glfw.getHeight() - m_mousePos.second) - halfSquareSize;
      } else {
        double distance = euclidean_distance(m_lastHoldedPiecePosition, m_mousePos);
        if (distance < 0.1f) { 
          holdingPiecePos = m_lastHoldedPiecePosition;
        }
        else {
          holdingPiecePos.first = m_lastHoldedPiecePosition.first + (m_mousePos.first - halfSquareSize - m_lastHoldedPiecePosition.first) * lerpSpeed;
          holdingPiecePos.second = m_lastHoldedPiecePosition.second + ((m_glfw.getHeight() - m_mousePos.second) - halfSquareSize - m_lastHoldedPiecePosition.second) * lerpSpeed;
        }
      }

      uint8_t selectedPiece = m_game->getSelectedPiece();
      drawPiece(holdingPiecePos.first, holdingPiecePos.second, squareSize,
                squareSize, 4,
                pieceTextures[board[selectedPiece >> 3][selectedPiece % 8]]);

      m_lastHoldedPiecePosition = holdingPiecePos;
    } else {
      m_wasHoldingPiece = false;
    }
  }
}

void Renderer::drawSquare(int x, int y, int width, int height, float r, float g,
                          float b) {
  glColor3f(r, g, b);
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

void Renderer::drawPiece(int x, int y, int width, int height, int padding,
                         GLuint texture) {
  drawImage(x + padding, y + padding, width - 2 * padding, height - 2 * padding,
            texture);
}