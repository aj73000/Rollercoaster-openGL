//
// Created by arthur on 2/27/24.
//

#ifndef LEARNOPENGL_PLANE_H
#define LEARNOPENGL_PLANE_H

#include "GL/glew.h"
#include "../shaders/Shader.h"
#include "../Physics/Object.h"


class Plane{
    unsigned int planeVAO;
    unsigned int planeVBO;
    static constexpr unsigned int NUM_PATCH_PTS = 4;
    unsigned int grass_texture,rock_texture,sand_texture;

    static constexpr unsigned int rez = 10;
    int width = 2400, height = 1000;
public:
    Plane(Shader* shader);
    void render();

};


#endif //LEARNOPENGL_PLANE_H
