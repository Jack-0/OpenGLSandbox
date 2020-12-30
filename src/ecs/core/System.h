//
// Created by jack on 29/12/2020.
//

#ifndef ECS_SYSTEM_H
#define ECS_SYSTEM_H

#include "EntityManager.h"
#include <set>

class System
{
public:
    std::set<Entity> m_entities;
};


#endif //ECS_SYSTEM_H
