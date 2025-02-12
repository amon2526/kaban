#include <error_bus.hpp>
#include <iostream>
#include <utility>

ErrorBus &ErrorBus::getInstance() {
  static ErrorBus instance;
  return instance;
}

void ErrorBus::addReceiver(std::function<void(const Message &)> receiver) {
  m_bus.addReceiver(std::move(receiver));
}
void ErrorBus::sendMessage(std::unique_ptr<Message> message) {
  m_bus.sendMessage(std::move(message));
}
void ErrorBus::sendError(int error, std::string description) {
  auto message = std::make_unique<ErrorMessage>();
  message->m_error = error;
  message->m_description = description;
  sendMessage(std::move(message));
}
void ErrorBus::glfwErrorCallback(int error, const char *description) {
  ErrorBus::getInstance().sendError(error, description);
}

void ErrorBus::notify() { m_bus.notify(); }

ErrorBus::ErrorBus() {
  addReceiver([](const Message &msg) {
    if (const auto *errorMsg = dynamic_cast<const ErrorMessage *>(&msg)) {
      std::cerr << "ERROR " << errorMsg->m_error << ": "
                << errorMsg->m_description << std::endl;
    }
  });
}