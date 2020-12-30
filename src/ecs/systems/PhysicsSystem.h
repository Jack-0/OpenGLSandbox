//
// Created by jack on 30/12/2020.
//

#ifndef OPENGLSANDBOX_PHYSICSSYSTEM_H
#define OPENGLSANDBOX_PHYSICSSYSTEM_H

#include "Game.h"

class PhysicsSystem : public System
{
public:
    void update()
    {
        for (auto const& entity : mEntities)
        {
            auto& rigidBody = gCoordinator.GetComponent<RigidBodyComponent>(entity);
            auto& transform = gCoordinator.GetComponent<TransformComponent>(entity);
        
            // update with delta time
            transform.position += rigidBody.velocity * (Game::Instance()->getFPS() / 100); // FPS / 100 = DELTA TIME
        }
    
    }
};

#endif //OPENGLSANDBOX_PHYSICSSYSTEM_H
