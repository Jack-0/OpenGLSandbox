//
// Created by jack on 22/08/2020.
//

#ifndef OPENGLSANDBOX_GAMESTATE_H
#define OPENGLSANDBOX_GAMESTATE_H

#include <string>
#include <vector>
#include <ecs/core/EntityManager.h>

/**
 * Abstract class
 */
class GameState
{
public:
    virtual void update() =0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;
    
    virtual void clean() = 0;

    virtual std::string getStateID() const = 0;

protected:
    // entity id's are stored in m_entities to 'track' entities in the current state
    std::vector<Entity> m_entities;
};

#endif //OPENGLSANDBOX_GAMESTATE_H
