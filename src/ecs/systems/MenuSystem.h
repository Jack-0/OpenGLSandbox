//
// Created by jack on 13/01/2021.
//

#ifndef OPENGLSANDBOX_MENUSYSTEM_H
#define OPENGLSANDBOX_MENUSYSTEM_H

#include <ecs/core/System.h>

class MenuSystem : public System
{
public:
    void update();
    void render();
};

#endif //OPENGLSANDBOX_MENUSYSTEM_H
