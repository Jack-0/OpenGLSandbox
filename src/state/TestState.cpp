//
// Created by jack on 22/08/2020.
//

#include <iostream>
#include <Game.h>
#include "TestState.h"


#include <GLFW/glfw3.h>
#include <ecs/ECSManager.h>
#include <ecs/systems/MeshRenderSystem.h>

const std::string TestState::s_StateID = "TEST";

void TestState::update()
{
}

void TestState::render() {
    mesh_renderer->render();
}

bool TestState::onEnter(){
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    
    Game::Instance()->get_ecs()->register_component<MeshComponent>();
    Game::Instance()->get_ecs()->register_component<ShaderComponent>();
    Game::Instance()->get_ecs()->register_component<TransformComponent>();
    
    // TODO here render a 3d MESH cube
    mesh_renderer = Game::Instance()->get_ecs()->register_system<MeshRenderSystem>(); // TODO maybe a state should have it's own ECS
    
    Entity cube = Game::Instance()->get_ecs()->create_entity();
    Game::Instance()->get_ecs()->add_component_to_entity(cube, MeshComponent{"../res/object/cube/cube.obj", NULL});
    Game::Instance()->get_ecs()->add_component_to_entity(cube, ShaderComponent{"../res/shaders/model_loading.vert","../res/shaders/model_loading.frag", NULL});
    Game::Instance()->get_ecs()->add_component_to_entity(cube, TransformComponent{{0,0,0},{0,0,0},{1,1,1}});
    
    mesh_renderer->init();
}

bool TestState::onExit()
{
}