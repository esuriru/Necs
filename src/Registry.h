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
                for (int i = 0; i < previousArchetype.Components.size(); ++i)
                {
                    newArchetype.Components[previousRow].AddToBack(previousArchetype.Components[previousRow].At(previousRow));
                    previousArchetype.Components[previousRow].RemoveAt(previousRow);
                }

                Record newRecord = { newArchetype,  };
                entityIndex_.insert({ entity, newRecord });
            }

            template<typename T>
            inline auto AddComponent(EntityID entity, T component) -> void
            {
                ComponentID id = GetComponentID<T>();
                Record& currentRecord = entityIndex_[entity];
                Archetype& currentArchetype = currentRecord.Archetype;
                Archetype& nextArchetype = currentArchetype.Edges.Add[]
                MoveEntity(entity, currentArchetype, currentRecord.Row, nextArchetype);

                componentIndex_.insert({ id, { nextArchetype.ID, nextArchetype.Components[] }})

                // Now that they have moved archetypes, add the new component and record to the new archetype.
                nextArchetype.Components[i].AddToBack()
            }

            // template<typename... Ts>
            // auto View() -> std::vector<EntityID>
            // {
            //     if ()
            // }
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

            template<typename T>
            auto GetComponentID() -> ComponentID
            {
                // NOTE - TypeID is evaluated at compile time, so no overhead.
                const char* typeName = typeid(T).name();

                NECS_ASSERT(componentTypes_.find(typeName) != componentTypes_.end());

                return componentTypes_[typeName];
            }

            // template<typename T>
            // inline auto GetComponentStorage() -> shared_ptr<ComponentStorage<T>>
            // {
            //     const char* typeName = typeid(T).name();

            //     NECS_ASSERT(componentTypes_.find(typeName) != componentTypes_.end());

            //     return std::static_pointer_cast<ComponentArray<T>>(componentStorage_[typeName]);
            // }
        };
    }
}