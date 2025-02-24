
#include <imgui.h>
#include <imgui_internal.h>
#include <input_handler.hpp>
#include <game.hpp>


void InputHandler::update() { handleInput(); }

void InputHandler::handleInput() {
  if (!ImGui::GetCurrentContext()) {
    return;
  }
  if (ImGui::IsMouseDown(ImGuiMouseButton_Left)) {
    if (!m_prevLMB) {
      m_game->processMouseButtonDown(ImGuiMouseButton_Left);
      m_prevLMB = true;
    }
  }
  else {
    if (m_prevLMB) {
      m_game->processMouseButtonUp(ImGuiMouseButton_Left);
      m_prevLMB = false;
    }
  }
  
  if (ImGui::IsMouseDown(ImGuiMouseButton_Right)) {
    if (!m_prevRMB) {
      m_game->processMouseButtonDown(ImGuiMouseButton_Right);
      m_prevRMB = true;
    }
  }
  else {
    if (m_prevRMB) {
      m_game->processMouseButtonUp(ImGuiMouseButton_Right);
      m_prevRMB = false;
    }
  }
  


  if (ImGui::IsKeyPressed(ImGuiKey_Q)) {
    m_renderer->shutdown();
  }
}
