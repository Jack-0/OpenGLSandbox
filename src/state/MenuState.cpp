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
    m_text->update();
    m_FPStext->setText("FPS: " + to_string(Game::Instance()->getFPS()));
    m_FPStext->update();
}

void MenuState::render()
{
    m_cube->render();
    m_text->render(); // Render text last to ensure it is on the top most layer - i.e not overlapped
    m_FPStext->render();
}

bool MenuState::onEnter()
{
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    m_cube = new Cube("../res/object/cube/cube.obj","../res/shaders/model_loading.vert","../res/shaders/model_loading.frag");
    m_text = new Text("Hello World", 100, 100, 1.0f, glm::vec3(255,255,255));
    m_FPStext = new Text("", 0, Game::Instance()->getScreenHeight()- Text::PIXEL_HEIGHT , 1.0f, glm::vec3(255,255,255));
}

bool MenuState::onExit()
{
}