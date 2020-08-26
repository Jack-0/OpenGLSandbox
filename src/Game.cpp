//
// Created by jack on 22/08/2020.
//

#include <state/TestState.h>
#include <std_image.h>
#define STB_IMAGE_IMPLEMENTATION
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

    // TODO test
    m_camera = new Camera (glm::vec3(0.0f, 0.0f, 3.0f));

    ourShader = new Shader("../res/shaders/model_loading.vert", "../res/shaders/model_loading.frag");
    // load models
    // -----------
    ourModel = new Model("../res/object/backpack/backpack.obj");

    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new TestState());

    m_running = true;

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

    // TODO use model
    // don't forget to enable shader before setting uniforms
    ourShader->use();

    // view/projection transformations
    glm::mat4 projection = glm::perspective(glm::radians(m_camera->Zoom), (float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.0f);
    glm::mat4 view = m_camera->GetViewMatrix();
    ourShader->setMat4("projection", projection);
    ourShader->setMat4("view", view);

    // render the loaded model
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f)); // translate it down so it's at the center of the scene
    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));	// it's a bit too big for our scene, so scale it down
    ourShader->setMat4("model", model);
    ourModel->Draw(*ourShader);

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


