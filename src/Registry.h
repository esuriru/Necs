#pragma once

#include "Entity.h"

#include <unordered_map>
#include "Archetype.h"

namespace Nare
{
    namespace ECS
    {
        class Registry
        {
        public:

        private:
            std::unordered_map<EntityID, Archetype&> entityToArchetypeMap_;
            std::unordered_map<Signature, Archetype> signatureToArchetypeMap_;
            std::unordered_map<ComponentID, ArchetypeSet> componentIDToArchetypeSetMap_;
        };
    }
}