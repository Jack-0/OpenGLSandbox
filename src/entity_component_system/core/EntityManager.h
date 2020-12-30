//
// Created by jack on 27/12/2020.
//

#ifndef ECS_ENTITYMANAGER_H
#define ECS_ENTITYMANAGER_H

#include <queue>
#include <cstdint>
#include <bitset>
#include <array>
#include <assert.h>

// type alias for clarity
using Entity = std::uint32_t;
using ComponentType = std::uint8_t;

// constants
const ComponentType MAX_COMPONENTS  = 3;
const Entity MAX_ENTITIES    = 11;

// signature type alias. Each bit represents if an Entity has a component.
// For example:
// let MAX_COMPONENTS = 3
// m_signatures[0] = b111 ... would be an entity with all components active
// m_signatures[1] = b010 ... would be an entity that only has component 1 active (where 0 is the first component)
using Signature = std::bitset<MAX_COMPONENTS>;

// System to manage entities
class EntityManager
{
public:
    EntityManager()
    {
        std::cout << "EntityManger:\n"
            << "\tMAX_COMPONENTS = " << int(MAX_COMPONENTS) << "\n"
            << "\tMAX_ENTITIES = " << int(MAX_ENTITIES) << "\n";
        
        // init the que with entities that have id from 0 to MAX_ENTITIES - 1
        for(std::uint32_t entity = 0; entity < MAX_ENTITIES; ++entity)
        {
            m_availableEntities.push(entity);
        }
    }
    
    Entity create_entity()
    {
        assert(m_totalEntities < MAX_ENTITIES && "Entity count too high");
        
        // get id from front of queue
        Entity id = m_availableEntities.front();    // get id from front of queue
        m_availableEntities.pop();                  // remove first item in queue
        ++m_totalEntities;
        
        return id;
    }
    
    void destroy_entity(Entity id)
    {
        assert(id < MAX_ENTITIES && "Entity out of range");
        
        m_signatures[id].reset();                   // set all the bits in the bit-set to 0
        m_availableEntities.push(id);               // put the entity id back into the queue
        --m_totalEntities;
    }
    
    void set_signature(Entity id, Signature signature)
    {
        assert(id < MAX_ENTITIES && "Entity out of range");
        m_signatures[id] = signature;
    }
    
    Signature get_signature(Entity id)
    {
        assert(id < MAX_ENTITIES && "Entity out of range");
        return m_signatures[id];
    }
    
    void info(Entity id)
    {
        std::cout << "Info for \'Entity " << int(id) << "\' = b" << m_signatures[id].to_string() <<"\n";
    }

private:
    // FIFO queue of available entities
    std::queue<Entity> m_availableEntities{};
    
    // Array of signatures where the index corresponds to the entity ID
    std::array<Signature, MAX_ENTITIES> m_signatures{};
    
    // Total living entities - used to keep limits on how many exist
    uint32_t m_totalEntities = 0;
};


#endif //ECS_ENTITYMANAGER_H
