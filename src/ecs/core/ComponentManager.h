//
// Created by jack on 28/12/2020.
//

#ifndef ECS_COMPONENTMANAGER_H
#define ECS_COMPONENTMANAGER_H


#include <unordered_map>
#include <memory>
#include "EntityManager.h"
#include "ComponentArray.h"

class ComponentManager
{
public:
    
    template<typename T>
    void register_component()
    {
        const char* type_name = typeid(T).name();
        assert(m_componentTypes.find(type_name) == m_componentTypes.end() && "Registering component type more than once");
        
        
        // add this component type to the type map
        m_componentTypes.insert({type_name, m_nextComponentType});
        
        // create a component array pointer and add it to component arrays
        m_componentArrays.insert({type_name, std::make_shared<ComponentArray<T>>()}); // create pointer to memory for ComponentArray of type T
        
        // increment component type so the next component to be registered is different (not mapped to existing)
        ++m_nextComponentType;
    }
    
    template<typename T>
    ComponentType get_component_type()
    {
        const char* type_name = typeid(T).name();
        assert(m_componentTypes.find(type_name) != m_componentTypes.end() && "Component not registered before use");
        // return type (used for creating signatures)
        return m_componentTypes[type_name];
    }
    
    template<typename T>
    void add_component(Entity entity, T component)
    {
        get_componentArray<T>()->insert_data(entity, component);
    }
    
    template<typename T>
    void remove_component(Entity entity)
    {
        get_componentArray<T>()->remove_data(entity);
    }
    
    template<typename T>
    T& get_component(Entity entity)
    {
        return get_componentArray<T>()->get_data(entity);
    }
    
    void entity_destroyed(Entity entity)
    {
        for(auto const& pair : m_componentArrays)
        {
            auto const& component = pair.second;
            component->entity_destroyed(entity);
        }
    }
    
    

private:
    // map from string pointer to component type
    std::unordered_map<const char*, ComponentType> m_componentTypes {};
    // map from string pointer to component array
    std::unordered_map<const char*, std::shared_ptr<IComponentArray>> m_componentArrays {};
    // the component type to be assigned to the next registered component - starting at 0
    ComponentType m_nextComponentType{};
    
    // convenience function to get the statically casted pointer to the ComponentArray of type T.
    template<typename T>
    std::shared_ptr<ComponentArray<T>> get_componentArray()
    {
        const char* type_name = typeid(T).name();
        assert(m_componentTypes.find(type_name) != m_componentTypes.end() && "Component not registered before use");
        return std::static_pointer_cast<ComponentArray<T>>(m_componentArrays[type_name]);
    }
    

};


#endif //ECS_COMPONENTMANAGER_H
