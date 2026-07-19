#ifndef INC_2D_GAME_CREDITS_H
#define INC_2D_GAME_CREDITS_H

#include <array>
#include <string_view>
#include <vector>

struct Credit {
  std::string_view author;
  std::vector<std::string_view> source_pages;
};

inline const std::array<Credit, 2> credits{
    {{
         "Kenney",
         {
             "https://kenney.nl/assets/ui-pack-pixel-adventure",
         },
     },
     {"ToffeeCraft", {"https://toffeecraft.itch.io/ui-user-interface-mega-pack"}}}};

#endif
