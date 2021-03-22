//
// Created by jack on 22/01/2021.
//

#include <ecs/systems/MeshRenderSystem.h>

#include <Game.h>
#include <ecs/components/MeshComponent.h>
#include <ecs/components/ShaderComponent.h>
#include <ecs/components/TransformComponent.h>

void MeshRenderSystem::init()
{
    for (auto const& entity : m_entities)
    {
        auto& mesh = ecs->get_component<MeshComponent>(entity);
        auto& shader = ecs->get_component<ShaderComponent>(entity);
        
        // check if model already exists
        if ( models.find(mesh.model_string_path) != models.end() )
        {
            // model has been created before no need to initialise
            mesh.model = models[mesh.model_string_path];
        }
        else
        {
            // model has not been created before. Create it and store a reference to it within the map
            models[mesh.model_string_path] = new Model(mesh.model_string_path);
            mesh.model = models[mesh.model_string_path];
        }

        //mesh.model = new Model(mesh.model_string_path);
        shader.shader = new Shader(shader.vert_path, shader.frag_path);
    }
}

void MeshRenderSystem::render()
{
    for (auto const& entity : m_entities)
    {
        auto& mesh = ecs->get_component<MeshComponent>(entity);
        auto& shader = ecs->get_component<ShaderComponent>(entity);
        auto& transform = ecs->get_component<TransformComponent>(entity);
        
        shader.shader->use();
        // view/projection transformations
        glm::mat4 projection = glm::perspective(glm::radians( game->getCamera()->Zoom), (float) game->getScreenWidth() / (float) game->getScreenHeight(), 0.1f, 100.0f);
        glm::mat4 view = game->getCamera()->GetViewMatrix();
        shader.shader->setMat4("projection", projection);
        shader.shader->setMat4("view", view);
        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, transform.pos); // translate it down so it's at the center of the scene
        model = glm::scale(model, transform.scale);	// it's a bit too big for our scene, so scale it down
        
        // apply rotation transform
        model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1,0,0));
        model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0,1,0));
        model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0,0,1));
        
        shader.shader->setMat4("model", model);
        mesh.model->Draw(*shader.shader);
    }
}