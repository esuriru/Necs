#pragma once

#include "Entity.h"
#include "Archetype.h"
#include "Component.h"
#include "Core.h"

#include <vector>
#include <unordered_map>
#include <memory>

namespace Nare
{
    namespace ECS
    {
        using std::unordered_map;
        using std::shared_ptr;

        class Registry
        {
        public:
            Registry()
            {
            }

            template<typename T> 
            auto GetComponent(EntityID entity, ComponentID component) -> T&
            {
                return *std::static_cast_pointer<T>(GetComponent(entity, component));
            }

            inline auto GetComponent(EntityID entity, ComponentID component) -> void*
            {
                // Record& record = entityToRecordMap_[entity]; 
                // Archetype& archetype = record.Archetype;

                // ArchetypeMap archetypes = componentIndex_[component];

                // if (archetypes.count(archetype.ID) == 0)
                // {
                //     return nullptr;
                // }

                // ArchetypeRecord& archetypeRecord = archetypes[archetype.ID];
                // ComponentStorage& storage = archetype.components[archetypeRecord.column];
                // return (storage.elements + storage.element_size * record.Row);
            }

            // template<typename T>
            inline auto MoveEntity(EntityID entity, Archetype& previousArchetype, size_t previousRow, Archetype& newArchetype) -> void
            {
                // Move all of the old components from the previous archetype.
                size_t newCountOfComponents = 0;
                for (size_t i = 0; i < previousArchetype.Components.size(); ++i)
                {
                    BasicColumn& previousArchetypeColumns = previousArchetype.Components[i];
                    BasicColumn& nextArchetypeColumns = newArchetype.Components[i];

                    nextArchetypeColumns.AddToBack(previousArchetype.Components[i].At(previousRow));
                    previousArchetype.RemoveAt(previousRow);

                    newCountOfComponents = newArchetypeColumns.Count();
                }

                // Remove the entity from the current archetype and move him to the new archetype.
                entityIndex_.insert({ entity, { newArchetype, newCountOfComponents - 1 } });
            }

            template<typename T>
            inline auto RegisterComponent() -> void
            {
                const char* typeName = typeid(T).name();
                if (componentTypes_.find(typeName) == componentTypes_.end())
                {
                    return;
                }

                componentTypes_.insert({ typeName, nextComponentID_ });
                
                // Setup the new archetypes.

                ++nextComponentID_;
            }

            template<typename T>
            inline auto AddComponent(EntityID entity, T component) -> void
            {
                // If there is not a component index for it yet, create it.
                ComponentID id = GetComponentID<T>();

                if (id == 0)
                {
                    RegisterComponent<T>();
                }

                Record& currentRecord = entityIndex_[entity];
                Archetype& currentArchetype = currentRecord.Archetype;
                Archetype& nextArchetype = currentArchetype.Edges.Add[]
                MoveEntity(entity, currentArchetype, currentRecord.Row, nextArchetype);

                // Now that they have moved archetypes, add the new component and record to the new archetype.
                if (componentIndex_.find(id) == componentIndex_.end())
                {
                    componentIndex_.insert({ id, { nextArchetype.ID, entityIndex_[entity] }});
                }
                
                ArchetypeMap archetypes = componentIndex_[id];
                ArchetypeRecord archetypeRecord = archetypes[nextArchetype.ID];
                nextArchetype.Components[archetypeRecord].AddToBack(&component);
            }
        private:
            struct Record
            {
                Archetype& Archetype;
                size_t Row;
                
                Record() = default;
                Record(const Record&) = default;
            };

            // unordered_map<const char*, shared_ptr<IComponentStorage>> componentStorage_;

            unordered_map<const char*, ComponentID> componentTypes_;
            unordered_map<EntityID, Record> entityIndex_;
            unordered_map<Signature, Archetype> signatureToArchetypeMap_;
            unordered_map<ComponentID, ArchetypeMap> componentIndex_;
            ComponentID nextComponentID_;

            template<typename T>
            auto GetComponentID() const -> ComponentID
            {
                // NOTE - TypeID is evaluated at compile time, so no overhead.
                const char* typeName = typeid(T).name();

                if (componentTypes_.find(typeName) == componentTypes_.end())
                {
                    return 0;
                }

                return componentTypes_[typeName];
            }
        };
    }
}