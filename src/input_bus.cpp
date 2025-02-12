#include <input_bus.hpp>
#include <memory>
#include <utility>

InputBus &InputBus::getInstance() {
  static InputBus instance;
  return instance;
}

void InputBus::addReceiver(std::function<void(const Message &)> receiver) {
  m_bus.addReceiver(std::move(receiver));
}

void InputBus::sendMessage(std::unique_ptr<Message> message) {
  m_bus.sendMessage(std::move(message));
}

void InputBus::notify() { m_bus.notify(); }

void InputBus::keyCallback(GLFWwindow *window, int key, int scancode,
                           int action, int mods) {
  InputBus::getInstance().sendKey(key, scancode, action, mods);
}

void InputBus::sendKey(int key, int scancode, int action, int mods) {
  auto message = std::make_unique<InputMessage>();
  message->source = Keyboard;
  message->type = action == GLFW_PRESS ? Down : Up;
  sendMessage(std::move(message));
}
