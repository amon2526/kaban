#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <GLFW/glfw3.h>
#include <iostream>
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <game.hpp>
#include <board.hpp>

class Renderer
{
public:
    Renderer();
    ~Renderer();

    bool initialize(int height, const char* title, Game* game = NULL);
    bool initializeOpenGL(int width, int height, const char* title);
    bool initializeImgui();
    void render();
    void shutdown();

    void showDemoWindow();
    bool windowShouldClose();
    void toggleDemoWindow();
    int calculateWindowWidth(int height) const { return height + _menuWidth; };

    GLFWwindow* getWindow() const { return _window; }

private:
    GLFWmonitor* _monitor;
    GLFWwindow* _window;
    const GLFWvidmode* _mode;
    
    Game* _game = NULL;

    int _menuWidth = 200;

    bool _showDemoWindow = false;
};

#endif