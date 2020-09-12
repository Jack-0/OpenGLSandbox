//
// Created by jack on 11/09/2020.
//

#ifndef OPENGLSANDBOX_CUBE_H
#define OPENGLSANDBOX_CUBE_H

#import "GameObject.h"

class Cube : GameObject
{
public:
    Cube(std::string model_path, const char *vert_path, const char *frag_path);
    void update();
    void render();
    void clean();

    void move(float x, float y, float z)
    {
        m_x = x; m_y = y; m_z = z;
    }

private:
    float m_x = 0.0f;
    float m_y = 0.0f;
    float m_z = 0.0f;

};

#endif //OPENGLSANDBOX_CUBE_H
