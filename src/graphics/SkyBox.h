//
// Created by jack on 26/03/2021.
//

#ifndef OPENGLSANDBOX_SKYBOX_H
#define OPENGLSANDBOX_SKYBOX_H

#include <graphics/Shader.h>
#include <vector>
#include <string>

/**
 * Skybox texure where TOP is a .jpeg named top.jpg
 * The constructor looks for these files using the directory_path parameter
 *        |------|
 *        | TOP  |
 * |------|------|------|------|
 * | LEFT |FRONT |RIGHT | BACK |
 * |------|------|------|------|
 *        |BOTTOM|
 *        |------|
 */
class SkyBox
{
public:
    SkyBox(const char* directory_path);
    void render();
    void update();

private:
    unsigned int m_vao, m_vbo;
    unsigned int m_cubemap_texture;

    Shader* m_shader;

    unsigned int load_cubemap(std::vector<std::string> faces);
};

#endif //OPENGLSANDBOX_SKYBOX_H