#ifndef INC_2D_GAME_TILES_H
#define INC_2D_GAME_TILES_H
#include <vector>
struct TileLayer {
  int width;
  int height;
  std::vector<std::uint32_t> tiles;

  std::uint32_t At(const int x, const int y) const { return tiles[y * width + x]; }
};
#endif
