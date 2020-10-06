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
    m_cube->update();
}

void MenuState::render()
{
    m_cube->render();
}

bool MenuState::onEnter()
{
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    m_cube = new Cube("../res/object/cube/cube.obj","../res/shaders/model_loading.vert","../res/shaders/model_loading.frag");
}

bool MenuState::onExit()
{
}