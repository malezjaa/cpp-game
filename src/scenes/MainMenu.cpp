#include "MainMenu.h"

void MainMenu::Update() {}

void MainMenu::Draw() {
  ClearBackground(UIManager::BACKGROUND_COLOR);
  scene_manager.UI().DrawMenu(menu);
}
