//
// Created by jack on 22/08/2020.
//

#include <state/MenuState.h>

#define STB_IMAGE_IMPLEMENTATION
#include "Game.h"

#include <glad/glad.h>
#include <ecs/components/MeshComponent.h>
#include <ecs/components/ShaderComponent.h>
#include <ecs/components/Dimensions2DComponent.h>
#include <ecs/components/TextComponent.h>
#include <ecs/components/TransformComponent.h>
#include <ecs/components/FunctionPointerComponent.h>

Game* Game::s_pInstance = 0; // singleton

int Game::init_gl()
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
    //GLFWwindow* m_window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    m_window = glfwCreateWindow(m_windowWidth, m_windowHeight, "OpenGL Sandbox", NULL, NULL);
    if (m_window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(m_window);

    // get primary monitor for window centering
    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    // window
    if (!monitor)
        return -1;

    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    if (!mode)
        return -1;

    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);

    int windowWidth, windowHeight;
    glfwGetWindowSize(m_window, &windowWidth, &windowHeight);
    // center window on screen/monitor
    glfwSetWindowPos(m_window,
                     monitorX + (mode->width - windowWidth) / 2,
                     monitorY + (mode->height - windowHeight) / 2);

    // set window minimum size
    glfwSetWindowSizeLimits(m_window, windowWidth, windowHeight, 1920, 1080);

    ///glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback);
    ///glfwSetCursorPosCallback(m_window, mouse_callback);
    ///glfwSetScrollCallback(m_window, scroll_callback);
    

    // tell GLFW to capture our mouse
    glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    //glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL); // TODO: FOR DEBUG to keep mouse upon error

    // glad: load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    //stbi_set_flip_vertically_on_load(true);

    // configure global opengl state
    glEnable(GL_DEPTH_TEST);

    
    return 0;
}

int Game::init(int window_width, int window_height)
{
    m_windowWidth = window_width;
    m_windowHeight = window_height;

    // initialise OpenGL
    if (init_gl() == -1 )
        return -1;

    // set camera pointer
    m_camera = new Camera (glm::vec3(0.0f, 0.0f, 3.0f));


    // set game state to running
    m_running = true;

    // init previous frame time
    m_previousFrame = glfwGetTime();

    // callbacks
    glfwSetWindowUserPointer(m_window, this);
    glfwSetCursorPosCallback(m_window, mouse_callback); // TODO clean code
    glfwSetWindowSizeCallback(m_window, window_size_callback);
    glfwSetMouseButtonCallback(m_window, mouse_button_callback);
    glfwSetFramebufferSizeCallback(m_window, frame_buffer_size_callback);
    
    // set last mouse pos TODO review this
    m_lastMouseX = m_windowWidth / 2.0f;
    m_lastMouseY = m_windowHeight / 2.0f;

    // ensure the cursor is centered for the scene
    glfwSetCursorPos(m_window, window_width/2, window_height/2);
    
    // init entity component system
    init_ecs();
    // init systems
    init_systems();
    
    
    // init state machine and start the Game in the MenuState
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new MenuState());
//    m_pGameStateMachine->changeState(new MenuState());
    
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
    
    if (glfwGetKey(m_window, GLFW_KEY_E) == GLFW_PRESS)
        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
    
    if (glfwGetKey(m_window, GLFW_KEY_F) == GLFW_PRESS)
        glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

void Game::update()
{
    m_pGameStateMachine->update();
}

void Game::render()
{
    // render
    glClearColor(m_bgColor.x, m_bgColor.y, m_bgColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_pGameStateMachine->render();

    // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

void Game::calculate_fps()
{
    // time
    float currentFrame = glfwGetTime(); // todo
    m_deltaTime = currentFrame - m_lastFrame;
    m_lastFrame = currentFrame;

    // calculate fps
    m_frameCount++;
    if ( currentFrame - m_previousFrame >= 1.0)
    {
        m_fps = m_frameCount;
        m_frameCount = 0;
        m_previousFrame = currentFrame;
    }
}

void Game::clean()
{
    glfwTerminate();
}


void Game::mouse_button_callback(GLFWwindow *window, int button, int action, int mods)
{
       //TODO
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        Game::Instance()->m_left_click = true;
    else
        Game::Instance()->m_left_click = false;
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

void Game::window_size_callback(GLFWwindow *window, int width, int height)
{
    std::cout << "Window resized new width : height = " << width << " : " << height << "\n";
    Game::Instance()->m_windowWidth = width;
    Game::Instance()->m_windowHeight = height;
}

// changes view port size upon screen resize
void Game::frame_buffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0,0, width, height);
    Game::Instance()->render();
}


template<typename T>
void Game::ecs_register_component()
{
    m_ecs->register_component<T>();
}

template<typename T>
void Game::ecs_register_system()
{
  m_ecs->register_system<T>();
}

void Game::init_ecs()
{
    // define pointer and init ECS
    std::cout << "init ecs done\n";
    m_ecs = new ECSManager();
    m_ecs->init();
    std::cout << "init ecs done\n";
 
    // register all components to be used
    m_ecs->register_component<MeshComponent>();
    m_ecs->register_component<ShaderComponent>();
    m_ecs->register_component<TransformComponent>();
    m_ecs->register_component<TextComponent>();
    m_ecs->register_component<Dimensions2DComponent>();
    m_ecs->register_component<FunctionPointerComponent>();
}

void Game::init_systems()
{
    m_text_system = Game::Instance()->get_ecs()->register_system<TextRenderSystem>();
    {
        Signature sig;
        sig.set(Game::Instance()->get_ecs()->get_component_type_id<ShaderComponent>());
        sig.set(Game::Instance()->get_ecs()->get_component_type_id<TransformComponent>());
        sig.set(Game::Instance()->get_ecs()->get_component_type_id<TextComponent>());
        sig.set(Game::Instance()->get_ecs()->get_component_type_id<Dimensions2DComponent>());
        Game::Instance()->get_ecs()->set_system_sig<TextRenderSystem>(sig);
    }
    
    m_menu_system = Game::Instance()->get_ecs()->register_system<MenuSystem>();
    {
        Signature sig;
        sig.set(Game::Instance()->get_ecs()->get_component_type_id<ShaderComponent>());
        sig.set(Game::Instance()->get_ecs()->get_component_type_id<TransformComponent>());
        sig.set(Game::Instance()->get_ecs()->get_component_type_id<TextComponent>());
        sig.set(Game::Instance()->get_ecs()->get_component_type_id<Dimensions2DComponent>());
        sig.set(Game::Instance()->get_ecs()->get_component_type_id<FunctionPointerComponent>());
        Game::Instance()->get_ecs()->set_system_sig<MenuSystem>(sig);
    }
}

void Game::end_loop()
{
    m_running = false;
}

