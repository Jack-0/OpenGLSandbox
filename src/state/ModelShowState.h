//
// Created by jack on 24/03/2021.
//

#ifndef OPENGLSANDBOX_MODELSHOWSTATE_H
#define OPENGLSANDBOX_MODELSHOWSTATE_H

#include <std_image.h>
//#define STB_IMAGE_IMPLEMENTATION
#include <graphics/Shader.h>
#include <graphics/Model.h>


#include "GameState.h"

#include <memory>
#include <ecs/systems/MeshRenderSystem.h>
#include <ecs/systems/TextRenderSystem.h>

class ModelShowState : public GameState
{
public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual void clean();

    virtual std::string getStateID() const { return s_StateID; }

private:
    static const std::string s_StateID;
    
    std::shared_ptr<MeshRenderSystem> mesh_renderer;
};


#endif //OPENGLSANDBOX_MODELSHOWSTATE_H
