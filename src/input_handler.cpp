
#include <game.hpp>
#include <imgui.h>
#include <imgui_internal.h>
#include <input_handler.hpp>
#include <layout_manager.hpp>

void InputHandler::update() { handleInput(); }

void InputHandler::handleInput() {
  if (!ImGui::GetCurrentContext()) {
    return;
  }
  Square pointedSquare = m_layoutManager->getBoardSquare(
      ImGui::GetMousePos().x, ImGui::GetMousePos().y);
  if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
    if (!m_prevLMB) {
      m_game->holdPiece(pointedSquare);
      m_prevLMB = true;
    }
  } else {
    if (m_prevLMB) {
      m_game->releasePiece(pointedSquare);
      m_prevLMB = false;
    }
  }

  if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
    if (!m_prevRMB) {
      m_game->holdPiece(pointedSquare);
      m_prevRMB = true;
    }
  } else {
    if (m_prevRMB) {
      m_game->releasePiece(pointedSquare);
      m_prevRMB = false;
    }
  }

  if (ImGui::IsKeyPressed(ImGuiKey_Q)) {
    m_renderer->shutdown();
  }
  if (ImGui::IsKeyPressed(ImGuiKey_X)) {
    m_game->test();
  }
  if (ImGui::IsKeyPressed(ImGuiKey_F)) {
    m_renderer->toggleDemoWindow();
  }
}
