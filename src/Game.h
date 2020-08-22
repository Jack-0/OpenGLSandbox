//
// Created by jack on 22/08/2020.
//

#ifndef OPENGLSANDBOX_GAME_H
#define OPENGLSANDBOX_GAME_H

#include <state/GameStateMachine.h>

class Game
{
public:
    ~Game() {}

    /// Ensure game is a singleton
    static Game* Instance()
    {
        if(s_pInstance == 0)
        {
            s_pInstance = new Game();
            return s_pInstance;
        }
    }

    void init();
    //void render();
    //void update();
    //void handleEvents();

    GameStateMachine* getStateMachine() { return m_pGameStateMachine; }
    //int getScreenWidth() { return m_screenWidth; }
    //int getScreenHeight() { return m_screenHeight; }

private:

    Game() {}

    //int m_screenWidth;
    //int m_screenHeight;

    static Game* s_pInstance;

    GameStateMachine* m_pGameStateMachine;
};


#endif //OPENGLSANDBOX_GAME_H
