//
// Created by jack on 06/10/2020.
//

#ifndef OPENGLSANDBOX_MENUSTATE_H
#define OPENGLSANDBOX_MENUSTATE_H

#include <std_image.h>
//#define STB_IMAGE_IMPLEMENTATION
#include <graphics/Shader.h>
#include <util/Model.h>

#include <entity/Cube.h>
#include <entity/Text.h>
//#include <entity/Shape.h>

#include "GameState.h"

class MenuState : public GameState
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
    Text* m_text;
    Text* m_FPStext;
};


#endif //OPENGLSANDBOX_MENUSTATE_H
