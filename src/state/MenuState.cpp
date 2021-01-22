//
// Created by jack on 06/10/2020.
//

#include <iostream>
#include "MenuState.h"
#include "TestState.h"

#include <Game.h>
#include <GLFW/glfw3.h>
#include <ecs/components/FunctionPointerComponent.h>
#include <ecs/components/ShaderComponent.h>
#include <ecs/components/TransformComponent.h>
#include <ecs/components/TextComponent.h>
#include <ecs/components/Dimensions2DComponent.h>

const std::string MenuState::s_StateID = "MENU";

// aliases for the Game singleton
#define game Game::Instance()
#define ecs Game::Instance()->get_ecs()
#define menu_system Game::Instance()->get_menu_system()
#define text_system Game::Instance()->get_text_system()

void MenuState::update()
{
    menu_system->update();
}

void MenuState::render()
{
    text_system->render();
}

bool MenuState::onEnter()
{
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    
    // show mouse
    glfwSetInputMode(Game::Instance()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    // create menu title component
    Entity title_text = ecs->create_entity();
    ecs->add_component_to_entity(title_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(title_text, TransformComponent{glm::vec3{10,Game::Instance()->getScreenHeight()-PIXEL_HEIGHT-10,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(title_text, TextComponent{"Hello OpenGL", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(title_text, Dimensions2DComponent{0,0});
    
    // create menu button component
    Entity demo1_text = ecs->create_entity();
    ecs->add_component_to_entity(demo1_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(demo1_text, TransformComponent{glm::vec3{30,Game::Instance()->getScreenHeight()-PIXEL_HEIGHT-10 - PIXEL_HEIGHT*2,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(demo1_text, TextComponent{"> Cubes", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(demo1_text, Dimensions2DComponent{0,0});
    ecs->add_component_to_entity(demo1_text, FunctionPointerComponent{demo1});
    
    // create menu button component
    Entity demo2_text = ecs->create_entity();
    ecs->add_component_to_entity(demo2_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(demo2_text, TransformComponent{glm::vec3{30,Game::Instance()->getScreenHeight()-PIXEL_HEIGHT-1 - PIXEL_HEIGHT*4,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(demo2_text, TextComponent{"> Demo", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(demo2_text, Dimensions2DComponent{0,0});
    ecs->add_component_to_entity(demo2_text, FunctionPointerComponent{demo2});
    
    // create menu button component
    Entity exit_text = ecs->create_entity();
    ecs->add_component_to_entity(exit_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(exit_text, TransformComponent{glm::vec3{30,Game::Instance()->getScreenHeight()-PIXEL_HEIGHT-1 - PIXEL_HEIGHT*6,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(exit_text, TextComponent{"> Exit", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(exit_text, Dimensions2DComponent{0,0});
    ecs->add_component_to_entity(exit_text, FunctionPointerComponent{exit});
    
    // init the text system todo review
    text_system->init();
}

bool MenuState::onExit()
{
    // todo clean entities
    
    // hide mouse and ensure the cursor is centered for the scene
    glfwSetCursorPos(game->getWindow(), game->getScreenWidth()/2, game->getScreenHeight()/2);
    glfwSetInputMode(game->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide mouse
    
}

void MenuState::demo1()
{
    game->getStateMachine()->changeState(new TestState());
}

void MenuState::demo2()
{
    game->getStateMachine()->changeState(new TestState());
}

void MenuState::exit()
{
    game->end_loop();
}