#pragma once

#include <vector>
#include <cstdint>

namespace Nare
{
    namespace ECS
    {
        using ComponentID = uint32_t;
        using Signature = std::vector<ComponentID>;

        struct ComponentStorage 
        {
            void* elements;
            size_t element_size;
            size_t count;
        };
    }
}