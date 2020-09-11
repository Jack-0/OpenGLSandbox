//
// Created by jack on 22/08/2020.
//

#include <iostream>
#include <Game.h>
#include "TestState.h"

const std::string TestState::s_StateID = "TEST";

void TestState::render() {
    m_cube->render();
}

void TestState::update() {
    m_cube->update();
}

bool TestState::onEnter() {
    std::cout  << "TEST STATE ENTERED" << std::endl;
    m_cube = new Cube("../res/object/cube/cube.obj","../res/shaders/model_loading.vert","../res/shaders/model_loading.frag");
}

bool TestState::onExit() {}