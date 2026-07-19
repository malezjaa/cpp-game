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
  static void Draw(const Texture2D &texture, const Rectangle source, const Rectangle destination,
                   const NineSliceBorders borders, const Color tint = WHITE) {
    if (source.width <= borders.left + borders.right || source.height <= borders.top + borders.bottom ||
        destination.width <= 0.0f || destination.height <= 0.0f) {
      return;
    }

    const float left = std::min(borders.left, destination.width / 2.0f);
    const float right = std::min(borders.right, destination.width - left);
    const float top = std::min(borders.top, destination.height / 2.0f);
    const float bottom = std::min(borders.bottom, destination.height - top);

    const float source_center_width = source.width - borders.left - borders.right;
    const float source_center_height = source.height - borders.top - borders.bottom;
    const float destination_center_width = destination.width - left - right;
    const float destination_center_height = destination.height - top - bottom;

    DrawRegion(texture, {source.x, source.y, borders.left, borders.top}, {destination.x, destination.y, left, top},
               tint);
    DrawRegion(texture, {source.x + borders.left, source.y, source_center_width, borders.top},
               {destination.x + left, destination.y, destination_center_width, top}, tint);
    DrawRegion(texture, {source.x + source.width - borders.right, source.y, borders.right, borders.top},
               {destination.x + destination.width - right, destination.y, right, top}, tint);

    DrawRegion(texture, {source.x, source.y + borders.top, borders.left, source_center_height},
               {destination.x, destination.y + top, left, destination_center_height}, tint);
    DrawRegion(texture, {source.x + borders.left, source.y + borders.top, source_center_width, source_center_height},
               {destination.x + left, destination.y + top, destination_center_width, destination_center_height}, tint);
    DrawRegion(
        texture, {source.x + source.width - borders.right, source.y + borders.top, borders.right, source_center_height},
        {destination.x + destination.width - right, destination.y + top, right, destination_center_height}, tint);

    DrawRegion(texture, {source.x, source.y + source.height - borders.bottom, borders.left, borders.bottom},
               {destination.x, destination.y + destination.height - bottom, left, bottom}, tint);
    DrawRegion(
        texture,
        {source.x + borders.left, source.y + source.height - borders.bottom, source_center_width, borders.bottom},
        {destination.x + left, destination.y + destination.height - bottom, destination_center_width, bottom}, tint);
    DrawRegion(texture,
               {source.x + source.width - borders.right, source.y + source.height - borders.bottom, borders.right,
                borders.bottom},
               {destination.x + destination.width - right, destination.y + destination.height - bottom, right, bottom},
               tint);
  }

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
