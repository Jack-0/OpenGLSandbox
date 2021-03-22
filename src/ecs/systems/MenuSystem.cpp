//
// Created by jack on 22/01/2021.
//

#include <ecs/systems/MenuSystem.h>
#include <Game.h>
#include <ecs/components/FunctionPointerComponent.h>
#include <ecs/components/TransformComponent.h>
#include <ecs/components/ShaderComponent.h>
#include <ecs/components/TextComponent.h>
#include <ecs/components/Dimensions2DComponent.h>


void MenuSystem::update()
{
    for (auto const& entity : m_entities)
    {
        auto &transform = ecs->get_component<TransformComponent>(entity);
        auto &shader = ecs->get_component<ShaderComponent>(entity);
        auto &text = ecs->get_component<TextComponent>(entity);
        auto &dimension2D = ecs->get_component<Dimensions2DComponent>(entity);
        auto &func_ptr = ecs->get_component<FunctionPointerComponent>(entity);
        
        
        // check mouse over TODO maybe this will/should be its own system
        float mouse_x = game->m_lastMouseX;
        float mouse_y = game->getScreenHeight() - game->m_lastMouseY; // Y position must be subtracted from screen height to work with entities coord system TODO
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
                        if( game->m_left_click )
                        {
                            func_ptr.fp();
                        }
                    }
                }
            }
        }
        
    }
}

void MenuSystem::render()
{}