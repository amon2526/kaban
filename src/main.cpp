#include <iostream>
#include <renderer.hpp>
#include <input_handler.hpp>
#include <game.hpp>

int main (int argc, char* argv[]) {
    Game game;
    Renderer renderer;
    InputHandler input_handler(&renderer, &game);

    renderer.initialize(480, "Kaban", &game);

    game.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");
    std::cout << game.getPlainBoard() << std::endl;
    while (!renderer.windowShouldClose()) {
        input_handler.update();
        renderer.render();
    }

    std::cout << "Press any key to exit..." << std::endl;
    std::cin.get();
    renderer.shutdown();

    return 0;
}