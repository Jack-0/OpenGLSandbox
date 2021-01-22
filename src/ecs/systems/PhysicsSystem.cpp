//
// Created by jack on 22/01/2021.
//

#include <ecs/systems/PhysicsSystem.h>
#include <ecs/components/RigidBodyComponent.h>
#include <ecs/components/TransformComponent.h>

#include "Game.h"

void PhysicsSystem::update()
{
    for (auto const& entity : m_entities)
    {
        auto& rigid_body = Game::Instance()->get_ecs()->get_component<RigidBodyComponent>(entity);
        auto& transform = Game::Instance()->get_ecs()->get_component<TransformComponent>(entity);
        
        // update with delta time
        transform.pos.x += rigid_body.velocity[0] * (Game::Instance()->getFPS() / 100); // FPS / 100 = DELTA TIME
        transform.pos.y += rigid_body.velocity[1] * (Game::Instance()->getFPS() / 100); // FPS / 100 = DELTA TIME
        transform.pos.z += rigid_body.velocity[2] * (Game::Instance()->getFPS() / 100); // FPS / 100 = DELTA TIME
    }
}
