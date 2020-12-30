//
// Created by jack on 30/12/2020.
//

#ifndef OPENGLSANDBOX_MESHCOMPONENT_H
#define OPENGLSANDBOX_MESHCOMPONENT_H

#include <util/Model.h>
#include <graphics/Shader.h>

struct MeshComponent
{
    std::string model_string_path;
    Model* model;
};

#endif //OPENGLSANDBOX_MESHCOMPONENT_H
