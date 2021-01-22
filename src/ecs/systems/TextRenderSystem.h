//
// Created by jack on 08/01/2021.
//

#ifndef OPENGLSANDBOX_TEXTRENDERSYSTEM_H
#define OPENGLSANDBOX_TEXTRENDERSYSTEM_H


#include <ecs/core/System.h>
#include <ecs/components/TextComponent.h>
#include <freetype/tttags.h>
#include <ecs/components/Dimensions2DComponent.h>

#include <map>
#include <ecs/components/TransformComponent.h>
#include <ecs/components/ShaderComponent.h>

#include <Game.h>


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
    void init()
    {
        
        for (auto const& entity : m_entities)
        {
            auto& transform = Game::Instance()->get_ecs()->get_component<TransformComponent>(entity);
            auto& shader = Game::Instance()->get_ecs()->get_component<ShaderComponent>(entity);
            auto& text = Game::Instance()->get_ecs()->get_component<TextComponent>(entity);
            auto &dimension2D = Game::Instance()->get_ecs()->get_component<Dimensions2DComponent>(entity);
            
            dimension2D.height = PIXEL_HEIGHT; // tODO
    
            shader.shader = new Shader(shader.vert_path, shader.frag_path);
            
            // set OpenGL state for font rendering
            glEnable(GL_CULL_FACE);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    
            FT_Library ft;
            FT_Face face;
    
    
            shader.shader->use();
            glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(Game::Instance()->getScreenWidth()), 0.0f, static_cast<float>(Game::Instance()->getScreenHeight()));
            glUniformMatrix4fv(glGetUniformLocation(shader.shader->program_id, "projection"), 1, GL_FALSE, &projection[0][0]);
    
            // TODO this may only need to be done once
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
                characters.insert(std::pair<char, Character>(c, character));
            }
            glBindTexture(GL_TEXTURE_2D, 0);
    
    
    
            FT_Done_Face(face);
            FT_Done_FreeType(ft);
    
            // configure VAO/VBO for texture quads
            glGenVertexArrays(1, &text.vao);
            glGenBuffers(1, &text.vbo);
            glBindVertexArray(text.vao);
            glBindBuffer(GL_ARRAY_BUFFER, text.vbo);
            glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
            glEnableVertexAttribArray(0);
            glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        
    }
    
    void render()
    {
        for (auto const& entity : m_entities)
        {
            
            auto &transform = Game::Instance()->get_ecs()->get_component<TransformComponent>(entity);
            auto &shader = Game::Instance()->get_ecs()->get_component<ShaderComponent>(entity);
            auto &text = Game::Instance()->get_ecs()->get_component<TextComponent>(entity);
            auto &dimension2D = Game::Instance()->get_ecs()->get_component<Dimensions2DComponent>(entity);
            
            // activate corresponding render state
            shader.shader->use();
            glUniform3f(glGetUniformLocation(shader.shader->program_id, "textColor"), text.colour.x, text.colour.y, text.colour.z); // last 3  = colour
            glActiveTexture(GL_TEXTURE0);
            glBindVertexArray(text.vao);
    
            // iterate through all characters TODO refactor to be more efficient
            int temp_x = transform.pos.x;
    
            std::string::const_iterator c;
            for (c = text.text.begin(); c != text.text.end(); c++)
            {
                Character ch = characters[*c];
        
                float x = temp_x + ch.Bearing.x * text.scale;
                float y = transform.pos.y - (ch.Size.y - ch.Bearing.y) * text.scale;
        
                float w = ch.Size.x * text.scale;
                float h = ch.Size.y * text.scale;
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
                glBindBuffer(GL_ARRAY_BUFFER, text.vbo);
                glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices); // be sure to use glBufferSubData and not glBufferData
        
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                // render quad
                glDrawArrays(GL_TRIANGLES, 0, 6);
                // now advance cursors for next glyph (note that advance is number of 1/64 pixels)
                temp_x += (ch.Advance >> 6) * text.scale; // bitshift by 6 to get value in pixels (2^6 = 64 (divide amount of 1/64th pixels by 64 to get amount of pixels))
            }
            dimension2D.width = temp_x; // todo needed to check bounds
    
            glBindVertexArray(0);
            glBindTexture(GL_TEXTURE_2D, 0);
        
        }
        
    }
};

#endif //OPENGLSANDBOX_TEXTRENDERSYSTEM_H
