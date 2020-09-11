//
// Created by jack on 11/09/2020.
//

#include <Game.h>
#include "Cube.h"

Cube::Cube (std::string model_path, const char *vert_path, const char *frag_path) : GameObject()
{
    m_model = new Model(model_path);
    m_shader = new Shader(vert_path, frag_path);
}

void Cube::update()
{
}

void Cube::render()
{
    m_shader->use();
    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(Game::Instance()->getCamera()->Zoom), (float)Game::Instance()->getScreenWidth() / (float)Game::Instance()->getScreenHeight(), 0.1f, 100.0f);
    glm::mat4 view = Game::Instance()->getCamera()->GetViewMatrix();
    m_shader->setMat4("projection", projection);
    m_shader->setMat4("view", view);
    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    m_shader->setMat4("model", model);
    m_model->Draw(*m_shader);
}

void Cube::clean()
{}