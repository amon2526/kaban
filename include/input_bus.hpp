#include <message_bus.hpp>
#include <glfw/glfw3.h>

enum InputSource { Keyboard, Mouse };

enum InputType { Down, Up, Move };

struct InputMessage : public Message {
  InputSource source;
  InputType type;
  int x;
  int y;
};

class InputBus {
public:
  static InputBus &getInstance();
  void addReceiver(std::function<void(const Message &)> receiver);
  void sendKey(int key, int scancode, int action, int mods);
  void notify();
  static void keyCallback(GLFWwindow *window, int key, int scancode, int action,
                          int mods);

private:
  void sendMessage(std::unique_ptr<Message> message);
  MessageBus m_bus;
};