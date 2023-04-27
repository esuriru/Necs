#pragma once

#include "Entity.h"

#include <vector>
#include <cstdint>
#include <unordered_set>
#include <bitset>

namespace Nare
{
    namespace ECS
    {
        using ComponentID = uint32_t;
        // constexpr ComponentID MaxComponents = 10000;
        using Signature = std::vector<ComponentID>; 


        class BasicColumn
        {
        public:
            virtual auto At(size_t index) -> void* = 0;
            virtual auto Set(size_t index, void* component) -> void = 0;
            virtual auto AddToBack(void* component) -> void = 0;
            virtual auto RemoveAt(size_t index) -> void = 0;
            virtual auto Count() const -> size_t = 0;
        };

        template<typename T>
        class Column : public BasicColumn
        {
        public:
            auto At(size_t index) -> void* override
            {
                return &components_[index];
            }
            
            auto Set(size_t index, void* component) -> void override
            {
                components_[index] = static_cast<T>(&component);
            }

            auto AddToBack(void* component) -> void override
            {
                components_.emplace_back(static_cast<T>(&component));
            }

            auto RemoveAt(size_t index) -> void override
            {
                // NOTE - .erase() is linear complexity, hence use this instead.
                if (index != components_.size() - 1)
                {
                    components_[index] = std::move(components_.back());
                }
                components_.pop_back();
            }
            
            auto Count() const -> size_t override
            {
                return components_.size();
            }
        
        private:
            std::vector<T> components_;
        };

        struct ComponentStorage
        {
            char* elements = nullptr;
            size_t element_size;
            size_t count;

            inline auto operator[](size_t index) -> void*
            {
                // NOTE - Can go out of range
                return (elements + index * element_size);
            }
        };



    }
}