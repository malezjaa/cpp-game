#ifndef INC_2D_GAME_SCENEMANAGER_H
#define INC_2D_GAME_SCENEMANAGER_H
#include <Camera2D.hpp>
#include <memory>
#include <unordered_map>
enum class SceneType { Game, MainMenu };

class Scene {
public:
  virtual ~Scene() = default;

  virtual void Update() = 0;
  virtual void Draw() = 0;
};

class SceneManager {
public:
  void SwitchTo(SceneType);
  [[nodiscard]] Scene &CurrentScene() const;
  explicit SceneManager(const raylib::Camera2D &camera) : camera(camera) {}

private:
  std::unordered_map<SceneType, std::unique_ptr<Scene>> scenes{};
  SceneType current_scene = SceneType::MainMenu;
  raylib::Camera2D camera;
};

#endif
