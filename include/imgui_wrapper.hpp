#ifndef IMGUI_WRAPPER_HPP
#define IMGUI_WRAPPER_HPP

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <imgui_internal.h>
#include <string>

class GLFWwindow {};

class IMGUIWrapper {
public:
  bool init(GLFWwindow *window);
  void shutdown();
  void showDemoWindow();
  void newFrame();
  void finishFrame();
  void setWindowPos(std::string title, int x, int y);
  void updateDimensions();
  void keepWindowInBounds(const char *windowName);

private:
  int m_display_w, m_display_h;
};

#endif