//
// Created by jack on 06/10/2020.
//

#include <iostream>
#include "MenuState.h"
#include "TestState.h"

#include <Game.h>
#include <GLFW/glfw3.h>
#include <ecs/components/FunctionPointerComponent.h>

const std::string MenuState::s_StateID = "MENU";


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
    
    text_system = Game::Instance()->get_ecs()->register_system<TextRenderSystem>();
    {
        Signature text_sig;
        text_sig.set(Game::Instance()->get_ecs()->get_component_type_id<ShaderComponent>());
        text_sig.set(Game::Instance()->get_ecs()->get_component_type_id<TransformComponent>());
        text_sig.set(Game::Instance()->get_ecs()->get_component_type_id<TextComponent>());
        text_sig.set(Game::Instance()->get_ecs()->get_component_type_id<Dimensions2DComponent>());
        Game::Instance()->get_ecs()->set_system_sig<TextRenderSystem>(text_sig);
    }
    
    menu_system = Game::Instance()->get_ecs()->register_system<MenuSystem>();
    {
        Signature text_sig;
        text_sig.set(Game::Instance()->get_ecs()->get_component_type_id<ShaderComponent>());
        text_sig.set(Game::Instance()->get_ecs()->get_component_type_id<TransformComponent>());
        text_sig.set(Game::Instance()->get_ecs()->get_component_type_id<TextComponent>());
        text_sig.set(Game::Instance()->get_ecs()->get_component_type_id<Dimensions2DComponent>());
        text_sig.set(Game::Instance()->get_ecs()->get_component_type_id<FunctionPointerComponent>());
        Game::Instance()->get_ecs()->set_system_sig<MenuSystem>(text_sig);
    }
    
    Entity title_text = Game::Instance()->get_ecs()->create_entity();
    Game::Instance()->get_ecs()->add_component_to_entity(title_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    Game::Instance()->get_ecs()->add_component_to_entity(title_text, TransformComponent{glm::vec3{10,Game::Instance()->getScreenHeight()-PIXEL_HEIGHT-10,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    Game::Instance()->get_ecs()->add_component_to_entity(title_text, TextComponent{"Hello OpenGL", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    Game::Instance()->get_ecs()->add_component_to_entity(title_text, Dimensions2DComponent{0,0});
    
    Entity demo1_text = Game::Instance()->get_ecs()->create_entity();
    Game::Instance()->get_ecs()->add_component_to_entity(demo1_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    Game::Instance()->get_ecs()->add_component_to_entity(demo1_text, TransformComponent{glm::vec3{30,Game::Instance()->getScreenHeight()-PIXEL_HEIGHT-10 - PIXEL_HEIGHT*2,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    Game::Instance()->get_ecs()->add_component_to_entity(demo1_text, TextComponent{"> Cubes", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    Game::Instance()->get_ecs()->add_component_to_entity(demo1_text, Dimensions2DComponent{0,0});
    Game::Instance()->get_ecs()->add_component_to_entity(demo1_text, FunctionPointerComponent{demo1});
    
    Entity demo2_text = Game::Instance()->get_ecs()->create_entity();
    Game::Instance()->get_ecs()->add_component_to_entity(demo2_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    Game::Instance()->get_ecs()->add_component_to_entity(demo2_text, TransformComponent{glm::vec3{30,Game::Instance()->getScreenHeight()-PIXEL_HEIGHT-1 - PIXEL_HEIGHT*4,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    Game::Instance()->get_ecs()->add_component_to_entity(demo2_text, TextComponent{"> Demo", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    Game::Instance()->get_ecs()->add_component_to_entity(demo2_text, Dimensions2DComponent{0,0});
    Game::Instance()->get_ecs()->add_component_to_entity(demo2_text, FunctionPointerComponent{demo2});
    
    Entity exit_text = Game::Instance()->get_ecs()->create_entity();
    Game::Instance()->get_ecs()->add_component_to_entity(exit_text, ShaderComponent{"../res/shaders/text.vert", "../res/shaders/text.frag", NULL});
    Game::Instance()->get_ecs()->add_component_to_entity(exit_text, TransformComponent{glm::vec3{30,Game::Instance()->getScreenHeight()-PIXEL_HEIGHT-1 - PIXEL_HEIGHT*6,0} ,glm::vec3 {0,0,0},glm::vec3 {1,1,1}});
    Game::Instance()->get_ecs()->add_component_to_entity(exit_text, TextComponent{"> Exit", glm::vec3{255,255,255}, NULL, NULL, 1.0f});
    Game::Instance()->get_ecs()->add_component_to_entity(exit_text, Dimensions2DComponent{0,0});
    Game::Instance()->get_ecs()->add_component_to_entity(exit_text, FunctionPointerComponent{exit});
    
    m_entities.push_back(title_text);
    m_entities.push_back(demo1_text);
    m_entities.push_back(demo2_text);
    m_entities.push_back(exit_text);
    
    text_system->init();
    
}

bool MenuState::onExit()
{
    // clean entities
    for (auto const& entity : m_entities)
    {
        Game::Instance()->get_ecs()->destroy_entity(entity);
    }
    
    // hide mouse and ensure the cursor is centered for the scene
    glfwSetCursorPos(Game::Instance()->getWindow(), Game::Instance()->getScreenWidth()/2, Game::Instance()->getScreenHeight()/2);
    glfwSetInputMode(Game::Instance()->getWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED); // hide mouse
    
}

void MenuState::demo1()
{
    Game::Instance()->getStateMachine()->changeState(new TestState());
}

void MenuState::demo2()
{
    Game::Instance()->getStateMachine()->changeState(new TestState());
}

void MenuState::exit()
{
    Game::Instance()->end_loop();
}