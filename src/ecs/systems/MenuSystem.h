//
// Created by jack on 13/01/2021.
//

#ifndef OPENGLSANDBOX_MENUSYSTEM_H
#define OPENGLSANDBOX_MENUSYSTEM_H

#include <Game.h>
#include <ecs/components/FunctionPointerComponent.h>

class MenuSystem : public System
{
public:
    void update()
    {
        for (auto const& entity : m_entities)
        {
            auto &func_ptr = Game::Instance()->get_ecs()->get_component<FunctionPointerComponent>(entity);
            func_ptr.fp();
        }
    }
    
    void render()
    {
    
    }
};

#endif //OPENGLSANDBOX_MENUSYSTEM_H
