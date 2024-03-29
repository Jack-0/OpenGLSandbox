//
// Created by jack on 06/10/2020.
//

#include <iostream>
#include "MenuState.h"
#include "CubeDemoState.h"
#include "ModelShowState.h"
#include "PracticeState.h"

#include <Game.h>
#include <GLFW/glfw3.h>
#include <ecs/components/FunctionPointerComponent.h>
#include <ecs/components/ShaderComponent.h>
#include <ecs/components/TransformComponent.h>
#include <ecs/components/TextComponent.h>
#include <ecs/components/Dimensions2DComponent.h>

const std::string MenuState::s_StateID = "MENU";

// aliases for the Game singleton

void MenuState::update()
{
    m_menu_system->update();
}

void MenuState::render()
{
    m_text_system->render();
}

bool MenuState::onEnter()
{
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    
    m_text_system = ecs->register_system<TextRenderSystem>();
    {
        Signature sig;
        sig.set(ecs->get_component_type_id<ShaderComponent>());
        sig.set(ecs->get_component_type_id<TransformComponent>());
        sig.set(ecs->get_component_type_id<TextComponent>());
        sig.set(ecs->get_component_type_id<Dimensions2DComponent>());
        ecs->set_system_sig<TextRenderSystem>(sig);
    }
    
    m_menu_system = ecs->register_system<MenuSystem>();
    {
        Signature sig;
        sig.set(ecs->get_component_type_id<ShaderComponent>());
        sig.set(ecs->get_component_type_id<TransformComponent>());
        sig.set(ecs->get_component_type_id<TextComponent>());
        sig.set(ecs->get_component_type_id<Dimensions2DComponent>());
        sig.set(ecs->get_component_type_id<FunctionPointerComponent>());
        ecs->set_system_sig<MenuSystem>(sig);
    }


    // show mouse
    glfwSetInputMode(game->getWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    
    // create menu title component
    Entity title_text = ecs->create_entity();
    ecs->add_component_to_entity(title_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(title_text, TransformComponent{glm::vec3{10,game->getScreenHeight()-PIXEL_HEIGHT-10,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(title_text, TextComponent{"Hello OpenGL", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(title_text, Dimensions2DComponent{0,0});
    
    // create menu button component
    Entity demo1_text = ecs->create_entity();
    ecs->add_component_to_entity(demo1_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(demo1_text, TransformComponent{glm::vec3{30,game->getScreenHeight()-PIXEL_HEIGHT-10 - PIXEL_HEIGHT*2,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(demo1_text, TextComponent{"> Cubes", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(demo1_text, Dimensions2DComponent{0,0});
    ecs->add_component_to_entity(demo1_text, FunctionPointerComponent{demo1});
    
    // create menu button component
    Entity demo2_text = ecs->create_entity();
    ecs->add_component_to_entity(demo2_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(demo2_text, TransformComponent{glm::vec3{30,game->getScreenHeight()-PIXEL_HEIGHT-1 - PIXEL_HEIGHT*4,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(demo2_text, TextComponent{"> Model", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(demo2_text, Dimensions2DComponent{0,0});
    ecs->add_component_to_entity(demo2_text, FunctionPointerComponent{demo2});
    
    // create menu button component
    Entity demo3_text = ecs->create_entity();
    ecs->add_component_to_entity(demo3_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(demo3_text, TransformComponent{glm::vec3{30,game->getScreenHeight()-PIXEL_HEIGHT-1 - PIXEL_HEIGHT*6,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(demo3_text, TextComponent{"> Practice", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(demo3_text, Dimensions2DComponent{0,0});
    ecs->add_component_to_entity(demo3_text, FunctionPointerComponent{demo3});
    
    // create menu button component
    Entity exit_text = ecs->create_entity();
    ecs->add_component_to_entity(exit_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    ecs->add_component_to_entity(exit_text, TransformComponent{glm::vec3{30,game->getScreenHeight()-PIXEL_HEIGHT-1 - PIXEL_HEIGHT*8,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    ecs->add_component_to_entity(exit_text, TextComponent{"> Exit", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    ecs->add_component_to_entity(exit_text, Dimensions2DComponent{0,0});
    ecs->add_component_to_entity(exit_text, FunctionPointerComponent{exit});
    


    // init the text system todo review
    m_text_system->init();

    // TODO this needs to be handled on creation of an entity - MAYBE A STATE SHOULD HAVE ADD ENTITY OPTION instead of using game ecs()
    m_entities.push_back(title_text); 
    m_entities.push_back(demo1_text);
    m_entities.push_back(demo2_text);
    m_entities.push_back(demo3_text);
    m_entities.push_back(exit_text);
}

bool MenuState::onExit()
{
    // hide mouse and ensure the cursor is centered for the scene
    glfwSetCursorPos(game->getWindow(), game->getScreenWidth()/2, game->getScreenHeight()/2);
    glfwSetInputMode(game->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide mouse TODO UNCOMMENT
}

// bug due to callback state changes before we can clean ... Maybe remove callbacks with observer pattern?
void MenuState::demo1()
{
    game->getStateMachine()->changeState(new CubeDemoState());
}

void MenuState::demo2()
{
    game->getStateMachine()->changeState(new ModelShowState());
}

void MenuState::demo3()
{
    game->getStateMachine()->changeState(new PracticeState());
}

void MenuState::exit()
{
    game->end_loop();
}

void MenuState::clean()
{
    // todo clean entities
    for (Entity e : m_entities)
    {
        //ecs->remove_component<TextComponent>(e);
        ecs->destroy_entity(e);
    }
}