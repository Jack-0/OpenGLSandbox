//
// Created by jack on 22/08/2020.
//

#include <state/TestState.h>
#include "Game.h"

Game* Game::s_pInstance = 0; // singleton

void Game::init()
{
    m_pGameStateMachine = new GameStateMachine();
    m_pGameStateMachine->changeState(new TestState());
}

//void Game::update() {}

//void Game::render() {}

//void Game::handleEvents() {}
