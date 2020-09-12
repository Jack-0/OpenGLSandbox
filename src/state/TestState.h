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
#include <entity/Shape.h>

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
    Cube* m_cube2;
    Shape* m_shape;
    float test = 2.0f;
};


#endif //OPENGLSANDBOX_TESTSTATE_H
