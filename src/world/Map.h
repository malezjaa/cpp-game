#ifndef INC_2D_GAME_MAP_H
#define INC_2D_GAME_MAP_H
#include "../third_party/raytmx.h"
#include "tiles.h"

#include <optional>

enum class CellState { Free, Blocked, Reserved };

struct Cell {
  int x;
  int y;
  CellState state;
};

struct BuildGrid {
  int width;
  int height;
  std::vector<Cell> cells;
};

struct MapCollider {
  std::vector<Vector2> points;

  // Rectangles are easier to check collisions for.
  std::optional<Rectangle> bounds;
};

struct Map {
  TmxMap *tmx_map;
  BuildGrid grid;
  std::vector<MapCollider> colliders;
  uint32_t width;
  uint32_t height;
};
#endif
