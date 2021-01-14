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
            auto &transform = Game::Instance()->get_ecs()->get_component<TransformComponent>(entity);
            auto &shader = Game::Instance()->get_ecs()->get_component<ShaderComponent>(entity);
            auto &text = Game::Instance()->get_ecs()->get_component<TextComponent>(entity);
            auto &dimension2D = Game::Instance()->get_ecs()->get_component<Dimensions2DComponent>(entity);
            auto &func_ptr = Game::Instance()->get_ecs()->get_component<FunctionPointerComponent>(entity);
    
    
            // check mouse over TODO maybe this will/should be its own system
            float mouse_x = Game::Instance()->m_lastMouseX;
            float mouse_y = Game::Instance()->getScreenHeight() - Game::Instance()->m_lastMouseY; // Y position must be subtracted from screen height to work with entities coord system TODO
            // set default colour
            text.colour = {255,255,255}; // set colour to white
            // check if the mouse is within the text bounds
            if (mouse_x > transform.pos.x) {
                if (mouse_x < (transform.pos.x + dimension2D.width)) {
                    if (mouse_y < transform.pos.y + PIXEL_HEIGHT) {
                        if (mouse_y >  transform.pos.y) {
                            // mouse is over the text, change text colour
                            text.colour = {0, 240, 0}; // set text colour to green
                            // check for mouse click
                            if( Game::Instance()->m_left_click )
                            {
                                func_ptr.fp();
                            }
                        }
                    }
                }
            }
            
        }
    }
    
    void render()
    {
    
    }
};

#endif //OPENGLSANDBOX_MENUSYSTEM_H
