#ifndef INC_2D_GAME_PANEL_H
#define INC_2D_GAME_PANEL_H

#include "NineSlice.h"

class Panel {
public:
  static void Draw(const Texture2D &texture, const Rectangle border_source, const Rectangle bounds,
                   const NineSliceBorders border_size, const Color top_color, const Color bottom_color) {
    DrawRectangleGradientV(static_cast<int>(bounds.x), static_cast<int>(bounds.y), static_cast<int>(bounds.width),
                           static_cast<int>(bounds.height), top_color, bottom_color);

    const Rectangle highlight{
        bounds.x + border_size.left,
        bounds.y + border_size.top,
        bounds.width - border_size.left - border_size.right,
        std::min(8.0f, bounds.height - border_size.top - border_size.bottom),
    };
    if (highlight.width > 0.0f && highlight.height > 0.0f) {
      DrawRectangleGradientV(static_cast<int>(highlight.x), static_cast<int>(highlight.y),
                             static_cast<int>(highlight.width), static_cast<int>(highlight.height), {255, 255, 255, 16},
                             {255, 255, 255, 0});
    }

    NineSlice::DrawBorder(texture, border_source, bounds, border_size);
  }
};

#endif
