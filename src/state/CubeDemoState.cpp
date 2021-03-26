//
// Created by jack on 22/08/2020.
//

#include <iostream>
#include <Game.h>
#include "CubeDemoState.h"


#include <GLFW/glfw3.h>
#include <random>
#include <ecs/components/MeshComponent.h>
#include <ecs/components/ShaderComponent.h>
#include <ecs/components/TransformComponent.h>
#include <ecs/components/TextComponent.h>
#include <ecs/components/Dimensions2DComponent.h>

#include <chrono>

const std::string CubeDemoState::s_StateID = "CUBE_DEMO_STATE";

void CubeDemoState::update()
{
    // todo test deleting enities
    if( game->get_key(GLFW_KEY_Q) == GLFW_PRESS )
    {
        ecs->destroy_entity(m_entities.front());
        m_entities.erase(m_entities.begin());
    }
}

void CubeDemoState::render() {
    mesh_renderer->render();
    text_renderer->render(); // todo here error

}

bool CubeDemoState::onEnter(){
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    
    
    text_renderer = ecs->register_system<TextRenderSystem>(); // todo fix
    /*
    {
        Signature text_sig;
        text_sig.set(ecs->get_component_type_id<ShaderComponent>());
        text_sig.set(ecs->get_component_type_id<TransformComponent>());
        text_sig.set(ecs->get_component_type_id<TextComponent>());
        text_sig.set(ecs->get_component_type_id<Dimensions2DComponent>());
        ecs->set_system_sig<TextRenderSystem>(text_sig);
    }
    */
    
    Entity fps_text = ecs->create_entity();
    ecs->add_component_to_entity(fps_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(fps_text, TransformComponent{glm::vec3{10,game->getScreenHeight()-PIXEL_HEIGHT-10,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(fps_text, TextComponent{"HelloWorld", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(fps_text, Dimensions2DComponent{0,0});
    text_renderer->init();


    
    // TODO here render a 3d MESH cube
    mesh_renderer = ecs->register_system<MeshRenderSystem>(); // TODO maybe a state should have it's own ECS
    {
        Signature mesh_sig;
        mesh_sig.set(ecs->get_component_type_id<MeshComponent>());
        mesh_sig.set(ecs->get_component_type_id<ShaderComponent>());
        mesh_sig.set(ecs->get_component_type_id<TransformComponent>());
        ecs->set_system_sig<MeshRenderSystem>(mesh_sig);
    }
    
    std::default_random_engine rand;
    std::uniform_real_distribution<float> rand_rot(0.0f, 360.0f);
    
    // TODO debug time
    using std::chrono::high_resolution_clock;
    using std::chrono::duration_cast;
    using std::chrono::duration;
    using std::chrono::milliseconds;

    auto t1 = high_resolution_clock::now(); // start time = t1

    float x_reset = -9;
    float x = x_reset;
    float y = 0;
    
    
    for(int i = 0; i < 300; i++)
    {    
        // skip the first cube to create a cube grid
        if( i != 0)
        {
            // alter position vector values for each cube
            if (i % 8 == 0)
            {
                x = x_reset;
                y -= 4.5;
            }
            else
            {
                x += 3;
            }
        }

        glm::vec3 pos = {x, y, -10};
        glm::vec3 rotation = {rand_rot(rand),rand_rot(rand),rand_rot(rand)};
        glm::vec3 scale = {1.0f, 1.0f, 1.0f};

        
        Entity cube = ecs->create_entity();
        ecs->add_component_to_entity(cube, MeshComponent{"../res/object/cube/cube.obj", NULL});
        ecs->add_component_to_entity(cube, ShaderComponent{"../res/shaders/model_loading.vert",
                                                                                   "../res/shaders/model_loading.frag",
                                                                                   NULL});
        ecs->add_component_to_entity(cube, TransformComponent{pos,rotation,scale});

        m_entities.push_back(cube);
    }
    auto t2 = high_resolution_clock::now();
    mesh_renderer->init();
    auto t3 = high_resolution_clock::now();

    duration<double, std::milli> ms_loop = t2 - t1;
    duration<double, std::milli> ms_mesh = t3 - t2;
    duration<double, std::milli> ms_total = t3 - t1;

    std::cout << "Init time results:\n" << "Time to finish loop = " << ms_loop.count() << "ms\n"
    << "Time to finish mesh init() = " << ms_mesh.count() << "ms\n" 
    << "Total time = " << ms_total.count() << "ms\n";
}

bool CubeDemoState::onExit()
{
}

void CubeDemoState::clean()
{
    
}