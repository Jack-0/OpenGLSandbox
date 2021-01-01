//
// Created by jack on 30/12/2020.
//

#ifndef OPENGLSANDBOX_RENDERSYSTEM_H
#define OPENGLSANDBOX_RENDERSYSTEM_H

#include <ecs/core/System.h>
#include <ecs/components/MeshComponent.h>
#include <ecs/components/ShaderComponent.h>
#include <Game.h>
#include <ecs/components/TransformComponent.h>

class MeshRenderSystem : public System
{
public:
    void init()
    {
        for (auto const& entity : m_entities)
        {
            auto& mesh = Game::Instance()->get_ecs()->get_component<MeshComponent>(entity);
            auto& shader = Game::Instance()->get_ecs()->get_component<ShaderComponent>(entity);
            
            mesh.model = new Model(mesh.model_string_path);
            shader.shader = new Shader(shader.vert_path, shader.frag_path);
        }
    
    }
    
    void render()
    {
        for (auto const& entity : m_entities)
        {
            auto& mesh = Game::Instance()->get_ecs()->get_component<MeshComponent>(entity);
            auto& shader = Game::Instance()->get_ecs()->get_component<ShaderComponent>(entity);
            auto& transform = Game::Instance()->get_ecs()->get_component<TransformComponent>(entity);
 
            shader.shader->use();
            // view/projection transformations
            glm::mat4 projection = glm::perspective(glm::radians(Game::Instance()->getCamera()->Zoom), (float)Game::Instance()->getScreenWidth() / (float)Game::Instance()->getScreenHeight(), 0.1f, 100.0f);
            glm::mat4 view = Game::Instance()->getCamera()->GetViewMatrix();
            shader.shader->setMat4("projection", projection);
            shader.shader->setMat4("view", view);
            // render the loaded model
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, transform.pos); // translate it down so it's at the center of the scene
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
            shader.shader->setMat4("model", model);
            mesh.model->Draw(*shader.shader);
        }
    }
};

#endif //OPENGLSANDBOX_RENDERSYSTEM_H
