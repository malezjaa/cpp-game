#include "Player.h"
#include "raylib-cpp.hpp"
#include "scenes/Game.h"
using raylib::Window;

int main() {
  constexpr int screenWidth = UIManager::base_width;
  constexpr int screenHeight = UIManager::base_height;

  Window::SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE);
  Window window(screenWidth, screenHeight, "My game");
  SetExitKey(KEY_NULL);
  SetTextLineSpacing(16);

  Camera2D camera{};
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.zoom = 1.0f;

  Textures textures{};
  textures.Load();

  SceneManager scene_manager(textures, camera);
  scene_manager.SwitchTo(SceneType::MainMenu);
  scene_manager.UI().Alert("Hello!");

  while (!Window::ShouldClose()) {
    scene_manager.Update();
    scene_manager.Draw();
  }

  return 0;
}
