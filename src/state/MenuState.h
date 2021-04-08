//
// Created by jack on 06/10/2020.
//

#ifndef OPENGLSANDBOX_MENUSTATE_H
#define OPENGLSANDBOX_MENUSTATE_H

#include <std_image.h>
//#define STB_IMAGE_IMPLEMENTATION
#include <graphics/Shader.h>
#include <graphics/Model.h>

#include "GameState.h"

#include <ecs/systems/TextRenderSystem.h>
#include <ecs/systems/MenuSystem.h>
#include <memory>

#include <vector>


class MenuState : public GameState
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
    
    static void demo1();
    static void demo2();
    static void demo3();
    static void exit();
    std::shared_ptr<TextRenderSystem> m_text_system;
    std::shared_ptr<MenuSystem> m_menu_system;
};


#endif //OPENGLSANDBOX_MENUSTATE_H
