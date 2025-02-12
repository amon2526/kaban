#include <error_bus.hpp>
#include <input_bus.hpp>
#include <game.hpp>

#include <renderer.hpp>

int main(int argc, char *argv[]) {

  Game game;
  Renderer renderer;

  renderer.initGraphics(480, "Kaban");

  game.loadFEN("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR");

  while (!renderer.windowShouldClose()) {
    ErrorBus::getInstance().notify();
    InputBus::getInstance().notify();
    renderer.render();
  }
  renderer.shutdown();

  return 0;
}