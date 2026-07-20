#ifndef INC_2D_GAME_MAP_H
#define INC_2D_GAME_MAP_H
#include "tiles.h"
enum class MapId { House };

struct Map {
  TileLayer ground;
  TileLayer decorations;
  TileLayer collision;
};
#endif
