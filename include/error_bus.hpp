#ifndef ERROR_BUS_HPP
#define ERROR_BUS_HPP

#include <message_bus.hpp>
#include <string>

struct ErrorMessage : public Message {
  int m_error;
  std::string m_description;
};

class ErrorBus {
public:
  static ErrorBus &getInstance();
  void notify();
  void addReceiver(std::function<void(const Message &)> receiver);
  void sendError(int error, std::string description);
  static void glfwErrorCallback(int error, const char *description);
  
  private:
  ErrorBus();
  ~ErrorBus() = default;
  
  ErrorBus(const ErrorBus &) = delete;
  ErrorBus(ErrorBus &&) = delete;
  ErrorBus &operator=(const ErrorBus &) = delete;
  ErrorBus &operator=(ErrorBus &&) = delete;
  void sendMessage(std::unique_ptr<Message> message);

  MessageBus m_bus;
};

#endif