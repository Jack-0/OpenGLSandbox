#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


#include <iostream>
#include <string>
#include "Shader.h"

#define STB_IMAGE_IMPLEMENTATION
#include "std_image.h"

// functions
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);
int centerWindow(GLFWwindow* window);
unsigned int createTexture(char* file_path, int32_t internalFormat);
GLFWwindow* create_window();
static unsigned int CompileShader( unsigned int type, const std::string& source);
static unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{
    GLFWwindow* window = create_window();
    if (window == nullptr)
        return -1;

    float vertices[] = {
            // positions          // colors           // texture coords
             0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
             0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
            -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
            -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
    };

    unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    // texture attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    //glBindVertexArray(0);

    // as we only have a single shader, we could also just activate our shader once beforehand if we want to
    Shader shader_test("../res/shaders/basic.vert", "../res/shaders/basic.frag");
    shader_test.use();

    unsigned int texture1 = createTexture("../res/img/container.jpg", GL_RGB);

    // flip face
    stbi_set_flip_vertically_on_load(true);

    unsigned int texture2 = createTexture("../res/img/awesomeface.png", GL_RGBA);

    // either set it manually like so:
    glUniform1i(glGetUniformLocation(shader_test.program_id, "texture1"), 0);
    // or set it via the texture class
    shader_test.setInt("texture2", 1);

    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // change poly mode to only show lines

    // TODO new
    glm::vec4 vec(1.0f, 0.0f, 0.0f, 1.0f);
    glm::mat4 trans = glm::mat4(1.0f);
    trans = glm::translate(trans, glm::vec3(1.0f, 1.0f, 0.0f));
    vec = trans * vec;
    std::cout << vec.x << vec.y << vec.z << std::endl;



    // render loop
    while (!glfwWindowShouldClose(window))
    {
        // input
        processInput(window);

        // render
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // render the triangle
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, texture2);

        //
        shader_test.use();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // swap front and back buffers
        glfwSwapBuffers(window);
        // poll
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw terminate, clearing all previously allocated GLFW resources.
    glfwTerminate();
    return 0;
}

unsigned int createTexture(char* file_path, int32_t internalFormat)
{
// texture
    unsigned int texture;
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    // load and generate the texture
    int width, height, nrChannels;
    unsigned char *data = stbi_load(file_path, &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, internalFormat, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    return texture;
}

/**
 * query GLFW inputs
 * @param window
 */
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}


/**
 * set window to center of screen
 * @param window
 * @return
 */
int centerWindow(GLFWwindow *window)
{
    GLFWmonitor *monitor = glfwGetPrimaryMonitor();
    if (!monitor)
        return -1;

    const GLFWvidmode *mode = glfwGetVideoMode(monitor);
    if (!mode)
        return -1;

    int monitorX, monitorY;
    glfwGetMonitorPos(monitor, &monitorX, &monitorY);

    int windowWidth, windowHeight;
    glfwGetWindowSize(window, &windowWidth, &windowHeight);

    glfwSetWindowPos(window,
                     monitorX + (mode->width - windowWidth) / 2,
                     monitorY + (mode->height - windowHeight) / 2);

    return 0;
}


/**
 * GLFW callback function called whenever the window size changes
 * @param window
 * @param width
 * @param height
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


/**
 * Attempt to create and return a GLFW window
 * @return GLFWwindow*
 */
GLFWwindow* create_window()
{
    // glfw initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "OpenGL Sandbox", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }
    // center the window on within the screen
    if (centerWindow(window) == -1)
        return nullptr;

    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad load all OpenGL function pointers
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;

    return window;
}