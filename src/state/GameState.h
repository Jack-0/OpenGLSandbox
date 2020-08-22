//
// Created by jack on 22/08/2020.
//

#ifndef OPENGLSANDBOX_GAMESTATE_H
#define OPENGLSANDBOX_GAMESTATE_H

#include <string>
#include <vector>

/**
 * Abstract class
 */
class GameState
{
public:
    virtual void update() =0;
    virtual void render() = 0;

    virtual bool onEnter() = 0;
    virtual bool onExit() = 0;

    virtual std::string getStateID() const = 0;

protected:
    std::vector<std::string> m_textureIDs;
};

#endif //OPENGLSANDBOX_GAMESTATE_H
