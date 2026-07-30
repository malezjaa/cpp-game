#ifndef INC_2D_GAME_HEALTHBAR_H
#define INC_2D_GAME_HEALTHBAR_H
#include "../ecs/components.h"
#include "../ui/TextRenderer.h"


void DrawHealthBar(const TextRenderer &, const Textures &textures, const Health &health);


#endif
