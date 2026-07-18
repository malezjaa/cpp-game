#ifndef INC_2D_GAME_UIMANAGER_H
#define INC_2D_GAME_UIMANAGER_H
#include "TextRenderer.h"


class UIManager {
public:
  TextRenderer text;
  explicit UIManager() : text(TextRenderer("../assets/fonts/BoldPixels.ttf")) {};
};


#endif
