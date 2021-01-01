//
// Created by jack on 28/12/2020.
//

#ifndef ECS_COMPONENTARRAY_H
#define ECS_COMPONENTARRAY_H

#include <assert.h>
#include <unordered_map>
#include "EntityManager.h"
#include "IComponentArray.h"


template<typename T>
class ComponentArray : public IComponentArray
{
public:
    void insert_data(Entity entity, T component)
    {
        // check that component is not being added multiple times
        assert(m_entityToIndexMap.find(entity) == m_entityToIndexMap.end() && "Component added to same entity more than once.");
        
        // put new entry at end and update the maps
        size_t new_index = m_size;
        // set entity index as end of array
        m_entityToIndexMap[entity] = new_index;
        
        m_indexToEntityMap[new_index] = entity;
        m_componentArray[new_index] = component;
        ++m_size;
    }
    
    void remove_data(Entity entity)
    {
        assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Remove a component that does not exist");
        
        // copy element at the end into deleted elements place to maintain density
        size_t index_of_removed_entity = m_entityToIndexMap[entity];
        size_t index_of_last_element = m_size - 1;
        
        // replace deleted elements entity with that of the last components entity
        m_componentArray[index_of_removed_entity] = m_componentArray[index_of_last_element];
    
        // update map to point to moved spot
        Entity entity_of_last_element = m_indexToEntityMap[index_of_last_element];
        m_entityToIndexMap[entity_of_last_element] = index_of_last_element;
        m_indexToEntityMap[index_of_removed_entity] = entity_of_last_element;
        
        m_entityToIndexMap.erase(entity);
        m_indexToEntityMap.erase(index_of_last_element);
        
        --m_size;
    }
    
    T& get_data(Entity entity)
    {
        assert(m_entityToIndexMap.find(entity) != m_entityToIndexMap.end() && "Remove a component that does not exist");
        
        return m_componentArray[m_entityToIndexMap[entity]];
    }
    
    virtual void entity_destroyed(Entity entity) override
    {
        if (m_entityToIndexMap.find(entity) != m_entityToIndexMap.end())
        {
            // remove entities component if it existed
            remove_data(entity);
        }
    }

private:
    // array with data type T for each entity.
    std::array<T, MAX_ENTITIES> m_componentArray;
    // map from an entity ID to an array index.
    std::unordered_map<Entity, size_t> m_entityToIndexMap;
    // map from an array index to an entity ID.
    std::unordered_map<size_t, Entity> m_indexToEntityMap;
    // total size of valid entries in array
    size_t m_size {};
};


#endif //ECS_COMPONENTARRAY_H
