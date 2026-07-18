#include "MainMenu.h"

void MainMenu::Update() {}

void MainMenu::Draw() {
  BeginDrawing();
  ClearBackground(RAYWHITE);

  scene_manager.UI().text.Render("Hello!", {20, static_cast<float>(GetScreenHeight() - 30)}, 20, GRAY);
  EndDrawing();
}
