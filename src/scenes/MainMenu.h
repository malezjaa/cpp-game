#ifndef INC_2D_GAME_MAINMENU_H
#define INC_2D_GAME_MAINMENU_H
#include "SceneManager.h"

class MainMenu : public Scene {
public:
  explicit MainMenu(Camera2D &camera, SceneManager &scene_manager) : camera(camera), scene_manager(scene_manager) {};

  void Update() override;
  void Draw() override;

private:
  Camera2D &camera;
  SceneManager &scene_manager;
};


#endif
