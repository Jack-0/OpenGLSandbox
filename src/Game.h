//
// Created by jack on 22/08/2020.
//

#ifndef OPENGLSANDBOX_GAME_H
#define OPENGLSANDBOX_GAME_H

#include <iostream>
#include <state/GameStateMachine.h>

#include <glad/glad.h> // TODO the order really matters
#include <GLFW/glfw3.h> // TODO ^

// setup to be a opengl wrapper
#include <graphics/Camera.h>
#include <ecs/ECSManager.h>

#include <ecs/systems/TextRenderSystem.h>
#include <ecs/systems/MenuSystem.h>


class Game
{
public:
    ~Game() {}

    /// Ensure game is a singleton
    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
    }


    int init(int window_width, int window_height);
    
    // core
    void render();
    void update();
    void handleEvents();
    void end_loop();
    void clean();
    

    // util
    void calculate_fps();
    
    // encapsulation
    int getScreenWidth() { return m_windowWidth; }
    int getScreenHeight() { return m_windowHeight; }
    int getFPS() {return m_fps; }
    bool running() { return m_running;}
    
    // mouse
    float m_lastMouseX = 0.0f;
    float m_lastMouseY = 0.0f;
    bool m_firstMouse = true;
    bool m_left_click = false; // TODO bit of a hack try subscriber model


    // ECS wrappers
    template<typename T>
    void ecs_register_component();
    
    template<typename T>
    void ecs_register_system();
    
    
    
    // pointers
    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }
    GLFWwindow* getWindow() { return m_window; }
    Camera* getCamera() { return m_camera; }
    
    // ecs
    ECSManager* get_ecs() { return m_ecs; }
    
    // system
    std::shared_ptr<TextRenderSystem> get_text_system() {return m_text_system; }
    std::shared_ptr<MenuSystem> get_menu_system() { return m_menu_system; }
    
    

private:

    // pointer to the Entity component system
    ECSManager* m_ecs;
    
    // systems
    std::shared_ptr<TextRenderSystem> m_text_system;
    std::shared_ptr<MenuSystem> m_menu_system;
 
    // callbacks
    static void mouse_callback(GLFWwindow* window, double xpos, double ypos); // TODO
    static void window_size_callback(GLFWwindow* window, int width, int height);
    static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
    
    // init ecs
    void init_ecs();
    // init system
    void init_systems();
    
    // initialise openGL
    int init_gl();

    // window dimensions
    int m_windowWidth;
    int m_windowHeight;


    Game() {}

    bool m_running = false;

    static Game* s_pInstance;

    GameStateMachine* m_pGameStateMachine;

    GLFWwindow* m_window;

    float m_deltaTime = 0.0f;
    float m_previousFrame = 0.0f;
    int m_frameCount = 0;
    float m_lastFrame = 0.0f;
    int m_fps = 0; // store frames per second

    Camera* m_camera;

    glm::vec3 m_bgColor = {0,0,0};
};


#endif //OPENGLSANDBOX_GAME_H
