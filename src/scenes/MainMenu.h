#ifndef INC_2D_GAME_MAINMENU_H
#define INC_2D_GAME_MAINMENU_H
#include "../ui/Menu.h"

#include "SceneManager.h"

class MainMenu : public Scene {
public:
  explicit MainMenu(Camera2D &camera, SceneManager &scene_manager) :
      camera(camera), scene_manager(scene_manager), menu(std::vector<Menu::Option>{
                                                        {
                                                            "Continue",
                                                            [this] { this->scene_manager.SwitchTo(SceneType::Game); },
                                                        },
                                                        {
                                                            "Quit",
                                                            [this] { this->scene_manager.UI().ShowQuitDialog(); },
                                                        },
                                                    }) {};

  void Update() override;
  void Draw() override;

private:
  Camera2D &camera;
  SceneManager &scene_manager;
  Menu menu;
};


#endif
