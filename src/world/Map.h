#ifndef INC_2D_GAME_MAP_H
#define INC_2D_GAME_MAP_H
#include <string>
#include "../third_party/raytmx.h"
#include "tiles.h"

#include <optional>

enum class MapId { World };

constexpr const char *MapIdToPath(const MapId id) {
  switch (id) {
    case MapId::World:
      return "../assets/maps/map.tmx";
  }
}

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

struct MapTransition {
  std::vector<MapCollider> transition_points;
  std::string map_id;
};

struct Map {
  TmxMap *tmx_map;
  BuildGrid grid;
  std::vector<MapCollider> colliders;
  std::vector<MapTransition> transitions;
  uint32_t width;
  uint32_t height;
};
#endif
