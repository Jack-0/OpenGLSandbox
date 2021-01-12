//
// Created by jack on 30/12/2020.
//

#ifndef OPENGLSANDBOX_PHYSICSSYSTEM_H
#define OPENGLSANDBOX_PHYSICSSYSTEM_H

#include <ecs/core/System.h>
#include "Game.h"

class PhysicsSystem : public System
{
public:
    void update()
    {
        for (auto const& entity : m_entities)
        {
            auto& rigid_body = Game::Instance()->get_ecs()->get_component<RigidBodyComponent>(entity);
            auto& transform = Game::Instance()->get_ecs()->get_component<TransformComponent>(entity);
        
            // update with delta time
            transform.pos += rigid_body.velocity * (Game::Instance()->getFPS() / 100); // FPS / 100 = DELTA TIME
        }
    
    }
};

#endif //OPENGLSANDBOX_PHYSICSSYSTEM_H
