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
#include <graphics/Shader.h>

#include <util/Model.h>
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

    void clean();

    bool running() { return m_running;}

    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }

    GLFWwindow* getWindow() { return m_window; }

    //int getScreenWidth() { return m_screenWidth; }
    //int getScreenHeight() { return m_screenHeight; }

private:

    int initGL();

    int m_windowWidth;
    int m_windowHeight;


    Game() {}

    bool m_running = false;

    static Game* s_pInstance;

    GameStateMachine* m_pGameStateMachine;

    GLFWwindow* m_window;

    Camera* m_camera;
    Shader* ourShader;
    Model* ourModel;
};


#endif //OPENGLSANDBOX_GAME_H
