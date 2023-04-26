#pragma once

#include "Component.h"

#include <cstdint>
#include <unordered_set>

namespace Nare
{
    namespace ECS 
    {
        using ArchetypeID = uint32_t;

        struct Archetype
        {
            ArchetypeID ID;
            Signature signature;      
        };

        using ArchetypeSet = std::unordered_set<ArchetypeID>;
    }
}