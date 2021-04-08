//
// Created by jack on 08/04/2021.
//

#ifndef OPENGLSANDBOX_PRACTICESTATE_H
#define OPENGLSANDBOX_PRACTICESTATE_H

#include "GameState.h"

class PracticeState : public GameState
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
};



#endif //OPENGLSANDBOX_PRACTICESTATE_H
