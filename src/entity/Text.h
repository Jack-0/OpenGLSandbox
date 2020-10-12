//
// Created by jack on 12/10/2020.
//

#ifndef OPENGLSANDBOX_TEXT_H
#define OPENGLSANDBOX_TEXT_H


#include "GameObject.h"

#include <ft2build.h>
#include FT_FREETYPE_H

struct Character {
    unsigned int TextureID;  // ID handle of the glyph texture
    glm::ivec2   Size;       // Size of glyph
    glm::ivec2   Bearing;    // Offset from baseline to left/top of glyph
    unsigned int Advance;    // Offset to advance to next glyph
};


class Text : GameObject
{
public:
    static const int PIXEL_HEIGHT = 48;

    Text(std::string text, float x, float y, float scale, glm::vec3 color);
    void update();
    void render();
    void clean();

    void setText(std::string text) { m_text = text; }
    void move(float x, float y);

private:
    std::map<char, Character> Characters;

    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_scale = 1.0f;
    glm::vec3 m_color = {0,0,0};
    string m_text = "";

    Shader* m_shader;
    glm::mat4 m_projection;
    unsigned int m_VAO, m_VBO;

};


#endif //OPENGLSANDBOX_TEXT_H
