#pragma once

#include "Component.h"

#include <cstdint>
#include <unordered_set>
#include <unordered_map>

namespace Nare
{
    namespace ECS 
    {
        using ArchetypeID = uint32_t;

        // For archetype graph.
        struct ArchetypeEdge
        {
            Archetype& Add;
            Archetype& Remove;
        };

        struct Archetype
        {
            ArchetypeID ID;
            Signature signature;      
            std::vector<BasicColumn> Components;
            std::unordered_map<ComponentID, ArchetypeEdge> Edges;
        };

        struct ArchetypeRecord
        {
            size_t column;
        };

        using ArchetypeMap = std::unordered_map<ArchetypeID, ArchetypeRecord>;

    }
}