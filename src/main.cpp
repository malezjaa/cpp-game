#include "Player.h"
#include "raylib-cpp.hpp"
#include "scenes/Game.h"
using raylib::Window;

int main() {
  constexpr int screenWidth = 800;
  constexpr int screenHeight = 450;

  Window::SetConfigFlags(FLAG_WINDOW_RESIZABLE);
  Window window(screenWidth, screenHeight, "My game");
  SetExitKey(KEY_NULL);
  SetTextLineSpacing(16);

  Camera2D camera{};
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.zoom = 1.0f;

  SceneManager scene_manager(camera);
  scene_manager.SwitchTo(SceneType::MainMenu);

  while (!Window::ShouldClose()) {
    scene_manager.CurrentScene().Update();
    scene_manager.CurrentScene().Draw();
  }

  return 0;
}
