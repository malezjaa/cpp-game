#include "Game.h"
#include "Player.h"
#include "raylib-cpp.hpp"
using raylib::Window;

int main() {
  constexpr int screenWidth = 800;
  constexpr int screenHeight = 450;

  Window::SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  Window window(screenWidth, screenHeight, "My game");
  SetExitKey(KEY_NULL);

  Camera2D camera{};
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.zoom = 1.0f;

  Game game{camera};

  while (!Window::ShouldClose()) {
    game.Update();
    game.Draw();
  }

  return 0;
}
