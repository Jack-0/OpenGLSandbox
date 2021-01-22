//
// Created by jack on 08/01/2021.
//

#ifndef OPENGLSANDBOX_TEXTRENDERSYSTEM_H
#define OPENGLSANDBOX_TEXTRENDERSYSTEM_H


#include <ecs/core/System.h>

#include <map>

#include <glm/glm.hpp>

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};


class TextRenderSystem : public System
{
    std::map<char, Character> characters;
    
public:
    
    void init();
    void render();
};

#endif //OPENGLSANDBOX_TEXTRENDERSYSTEM_H
