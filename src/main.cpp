#include <iostream>
#include <renderer.hpp>
#include <input_handler.hpp>
#include <game.hpp>
#include <userio.hpp>

int main (int argc, char* argv[]) {

    Game game;

    Renderer& renderer = Renderer::getInstance();
    InputHandler& input_handler = InputHandler::getInstance();

    renderer.initialize(480, "Kaban", input_handler);

    game.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

    while (!renderer.windowShouldClose()) {
        renderer.render();
    }
    renderer.shutdown();

    return 0;
}