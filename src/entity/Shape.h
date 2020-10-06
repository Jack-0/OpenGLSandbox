//
// Created by jack on 12/09/2020.
//

#ifndef OPENGLSANDBOX_SHAPE_H
#define OPENGLSANDBOX_SHAPE_H


#include "GameObject.h"
//#include <vector>

class Shape : GameObject
{
public:
    Shape();
    void update();
    void render();
    void clean();
private:
    //vector<float> m_vertices;
    float* vertices;
    unsigned int m_vbo;
    unsigned int  m_vao;
    unsigned int m_texture;
    Shader* m_shader;
};


#endif //OPENGLSANDBOX_SHAPE_H
