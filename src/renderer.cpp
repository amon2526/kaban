#include <GLFW/glfw3.h>
#include <error_bus.hpp>
#include <renderer.hpp>

bool Renderer::initGraphics(int height, const char *title) {
  int width = calculateWindowWidth(height);
  if (!m_glfw.init(width, height, title) || !m_imgui.init(m_glfw.getWindow())) {
    shutdown();
    ErrorBus::getInstance().sendError(1, "Failed to init graphics");
    return false;
  }
  updateTime();

  return true;
};

void Renderer::render() {

  updateTime();

  newFrame();
  fillFrame();

  if (m_showDemoWindow) {
    m_imgui.showDemoWindow();
  }

  m_imgui.keepWindowInBounds("Dear ImGui Demo");

  if (ImGui::Begin("My Panel")) {
    ImGui::Text("This window cannot go outside!");
  }
  ImGui::End();


  // if (_game) {
  //   char *board = _game->getPlainBoard();
  // }

  finishFrame();
}

void Renderer::shutdown() {
  m_imgui.shutdown();
  m_glfw.shutdown();
}

bool Renderer::windowShouldClose() { return m_glfw.windowShouldClose(); }

void Renderer::toggleDemoWindow() { m_showDemoWindow = !m_showDemoWindow; }

int Renderer::calculateWindowWidth(int height) { return m_menuWidth + height; }

void Renderer::newFrame() {
  m_glfw.newFrame();
  m_imgui.newFrame();
}

void Renderer::finishFrame() {
  m_imgui.finishFrame();
  m_glfw.finishFrame();
}

void Renderer::updateTime() {
  currentTime = m_glfw.getTime();
  deltaTime = currentTime - lastTime;
  lastTime = currentTime;
}

void Renderer::fillFrame(double r, double g, double b, double a) {
  m_glfw.fillFrame(r, g, b, a);
}