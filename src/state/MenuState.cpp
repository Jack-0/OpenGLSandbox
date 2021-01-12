//
// Created by jack on 06/10/2020.
//

#include <iostream>
#include <Game.h>
#include "MenuState.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

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
    float scale = 1.0f;
    scale = 0.8f;
}

bool MenuState::onExit()
{
}