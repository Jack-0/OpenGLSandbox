//
// Created by jack on 30/12/2020.
//

#ifndef OPENGLSANDBOX_RENDERSYSTEM_H
#define OPENGLSANDBOX_RENDERSYSTEM_H


#include <ecs/core/System.h>

class MeshRenderSystem : public System
{
public:
    void init();
    void render();
};

#endif //OPENGLSANDBOX_RENDERSYSTEM_H
