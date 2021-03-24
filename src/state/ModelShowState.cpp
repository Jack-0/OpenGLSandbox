//
// Created by jack on 24/03/2021.
//

#include "ModelShowState.h"
#include <Game.h>

#include <ecs/components/MeshComponent.h>
#include <ecs/components/ShaderComponent.h>
#include <ecs/components/TransformComponent.h>

const std::string  ModelShowState::s_StateID = "MODEL_SHOW_STATE";

void ModelShowState::update()
{}

void ModelShowState::render()
{
    mesh_renderer->render();
}

bool ModelShowState::onEnter()
{
    mesh_renderer = ecs->register_system<MeshRenderSystem>(); // TODO maybe a state should have it's own ECS
    {
        Signature mesh_sig;
        mesh_sig.set(ecs->get_component_type_id<MeshComponent>());
        mesh_sig.set(ecs->get_component_type_id<ShaderComponent>());
        mesh_sig.set(ecs->get_component_type_id<TransformComponent>());
        ecs->set_system_sig<MeshRenderSystem>(mesh_sig);
    }

    glm::vec3 pos = {0, 0, 0};
    glm::vec3 rotation = {0,0,0};
    glm::vec3 scale = {1.0f, 1.0f, 1.0f};

    
    Entity cube = ecs->create_entity();
    ecs->add_component_to_entity(cube, MeshComponent{"../res/object/cube/cube.obj", NULL});
    ecs->add_component_to_entity(cube, ShaderComponent{"../res/shaders/model_loading.vert",
                                                                                "../res/shaders/model_loading.frag",
                                                                                NULL});
    ecs->add_component_to_entity(cube, TransformComponent{pos,rotation,scale});

    mesh_renderer->init();
}

bool ModelShowState::onExit()
{}

void ModelShowState::clean()
{}