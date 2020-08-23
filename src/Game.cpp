//
// Created by jack on 22/08/2020.
//

#include <state/TestState.h>
#include <std_image.h>
#include <glad/glad.h>
#include "Game.h"


Game* Game::s_pInstance = 0; // singleton

int Game::initGL()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    //GLFWwindow* m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "LearnOpenGL", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_window);
    ///glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    ///glfwSetCursorPosCallback(m_window, mouse_callback);
    ///glfwSetScrollCallback(m_window, scroll_callback);

    // tell GLFW to capture our mouse
    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // TODO: FOR DEBUG to keep mouse upon error

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    return 0;
}

int Game::init(int window_width, int window_height)
{
    m_windowWidth = window_width;
    m_windowHeight = window_height;

    if ( initGL() == -1 )
        return -1;

    // build and compile shaders
    // -------------------------

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new TestState());

    m_running = true;

    //m_cube = new Cube();
    // TODO

    /*

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture coord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
     */

   return 0;
}

void Game::handleEvents()
{
    // if the window is closed end the game loop
    if( glfwWindowShouldClose(m_window) )
        m_running = false;

    // if escape is pressed close the window
    if (glfwGetKey(m_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(m_window, true);

}

void Game::update()
{
    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Game::render()
{}

void Game::clean()
{
    glfwTerminate();
}


