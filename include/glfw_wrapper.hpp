#ifndef GLFW_WRAPPER_HPP
#define GLFW_WRAPPER_HPP

#include <GLFW/glfw3.h>

class GLFWWrapper {
public:
  GLFWWrapper() = default;
  ~GLFWWrapper() = default;
  bool init(int width, int height, const char *title, bool useVsync = false);
  void shutdown();
  bool windowShouldClose();
  void setWindowShouldClose(bool value);
  void updateDimensions();
  double getTime();
  void newFrame();
  void finishFrame();
  void fillFrame(double r, double g, double b, double a);
  int getWidth() const { return m_display_w; };
  int getHeight() const { return m_display_h; };
  GLFWwindow *getWindow() const;

private:
  GLFWwindow *m_window;
  GLFWmonitor *m_monitor;
  const GLFWvidmode *m_mode;

  int m_display_w, m_display_h;
};

#endif