#include <game.hpp>
#include <gtest/gtest.h>
#include <input_handler.hpp>
#include <renderer.hpp>

int main(int argc, char *argv[]) {
  Game game;
  Renderer renderer;
  InputHandler inputHandler(&renderer, &game);
  renderer.init(600, "Kaban");
  renderer.hookUpGame(&game);

  game.setFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

  while (!renderer.windowShouldClose()) {
    inputHandler.update();
    renderer.render();
  }
  renderer.shutdown();
}