//
// Created by jack on 22/08/2020.
//

#ifndef OPENGLSANDBOX_GAMESTATEMACHINE_H
#define OPENGLSANDBOX_GAMESTATEMACHINE_H

#include <vector>
#include "GameState.h"

class GameStateMachine
{
public:

    void pushState(GameState* pState);
    void changeState(GameState* pState);
    void popState();

    void update();
    void render();

private:
    std::vector<GameState*> m_gameStates;
};

#endif //OPENGLSANDBOX_GAMESTATEMACHINE_H
