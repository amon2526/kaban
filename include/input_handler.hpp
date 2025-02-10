#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <event_bus.hpp>
#include <GLFW/glfw3.h>
#include <iostream>

class InputHandler
{
public:
    static InputHandler &getInstance()
    {
        static InputHandler instance;
        return instance;
    }

    InputHandler(const InputHandler &) = delete;
    InputHandler &operator=(const InputHandler &) = delete;

    static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS)
        {
            InputEvent event;
            event.type = EventType::KeyDown;
            event.key = key;
            getInstance()._eventBus.publish(event);
        }
    }

private:
    InputHandler() = default;
    ~InputHandler() = default;

    EventBus _eventBus;
};

#endif

