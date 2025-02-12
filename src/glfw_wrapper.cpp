#include <GLFW/glfw3.h>
#include <error_bus.hpp>
#include <glfw_wrapper.hpp>
#include <imgui.h>
#include <input_bus.hpp>

bool GLFWWrapper::init(int width, int height, const char *title) {
  glfwSetErrorCallback(ErrorBus::getInstance().glfwErrorCallback);

  if (!glfwInit()) {
    ErrorBus::getInstance().sendError(0, "Failed to initialize GLFW");
    shutdown();
    return false;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_monitor = glfwGetPrimaryMonitor();
  m_mode = glfwGetVideoMode(m_monitor);

  m_window = glfwCreateWindow(width, height, title, NULL, NULL);

  if (!m_window) {
    ErrorBus::getInstance().sendError(0, "Failed to initialize a window");
    shutdown();
    return false;
  }

  glfwSetKeyCallback(m_window, InputBus::getInstance().keyCallback);

  glfwMakeContextCurrent(m_window);
  glfwSwapInterval(1);

  updateDimensions();

  return true;
}

void GLFWWrapper::shutdown() {
  if (m_window) {
    glfwDestroyWindow(m_window);
    m_window = nullptr;
  }
  glfwTerminate();
}

bool GLFWWrapper::windowShouldClose() {
  return glfwWindowShouldClose(m_window);
}

int GLFWWrapper::getTime() { return glfwGetTime(); }

void GLFWWrapper::updateDimensions() {
  glfwGetFramebufferSize(getWindow(), &m_display_w, &m_display_h);
}

void GLFWWrapper::newFrame() { updateDimensions(); }

void GLFWWrapper::finishFrame() { 
  glfwSwapBuffers(m_window);
  glfwPollEvents();
}

void GLFWWrapper::fillFrame(double r, double g, double b, double a) {
  glViewport(0, 0, m_display_w, m_display_h);
  glClearColor(r, g, b, a);
  glClear(GL_COLOR_BUFFER_BIT);
}