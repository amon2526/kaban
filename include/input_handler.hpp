#ifndef INPUT_HANDLER_HPP
#define INPUT_HANDLER_HPP

#include <renderer.hpp>
#include <game.hpp>

class InputHandler
{
public:
    InputHandler(Renderer* renderer, Game* game);
    void update();

private:
    Renderer* _renderer;
    Game* _game;
};

#endif