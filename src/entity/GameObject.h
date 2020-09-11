//
// Created by jack on 11/09/2020.
//

#ifndef OPENGLSANDBOX_GAMEOBJECT_H
#define OPENGLSANDBOX_GAMEOBJECT_H

#include <util/Model.h>
#include <graphics/Shader.h>

class GameObject
{
public:
    virtual void update() = 0;
    virtual void render() = 0;
    virtual void clean()  = 0;

protected:
    GameObject() {}
    virtual ~GameObject() {}

    // vertices and texture data
    Model* m_model;
    Shader* m_shader;
    // camera matrices
    glm::mat4 m_projection;
    glm::mat4 m_view;
};

#endif //OPENGLSANDBOX_GAMEOBJECT_H

