//
// Created by jack on 30/12/2020.
//

#ifndef OPENGLSANDBOX_TRANSFORMCOMPONENT_H
#define OPENGLSANDBOX_TRANSFORMCOMPONENT_H


struct TransformComponent
{
    glm::vec3 pos = {0,0,0};
    glm::vec3 rotation = {0,0,0};
    glm::vec3 scale = {1.0f,1.0f,1.0f};
};

#endif //OPENGLSANDBOX_TRANSFORMCOMPONENT_H
