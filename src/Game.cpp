//
// Created by jack on 22/08/2020.
//

#include <state/TestState.h>
#include <state/MenuState.h>

#define STB_IMAGE_IMPLEMENTATION
#include <glad/glad.h>
#include "Game.h"


#include <ft2build.h>
#include FT_FREETYPE_H


Game* Game::s_pInstance = 0; // singleton

int Game::initGL()
{

    // TODO font test
    FT_Library ft;
    if (FT_Init_FreeType(&ft))
    {
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
        return -1;
    }

    FT_Face face;
    if (FT_New_Face(ft, "../res/fonts/Roboto/Roboto-Black.ttf", 0, &face))
    {
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
        return -1;
    }

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

    // TODO test
    m_camera = new Camera (glm::vec3(0.0f, 0.0f, 3.0f));


    m_pGameStateMachine = new GameStateMachine();
    //m_pGameStateMachine->changeState(new TestState());
    m_pGameStateMachine->changeState(new MenuState());

    m_running = true;

    m_previousFrame = glfwGetTime();

    glfwSetWindowUserPointer(m_window, this);
    glfwSetCursorPosCallback(m_window, mouse_callback); // TODO clean code


    m_lastMouseX = m_windowWidth / 2.0f;
    m_lastMouseY = m_windowHeight / 2.0f;

    // remove cursor and keep mouse focus
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);


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

    // camera
    if (glfwGetKey(m_window, GLFW_KEY_W) == GLFW_PRESS)
        m_camera->ProcessKeyboard(FORWARD, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_S) == GLFW_PRESS)
        m_camera->ProcessKeyboard(BACKWARD, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_A) == GLFW_PRESS)
        m_camera->ProcessKeyboard(LEFT, m_deltaTime);
    if (glfwGetKey(m_window, GLFW_KEY_D) == GLFW_PRESS)
        m_camera->ProcessKeyboard(RIGHT, m_deltaTime);

}

void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::render()
{
    // render
    // ------
    glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    m_pGameStateMachine->render();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    // -------------------------------------------------------------------------------
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Game::calculate_fps()
{
    // TIME
    float currentFrame = glfwGetTime(); // todo
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    // calculate fps
    m_frameCount++;
    if ( currentFrame - m_previousFrame >= 1.0)
    {
        std::cout << "FPS=" << m_frameCount << std::endl;
        m_frameCount = 0;
        m_previousFrame = currentFrame;
    }
}

void Game::clean()
{
    glfwTerminate();
}


 void Game::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{

    if (Game::Instance()->m_firstMouse)
    {
        Game::Instance()->m_lastMouseX = xpos;
        Game::Instance()->m_lastMouseY = ypos;
        Game::Instance()->m_firstMouse = false;
    }

    float xoffset = xpos - Game::Instance()->m_lastMouseX;
    float yoffset = Game::Instance()->m_lastMouseY - ypos; // reversed since y-coordinates go from bottom to top

    Game::Instance()->m_lastMouseX = xpos;
    Game::Instance()->m_lastMouseY = ypos;

    Game::Instance()->getCamera()->ProcessMouseMovement(xoffset, yoffset);
}
