//
// Created by jack on 12/10/2020.
//

#include <Game.h>
#include "Text.h"

Text::Text(std::string text, float x, float y, float scale, glm::vec3 color) : GameObject()
{
    m_text = text;
    m_x = x;
    m_y = y;
    m_scale = scale;
    m_color = color;
    // set OpenGL state for font rendering
    glEnable(GL_CULL_FACE);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);


    FT_Library ft;
    FT_Face face;


    m_shader = new Shader("../res/shaders/text.vert","../res/shaders/text.frag");
    m_shader->use();
    m_projection = glm::ortho(0.0f, static_cast<float>(Game::Instance()->getScreenWidth()), 0.0f, static_cast<float>(Game::Instance()->getScreenHeight()));
    glUniformMatrix4fv(glGetUniformLocation(m_shader->program_id, "projection"), 1, GL_FALSE, &m_projection[0][0]);

    if (FT_Init_FreeType(&ft))
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;

    if (FT_New_Face(ft, "../res/fonts/Roboto/Roboto-Thin.ttf", 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;

    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, PIXEL_HEIGHT);

    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph (int: "<< int(c) <<") \"" << c << "\"" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
                GL_TEXTURE_2D,
                0,
                GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0,
                GL_RED,
                GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
                texture,
                glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
                glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
                static_cast<unsigned int>(face->glyph->advance.x)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);



    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    // configure VAO/VBO for texture quads
    // -----------------------------------
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glBindVertexArray(m_VAO);
    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);


    //glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

}

void Text::update()
{
    // Highlight text if mouse over ----------------------------
    // get mouse position
    float mouse_x = Game::Instance()->m_lastMouseX;
    float mouse_y = Game::Instance()->getScreenHeight() - Game::Instance()->m_lastMouseY; // Y position must be subtracted from screen height to work with entities coord system TODO
    // set default colour
    m_color = {255,255,255}; // set colour to white
    // check if the mouse is within the text bounds
    if (mouse_x > m_x) {
        if (mouse_x < (m_x + m_pixel_string_len)) {
            if (mouse_y < m_y + PIXEL_HEIGHT) {
                if (mouse_y >  m_y) {
                    // mouse is over the text
                    m_color = {0, 240, 0}; // set text colour to green
                }
            }
        }
    }

}

void Text::render()
{
    // activate corresponding render state
    m_shader->use();
    glUniform3f(glGetUniformLocation(m_shader->program_id, "textColor"), m_color.x, m_color.y, m_color.z); // last 3  = colour
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(m_VAO);

    // iterate through all characters TODO refactor to be more efficient
    int temp_x = m_x;

    std::string::const_iterator c;
    for (c = m_text.begin(); c != m_text.end(); c++)
    {
        Character ch = Characters[*c];

        float x = temp_x + ch.Bearing.x * m_scale;
        float y = m_y - (ch.Size.y - ch.Bearing.y) * m_scale;

        float w = ch.Size.x * m_scale;
        float h = ch.Size.y * m_scale;
        // update VBO for each character
        float vertices[6][4] = {
                {  x,     y + h,   0.0f, 0.0f },
                {  x,     y,       0.0f, 1.0f },
                {  x + w, y,       1.0f, 1.0f },

                {  x,     y + h,   0.0f, 0.0f },
                {  x + w, y,       1.0f, 1.0f },
                {  x + w, y + h,   1.0f, 0.0f }
        };
        // render glyph texture over quad
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        // update content of VBO memory
        glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
        glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        // render quad
        glDrawArrays(GL_TRIANGLES, 0, 6);
        // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
        temp_x += (ch.Advance >> 6) * m_scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
    }
    m_pixel_string_len = temp_x;

    //std::cout << "string = " << m_text << " length = " << m_pixel_string_len << "\n"; // todo

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Text::clean()
{

}

void Text::move(float x, float y)
{
    m_x = x;
    m_y = y;
}

void Text::setText(std::string text)
{
    m_text = text;
}

void Text::adjustForLength()
{
    render(); // needed to set string_length
    m_x = m_x - (m_pixel_string_len / 2);
}
