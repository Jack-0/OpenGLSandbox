//
// Created by jack on 22/08/2020.
//

#ifndef OPENGLSANDBOX_TESTSTATE_H
#define OPENGLSANDBOX_TESTSTATE_H

#include <std_image.h>
//#define STB_IMAGE_IMPLEMENTATION
#include <graphics/Shader.h>
#include <util/Model.h>

#include <entity/Cube.h>
#include "GameState.h"

class TestState : public GameState
{
public:

    virtual void update();
    virtual void render();

    virtual bool onEnter();
    virtual bool onExit();

    virtual std::string getStateID() const { return s_StateID; }

private:
    static const std::string s_StateID;
    Cube* m_cube;
};


#endif //OPENGLSANDBOX_TESTSTATE_H
