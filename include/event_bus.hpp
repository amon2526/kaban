#ifndef EVENT_BUS_HPP
#define EVENT_BUS_HPP 

#include <functional>
#include <vector>

enum class EventType {
    KeyDown,
    KeyUp, 
    MouseButtonDown,
    MouseButtonUp,
    MouseMove,
};

struct InputEvent {
    EventType type;
    int key = 0;
    int button = 0;
    int x = 0;
    int y = 0;
};

using EventListener = std::function<void(const InputEvent&)>;

class EventBus {
public: 
    EventBus() = default;  // Default constructor
    ~EventBus() = default;
    void subsribe(EventListener listener) {
        listeners.push_back(listener);
    }
    void publish(const InputEvent& event) {
        for (auto& listener : listeners) {
            listener(event);
        }
    }
private:
    std::vector<EventListener> listeners;
};

#endif