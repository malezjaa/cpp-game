#include "SceneManager.h"

#include <format>

#include <magic_enum/magic_enum.hpp>
#include "Game.h"
#include "MainMenu.h"
#include "imgui.h"

Scene &SceneManager::CurrentScene() const { return *scenes.at(current_scene); }

void SceneManager::SwitchTo(const SceneType type) {
  if (const auto it = scenes.find(type); it != scenes.end()) {
    current_scene = type;
    return;
  }

  switch (type) {
    case SceneType::MainMenu:
      scenes.emplace(type, std::make_unique<MainMenu>(camera, *this));
      break;
    case SceneType::Game:
      scenes.emplace(type, std::make_unique<Game>(camera, *this));
      break;
  }

  current_scene = type;
}

void SceneManager::Update() {
  if (IsKeyPressed(KEY_F1)) {
    dev_tools.Settings().enabled = !dev_tools.Settings().enabled;
  }
  CurrentScene().Update();
}

void SceneManager::DrawDevTools() {
  ImGui::Begin("Developer Tools");
  ImGui::Text("FPS: %d", GetFPS());
  const auto name = magic_enum::enum_name(current_scene);
  ImGui::Text("Scene: %.*s", static_cast<int>(name.size()), name.data());
  ImGui::Text("Profile: %s", BUILD_PROFILE);
  ImGui::End();
}

void SceneManager::Draw() {
  BeginDrawing();
  rlImGuiBegin();

  if (dev_tools.Settings().enabled) {
    DrawDevTools();
  }

  {
    CurrentScene().Draw();
    ui_manager.DrawAlerts();
    ui_manager.DrawDialog();
  }
  rlImGuiEnd();
  EndDrawing();
}
