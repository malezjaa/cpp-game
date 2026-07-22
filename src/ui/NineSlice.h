#ifndef INC_2D_GAME_NINESLICE_H
#define INC_2D_GAME_NINESLICE_H

#include <algorithm>

#include "raylib.h"

struct NineSliceBorders {
  float left;
  float top;
  float right;
  float bottom;
};

class NineSlice {
public:
  static void Draw(const Texture2D &texture, Rectangle source, Rectangle destination, NineSliceBorders borders,
                   Color tint = WHITE);
  static void DrawBorder(const Texture2D &texture, Rectangle source, Rectangle destination, NineSliceBorders borders,
                         Color tint = WHITE);

private:
  static void DrawRegion(const Texture2D &texture, const Rectangle source, const Rectangle destination,
                         const Color tint) {
    if (destination.width <= 0.0f || destination.height <= 0.0f) {
      return;
    }

    DrawTexturePro(texture, source, destination, {}, 0.0f, tint);
  }
};

#endif
