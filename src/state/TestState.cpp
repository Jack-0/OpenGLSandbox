//
// Created by jack on 22/08/2020.
//

#include <iostream>
#include "TestState.h"

const std::string TestState::s_StateID = "TEST";

void TestState::render() {}

void TestState::update() {}

bool TestState::onEnter() {
    std::cout  << "TEST STATE ENTERED" << std::endl;
}

bool TestState::onExit() {}