#include "NpcRegistry.h"

NpcRegistry::NpcRegistry(entt::registry &registry) { npcs.try_emplace(NpcId::Milio, registry, NpcId::Milio); }
