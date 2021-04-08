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
    m_skybox->render();
    mesh_renderer->render();
}

bool ModelShowState::onEnter()
{
    // init skybox
    m_skybox = new SkyBox("../res/skybox/field/");
    
    // get stb_image.h to flip loaded texture's on the y-axis 
    stbi_set_flip_vertically_on_load(true); // TODO some texures need this

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
    glm::vec3 scale = {0.2f, 0.2f, 0.2f};

    
    Entity model = ecs->create_entity();
    ecs->add_component_to_entity(model, MeshComponent{"../res/object/backpack/backpack.obj", NULL});
    ecs->add_component_to_entity(model, ShaderComponent{"../res/shaders/model_loading.vert",
                                                                                "../res/shaders/model_loading.frag",
                                                                                NULL});
    ecs->add_component_to_entity(model, TransformComponent{pos,rotation,scale});

    //glShadeModel(GL_SMOOTH);
    mesh_renderer->init();
}

bool ModelShowState::onExit()
{}

void ModelShowState::clean()
{}