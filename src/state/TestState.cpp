//
// Created by jack on 22/08/2020.
//

#include <iostream>
#include <Game.h>
#include "TestState.h"

const std::string TestState::s_StateID = "TEST";

void TestState::render() {
    //m_cube->render();
    m_cube2->render();
    m_shape->render();
}

void TestState::update() {
    m_cube->update();
    m_cube2->move(test,0,0);
    test += 0.0001f;
    m_cube2->update();
    m_shape->update();
}

bool TestState::onEnter() {
    std::cout  << "TEST STATE ENTERED" << std::endl;
    m_cube = new Cube("../res/object/cube/cube.obj","../res/shaders/model_loading.vert","../res/shaders/model_loading.frag");
    m_cube2 = new Cube("../res/object/cube/cube.obj","../res/shaders/model_loading.vert","../res/shaders/model_loading.frag");
    m_shape = new Shape();
}

bool TestState::onExit() {}