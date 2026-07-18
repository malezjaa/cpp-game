#ifndef INC_2D_GAME_MAINMENU_H
#define INC_2D_GAME_MAINMENU_H
#include <functional>


#include "SceneManager.h"

struct MenuOption {
  std::string name;
  std::function<void()> action;
};

class MainMenu : public Scene {
public:
  explicit MainMenu(Camera2D &camera, SceneManager &scene_manager) :
      camera(camera), scene_manager(scene_manager), options{
                                                        {
                                                            "Continue",
                                                            [this] { this->scene_manager.SwitchTo(SceneType::Game); },
                                                        },
                                                        {
                                                            "Quit",
                                                            [] { CloseWindow(); },
                                                        },
                                                    } {};

  void Update() override;
  void Draw() override;

private:
  Camera2D &camera;
  SceneManager &scene_manager;
  std::vector<MenuOption> options;
};


#endif
