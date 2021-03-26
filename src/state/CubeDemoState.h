//
// Created by jack on 22/08/2020.
//

#ifndef OPENGLSANDBOX_CUBEDEMOSTATE_H
#define OPENGLSANDBOX_CUBEDEMOSTATE_H

#include <std_image.h>
//#define STB_IMAGE_IMPLEMENTATION
#include <graphics/Shader.h>
#include <util/Model.h>


#include "GameState.h"

#include <memory>
#include <ecs/systems/MeshRenderSystem.h>
#include <ecs/systems/TextRenderSystem.h>

#include <graphics/SkyBox.h>

class CubeDemoState : public GameState
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
    std::shared_ptr<TextRenderSystem> text_renderer;

    SkyBox* m_skybox;
};


#endif //OPENGLSANDBOX_CUBEDEMOSTATE_H
