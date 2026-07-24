#ifndef INC_2D_GAME_SCENEMANAGER_H
#define INC_2D_GAME_SCENEMANAGER_H
#include <Camera2D.hpp>
#include <memory>
#include <unordered_map>

#include "../ui/UIManager.h"
#include "rlImGui.h"
enum class SceneType { Game, MainMenu };

class Scene {
public:
  virtual ~Scene() = default;

  virtual void Update() = 0;
  virtual void Draw() = 0;
};

struct DevTools {
  bool enabled = false;
  bool draw_colliders = false;
  bool colliders = true;
  bool draw_grid_map = false;
};

class SceneManager {
public:
  const Textures &textures;

  void SwitchTo(SceneType);
  UIManager &UI() { return ui_manager; }

  [[nodiscard]] Scene &CurrentScene() const;
  explicit SceneManager(const Textures &textures, const raylib::Camera2D &camera) :
      textures(textures), camera(camera), ui_manager(UIManager{textures}) {}

  void Update();
  void DrawDevTools();
  void Draw();

  DevTools dev_tools;

private:
  std::unordered_map<SceneType, std::unique_ptr<Scene>> scenes{};
  SceneType current_scene = SceneType::MainMenu;
  raylib::Camera2D camera;
  UIManager ui_manager;
};

#endif
