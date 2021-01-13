//
// Created by jack on 06/10/2020.
//

#include <iostream>
#include <Game.h>
#include "MenuState.h"

#include <GLFW/glfw3.h>
#include <ecs/components/FunctionPointerComponent.h>

const std::string MenuState::s_StateID = "MENU";

void MenuState::update()
{
}

void MenuState::render()
{
}

bool MenuState::onEnter()
{
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    
    // show mouse
    glfwSetInputMode(Game::Instance()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    
    // first register all components to be used
    Game::Instance()->get_ecs()->register_component<FunctionPointerComponent>();

    menu_system = Game::Instance()->get_ecs()->register_system<MenuSystem>();
    
    
    Entity test = Game::Instance()->get_ecs()->create_entity();
    
    Game::Instance()->get_ecs()->add_component_to_entity(test, FunctionPointerComponent{hello});
    
    menu_system->update();
    
}

bool MenuState::onExit()
{
    // hide mouse
    glfwSetInputMode(Game::Instance()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide mouse
}