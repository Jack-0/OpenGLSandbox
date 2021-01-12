//
// Created by jack on 22/08/2020.
//

#include <iostream>
#include <Game.h>
#include "TestState.h"


#include <GLFW/glfw3.h>
#include <ecs/ECSManager.h>
#include <random>
#include <ecs/components/TextComponent.h>

const std::string TestState::s_StateID = "TEST";

void TestState::update()
{
}

void TestState::render() {
    mesh_renderer->render();
    text_renderer->render(); // todo here error

}

bool TestState::onEnter(){
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    
    Game::Instance()->get_ecs()->register_component<MeshComponent>();
    Game::Instance()->get_ecs()->register_component<ShaderComponent>();
    Game::Instance()->get_ecs()->register_component<TransformComponent>();
    Game::Instance()->get_ecs()->register_component<TextComponent>();
    
    // TODO text render
    text_renderer = Game::Instance()->get_ecs()->register_system<TextRenderSystem>();
    
    Entity fps_text = Game::Instance()->get_ecs()->create_entity();
    Game::Instance()->get_ecs()->add_component_to_entity(fps_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    Game::Instance()->get_ecs()->add_component_to_entity(fps_text, TransformComponent{glm::vec3{100,100,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    Game::Instance()->get_ecs()->add_component_to_entity(fps_text, TextComponent{"HelloWorld", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    text_renderer->init();
    
    // TODO here render a 3d MESH cube
    mesh_renderer = Game::Instance()->get_ecs()->register_system<MeshRenderSystem>(); // TODO maybe a state should have it's own ECS
    
    std::default_random_engine rand;
    std::uniform_real_distribution<float> rand_rot(0.0f, 360.0f);
    
    float x = -4.5;
    for(int i = 0; i < 4; i++)
    {
        
        glm::vec3 pos = {x, 0, -10};
        glm::vec3 rotation = {rand_rot(rand),rand_rot(rand),rand_rot(rand)};
        glm::vec3 scale = {1.0f, 1.0f, 1.0f};
        
        Entity cube = Game::Instance()->get_ecs()->create_entity();
        Game::Instance()->get_ecs()->add_component_to_entity(cube, MeshComponent{"../res/object/cube/cube.obj", NULL});
        Game::Instance()->get_ecs()->add_component_to_entity(cube, ShaderComponent{"../res/shaders/model_loading.vert",
                                                                                   "../res/shaders/model_loading.frag",
                                                                                   NULL});
        Game::Instance()->get_ecs()->add_component_to_entity(cube, TransformComponent{pos,rotation,scale});
        x += 3;
    }
    mesh_renderer->init();
}

bool TestState::onExit()
{
}