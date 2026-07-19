#ifndef INC_2D_GAME_SCENEMANAGER_H
#define INC_2D_GAME_SCENEMANAGER_H
#include <Camera2D.hpp>
#include <memory>
#include <unordered_map>

#include "../ui/UIManager.h"
enum class SceneType { Game, MainMenu };

class Scene {
public:
  virtual ~Scene() = default;

  virtual void Update() = 0;
  virtual void Draw() = 0;
};

class SceneManager {
public:
  const Textures &textures;

  void SwitchTo(SceneType);
  UIManager &UI() { return ui_manager; }

  [[nodiscard]] Scene &CurrentScene() const;
  explicit SceneManager(const Textures &textures, const raylib::Camera2D &camera) :
      textures(textures), camera(camera), ui_manager(UIManager{textures}) {}

  void Update() const { CurrentScene().Update(); }

  void Draw() const {
    BeginDrawing();
    CurrentScene().Draw();
    ui_manager.DrawAlerts();
    ui_manager.DrawDialog();
    EndDrawing();
  }

private:
  std::unordered_map<SceneType, std::unique_ptr<Scene>> scenes{};
  SceneType current_scene = SceneType::MainMenu;
  raylib::Camera2D camera;
  UIManager ui_manager;
};

#endif
