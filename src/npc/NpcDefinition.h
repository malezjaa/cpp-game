#ifndef INC_2D_GAME_NPCDEFINITION_H
#define INC_2D_GAME_NPCDEFINITION_H

#include <array>
#include <string_view>
#include <utility>

enum class NpcId {
  Milio,

  Count
};

struct NpcDefinition {
  std::string_view name;
};

constexpr std::array<NpcDefinition, std::to_underlying(NpcId::Count)> NPC_DEFINITIONS{{
    {"Millio"},
}};

constexpr const NpcDefinition &GetNpcDefinition(const NpcId id) { return NPC_DEFINITIONS[std::to_underlying(id)]; }

#endif
