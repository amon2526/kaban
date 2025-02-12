#include <memory>
#include <message_bus.hpp>

MessageBus &MessageBus::getInstance() {
  static MessageBus instance;
  return instance;
}

void MessageBus::addReceiver(std::function<void(const Message&)> messageReceiver) {
  std::lock_guard<std::mutex> lock(m_mutex);
  m_receivers.push_back(messageReceiver);
}

void MessageBus::notify() {
  std::lock_guard<std::mutex> lock(m_mutex);
  while (!m_messages.empty()) {
    const std::unique_ptr<Message> &message = m_messages.front();
    for (const auto &receiver : m_receivers) {
      receiver(*message);
    }
    m_messages.pop();
  }
}

void MessageBus::sendMessage(std::unique_ptr<Message> message) {
  std::lock_guard<std::mutex> lock(m_mutex);
  m_messages.push(std::move(message));
}

/*std::function<void (Message)> BusNode::getNotifyFunc()
{
    auto messageListener = [=](Message message) -> void {
        this->onNotify(message);
    };
    return messageListener;
}

void BusNode::send(Message message)
{
    m_messageBus->sendMessage(message);
}*/