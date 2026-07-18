#include "SceneManager.h"

#include "Game.h"
#include "MainMenu.h"

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
