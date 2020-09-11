//
// Created by jack on 22/08/2020.
//

#ifndef OPENGLSANDBOX_GAME_H
#define OPENGLSANDBOX_GAME_H

#include <iostream>
#include <state/GameStateMachine.h>

#include <glad/glad.h> // TODO the order really matters
#include <GLFW/glfw3.h> // TODO ^

// todo add vbo vao
// setup to be a opengl wrapper
#include <graphics/Camera.h>


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
    void render();
    void update();
    void handleEvents();

    void calculate_fps();

    void clean();

    bool running() { return m_running;}

    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

    GLFWwindow* getWindow() { return m_window; }

    Camera* getCamera() { return m_camera; }

    int getScreenWidth() { return m_windowWidth; }
    int getScreenHeight() { return m_windowHeight; }


    // mouse
    float m_lastMouseX = 0.0f;
    float m_lastMouseY = 0.0f;
    bool m_firstMouse = true;


private:

    static void mouse_callback(GLFWwindow* window, double xpos, double ypos); // TODO

    int initGL();

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

    Camera* m_camera;


};


#endif //OPENGLSANDBOX_GAME_H
