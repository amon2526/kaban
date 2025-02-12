#ifndef MESSAGE_BUS_HPP
#define MESSAGE_BUS_HPP

#include <functional>
#include <mutex>
#include <queue>
#include <vector>

struct Message {
  virtual ~Message() = default;
};

class MessageBus {
public:
  MessageBus &getInstance();

  void addReceiver(std::function<void(const Message&)> messageReceiver);
  void notify();
  void sendMessage(std::unique_ptr<Message> message);

private:
  std::queue<std::unique_ptr<Message>> m_messages;
  std::vector<std::function<void(const Message&)>> m_receivers;
  std::mutex m_mutex;
};

#endif