//
// Created by jack on 30/12/2020.
//

#ifndef OPENGLSANDBOX_RENDERSYSTEM_H
#define OPENGLSANDBOX_RENDERSYSTEM_H


#include <ecs/core/System.h>
#include <map>
#include <string>
#include <util/Model.h>
#include <memory>

class MeshRenderSystem : public System
{
public:
    void init();
    void render();

private:
    // map string names to models to avoid long init times
    std::map<std::string, Model*> models;
};

#endif //OPENGLSANDBOX_RENDERSYSTEM_H
