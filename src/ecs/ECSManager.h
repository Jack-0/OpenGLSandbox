//
// Created by jack on 30/12/2020.
//

#ifndef ECS_ECSMANAGER_H
#define ECS_ECSMANAGER_H

#include "core/ComponentManager.h"
#include "core/SystemManager.h"

/**
 * ECSManager a class that acts as a mediator and manager between the EntityManager, ComponentManager and SystemManager.
 *
 *
 *
 */
class ECSManager
{
public:
    
    /// initialises the needed Managers for the ECS model
    void init()
    {
        m_componentManager = std::make_unique<ComponentManager>();
        m_entityManager = std::make_unique<EntityManager>();
        m_systemManager = std::make_unique<SystemManager>();
    }
    
    // Entity management -----------------------------------------------------------------------------------------------
    /// Returns a uint_32_t with an integer that acts as the entities ID
    Entity create_entity()
    {
        return m_entityManager->create_entity();
    }
 
    /// Removes a given entity from the ECS
    void destroy_entity(Entity e)
    {
        m_entityManager->destroy_entity(e);
        m_componentManager->entity_destroyed(e);
        m_systemManager->entity_destroyed(e);
    }
    
    // Component management --------------------------------------------------------------------------------------------
    /// Registers a component
    template<typename T>
    void register_component()
    {
        m_componentManager->register_component<T>();
    }
    
    /// Adds a component to an entity ensures all Mangers know
    template<typename T>
    void add_component_to_entity(Entity e, T component)
    {
        // add
        m_componentManager->add_component<T>(e, component);
        auto sig = m_entityManager->get_signature(e);
        sig.set(m_componentManager->get_component_type<T>(), true); // flip bit on
        m_entityManager->set_signature(e, sig);
        // notify system
        m_systemManager->entity_signature_changed(e, sig);
    }
    
    /// Remove a component from an entity ensures all managers know
    template<typename T>
    void remove_component(Entity e)
    {
        m_componentManager->remove_component<T>(e);
        auto sig = m_entityManager->get_signature(e);
        sig.set(m_componentManager->get_component_type<T>(), false); // flip bit off
        m_entityManager->set_signature(e, sig);
        // notify system
        m_systemManager->entity_signature_changed(e, sig);
    }
    
    template<typename T>
    T& get_component(Entity entity)
    {
        return m_componentManager->get_component<T>(entity);
    }
    
    /// Returns the component type
    /// this is the unique id of the component (which is also the bit that gets flipped in the signature)
    template<typename T>
    ComponentType get_component_type_id()
    {
        return m_componentManager->get_component_type<T>();
    }
    
    
    // System methods
    /// Register the system
    template<typename T>
    std::shared_ptr<T> register_system()
    {
        return m_systemManager->register_system<T>();
    }
    
    template<typename T>
    void set_system_sig(Signature signature)
    {
        m_systemManager->set_signature<T>(signature);
    }


private:
    
    std::unique_ptr<ComponentManager> m_componentManager;
    std::unique_ptr<EntityManager> m_entityManager;
    std::unique_ptr<SystemManager> m_systemManager;
};


#endif //ECS_ECSMANAGER_H
