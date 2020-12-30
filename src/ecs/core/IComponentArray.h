//
// Created by jack on 29/12/2020.
//

#ifndef ECS_ICOMPONENTARRAY_H
#define ECS_ICOMPONENTARRAY_H

#include "EntityManager.h"

class IComponentArray
{
public:
    virtual ~IComponentArray() = default;
    virtual void entity_destroyed(Entity entity) = 0;
};

#endif //ECS_ICOMPONENTARRAY_H
