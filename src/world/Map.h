#ifndef INC_2D_GAME_MAP_H
#define INC_2D_GAME_MAP_H
#include "../third_party/raytmx.h"
#include "tiles.h"

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

struct Map {
  TmxMap *tmx_map;
  BuildGrid grid;
  std::vector<Rectangle> collisions;
};
#endif
