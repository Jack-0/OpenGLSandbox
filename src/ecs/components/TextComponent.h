//
// Created by jack on 11/01/2021.
//

#ifndef OPENGLSANDBOX_TEXTCOMPONENT_H
#define OPENGLSANDBOX_TEXTCOMPONENT_H

#include <glm/glm.hpp>

static const int PIXEL_HEIGHT = 48;

struct TextComponent
{
    std::string text;
    glm::vec3 colour;
    unsigned int vao; // TODO maybe these need to be in shader
    unsigned int vbo; // TODO maybe these need to be in shader
    float scale;
};

#endif //OPENGLSANDBOX_TEXTCOMPONENT_H
