#ifndef INC_2D_GAME_COMPONENTS_H
#define INC_2D_GAME_COMPONENTS_H
#include <raylib.h>

struct Position {
  Vector2 value{};
};

struct Velocity {
  Vector2 value{};
};

struct Health {
  int current = 100;
  int maximum = 100;
};

struct MoveTarget {
  Vector2 target;
  float speed;
  float stopDistance = 2.0f;
};

struct PlayerControlled {};
#endif
