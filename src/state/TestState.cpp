//
// Created by jack on 22/08/2020.
//

#include <iostream>
#include <Game.h>
#include "TestState.h"

const std::string TestState::s_StateID = "TEST";

void TestState::render() {
    // TODO use model
    // don't forget to enable shader before setting uniforms
    ourShader->use();
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(Game::Instance()->getCamera()->Zoom), (float)Game::Instance()->getScreenWidth() / (float)Game::Instance()->getScreenHeight(), 0.1f, 100.0f);
    glm::mat4 view = Game::Instance()->getCamera()->GetViewMatrix();
    ourShader->setMat4("projection", projection);
    ourShader->setMat4("view", view);
    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    ourShader->setMat4("model", model);
    ourModel->Draw(*ourShader);
}

void TestState::update() {}

bool TestState::onEnter() {
    std::cout  << "TEST STATE ENTERED" << std::endl;

    ourShader = new Shader("../res/shaders/model_loading.vert", "../res/shaders/model_loading.frag");
    ourModel = new Model("../res/object/cube/cube.obj");
}

bool TestState::onExit() {}