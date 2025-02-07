#include <input_handler.hpp>

InputHandler::InputHandler(Renderer *renderer, Game *game) : _renderer(renderer), _game(game) {};

void InputHandler::update()
{
    glfwPollEvents();
    if (ImGui::IsKeyPressed(ImGuiKey_F1))
        _renderer->toggleDemoWindow();
    if (ImGui::IsKeyPressed(ImGuiKey_Escape))
        _renderer->shutdown();
};