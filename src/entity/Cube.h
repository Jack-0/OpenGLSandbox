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
};


#endif //OPENGLSANDBOX_CUBE_H
