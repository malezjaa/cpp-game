#define RAYTMX_IMPLEMENTATION

#include "Player.h"
#include "raylib-cpp.hpp"
#include "scenes/Game.h"

using raylib::Window;

// Buy rights to https://thelazystone.itch.io/post-apocalypse-pixel-art-asset-pack if ever released commercialy

int main() {
  rlImGuiSetup(true);

  constexpr int screenWidth = UIManager::base_width;
  constexpr int screenHeight = UIManager::base_height;

  Window::SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_FULLSCREEN_MODE);
  Window window(screenWidth, screenHeight, "paradigm");
  SetExitKey(KEY_NULL);
  SetTextLineSpacing(16);

  Camera2D camera{};
  camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
  camera.zoom = 3.0f;

  Textures textures{};

  SceneManager scene_manager(textures, camera);
  scene_manager.SwitchTo(SceneType::MainMenu);

  while (!Window::ShouldClose()) {
    scene_manager.Update();
    scene_manager.Draw();
  }
  rlImGuiShutdown();

  return 0;
}
