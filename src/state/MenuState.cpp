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
    m_titleText->update();
    m_demoText->update();
    m_exitText->update();
}

void MenuState::render()
{
    m_titleText->render();
    m_demoText->render();
    m_exitText->render();
}

bool MenuState::onEnter()
{
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    float scale = 1.0f;
    m_titleText = new Text("OpenGL Sandbox", Game::Instance()->getScreenWidth() * 0.1, Game::Instance()->getScreenHeight() - (Text::PIXEL_HEIGHT * scale * 2), scale, glm::vec3(255,255,255));
    scale = 0.8f;
    m_demoText = new Text("> Demo",  Game::Instance()->getScreenWidth() * 0.2, Game::Instance()->getScreenHeight() / 2 + Text::PIXEL_HEIGHT * scale , scale, glm::vec3(255,255,255));
    m_exitText = new Text("> Exit", Game::Instance()->getScreenWidth() * 0.2, Game::Instance()->getScreenHeight() / 2 - Text::PIXEL_HEIGHT * scale , scale, glm::vec3(255,255,255));

}

bool MenuState::onExit()
{
}