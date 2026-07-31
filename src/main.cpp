#define RAYTMX_IMPLEMENTATION

#include <iostream>


#include "Player.h"
#include "raylib-cpp.hpp"
#include "scenes/Game.h"

using raylib::Window;

// Buy rights to https://thelazystone.itch.io/post-apocalypse-pixel-art-asset-pack if ever released commercialy

int main() {
  try {
    constexpr int screenWidth = UIManager::base_width;
    constexpr int screenHeight = UIManager::base_height;

    Window window(screenWidth, screenHeight, "paradigm");
    Window::SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_BORDERLESS_WINDOWED_MODE);
    
    int monitor = GetCurrentMonitor();
    SetWindowSize(GetMonitorWidth(monitor), GetMonitorHeight(monitor));
    SetWindowPosition(0, 0);
    SetExitKey(KEY_NULL);
    SetTextLineSpacing(16);

    rlImGuiSetup(true);

    Camera2D camera{};
    camera.offset = {screenWidth / 2.0f, screenHeight / 2.0f};
    camera.zoom = 3.0f;

    const Textures textures{};

    SceneManager scene_manager(textures, camera);
    scene_manager.SwitchTo(SceneType::MainMenu);

    while (!Window::ShouldClose()) {
      if (IsKeyPressed(KEY_F11)) {
        ToggleFullscreen();
      }
      scene_manager.Update();
      scene_manager.Draw();
    }
    rlImGuiShutdown();
  } catch (int err) {
    TraceLog(LOG_ERROR, "Error while running main game loop: %i", err);
  }

  return 0;
}
