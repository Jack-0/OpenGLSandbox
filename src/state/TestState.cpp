//
// Created by jack on 22/08/2020.
//

#include <iostream>
#include <Game.h>
#include "TestState.h"


#include <glad/glad.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

const std::string TestState::s_StateID = "TEST";

void TestState::update() {
    m_cube->update();
    m_cube2->move(test,0,0);
    test += 0.0001f;
    m_cube2->update();
    m_shape->update();
}

void TestState::render() {
    //m_cube->render();
    m_shape->render();
    m_cube2->render();

    //glEnable(GL_DEPTH_TEST);
    //glBindVertexArray(vao);
    //glDrawElements(GL_LINES, length, GL_UNSIGNED_INT, NULL);
    //glBindVertexArray(0);
    //glDisable(GL_DEPTH_TEST);

}

bool TestState::onEnter(){
    std::cout  << "State \"" <<s_StateID << "\" loaded!" << std::endl;
    m_cube = new Cube("../res/object/cube/cube.obj","../res/shaders/model_loading.vert","../res/shaders/model_loading.frag");
    m_cube2 = new Cube("../res/object/cube/cube.obj","../res/shaders/model_loading.vert","../res/shaders/model_loading.frag");
    m_shape = new Shape();

    std::vector<glm::vec3> vertices;
    std::vector<glm::uvec4> indices;

    for(int j=0; j<=slices; ++j) {
        for(int i=0; i<=slices; ++i) {
            float x = (float)i/(float)slices;
            float y = 0;
            float z = (float)j/(float)slices;
            vertices.push_back(glm::vec3(x, y, z));
        }
    }

    for(int j=0; j<slices; ++j) {
        for(int i=0; i<slices; ++i) {

            int row1 =  j    * (slices+1);
            int row2 = (j+1) * (slices+1);

            indices.push_back(glm::uvec4(row1+i, row1+i+1, row1+i+1, row2+i+1));
            indices.push_back(glm::uvec4(row2+i+1, row2+i, row2+i, row1+i));

        }
    }

    glGenVertexArrays( 1, &vao );
    glBindVertexArray( vao );

    glGenBuffers( 1, &vbo );
    glBindBuffer( GL_ARRAY_BUFFER, vbo );
    glBufferData( GL_ARRAY_BUFFER, vertices.size()*sizeof(glm::vec3), &vertices[0][0], GL_STATIC_DRAW );
    glEnableVertexAttribArray( 0 );
    glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, nullptr );

    glGenBuffers( 1, &ibo );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo );
    glBufferData( GL_ELEMENT_ARRAY_BUFFER, indices.size()*sizeof(glm::uvec4), &indices[0][0], GL_STATIC_DRAW);

    glBindVertexArray(0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    length = indices.size()*4;

}

bool TestState::onExit() {}