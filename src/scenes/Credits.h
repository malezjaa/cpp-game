#ifndef INC_2D_GAME_CREDITS_H
#define INC_2D_GAME_CREDITS_H

#include <array>
#include <string_view>
#include <vector>

struct Credit {
  std::string_view author;
  std::vector<std::string_view> source_pages;
};

inline const std::array<Credit, 4> credits{
    {{
         "Kenney",
         {
             "https://kenney.nl/assets/ui-pack-pixel-adventure",
         },
     },
     {"Anokolisa", {"https://anokolisa.itch.io/free-pixel-art-asset-pack-topdown-tileset-rpg-16x16-sprites"}},
     {"TheLazyStone", {"https://thelazystone.itch.io/post-apocalypse-pixel-art-asset-pack"}},
     {"ToffeeCraft", {"https://toffeecraft.itch.io/ui-user-interface-mega-pack"}}}};

#endif
