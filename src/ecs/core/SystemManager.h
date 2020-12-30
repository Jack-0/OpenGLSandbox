//
// Created by jack on 29/12/2020.
//

#ifndef ECS_SYSTEMMANAGER_H
#define ECS_SYSTEMMANAGER_H

#include <memory>
#include "System.h"
#include "EntityManager.h"

//TODO: add remove System and destroy
class SystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> register_system()
    {
        const char* type_name = typeid(T).name();
        assert(m_systems.find(type_name) == m_systems.end() && "Registering system more than once");
    
        // create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();
        m_systems.insert({type_name, system});
        return system;
    }
    
    void entity_destroyed(Entity entity)
    {
        // erase a destroyed entity from all system lists
        // m_entities is a set so no check needed
        for (auto const& pair : m_systems)
        {
            auto const& system = pair.second;
        
            system->m_entities.erase(entity);
        }
    }
    
    void entity_signature_changed(Entity entity, Signature entity_signature)
    {
        // notify each system that an entity's signature changed
        for (auto const& pair : m_systems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& system_signature = m_signatures[type];
            
            // entity signature matches system signature - insert into set
            if ((entity_signature & system_signature) == system_signature)
            {
                system->m_entities.insert(entity);
            }
            // entity signature does not match system signature - erase from set
            else
            {
                system->m_entities.erase(entity);
            }
        }
    }

private:
    // map from system type string pointer to a signature
    std::unordered_map<const char*, Signature> m_signatures{};
    
    // map from system type string pointer to a system pointer
    std::unordered_map<const char*, std::shared_ptr<System>> m_systems{};
    
};


#endif //ECS_SYSTEMMANAGER_H
