//
// Created by arthur on 2/27/24.
//

#ifndef LEARNOPENGL_PLANE_H
#define LEARNOPENGL_PLANE_H

#include "GL/glew.h"
#include "../shaders/Shader.h"


class Plane {

    unsigned int planeVAO;

    // plane VAO
    unsigned int planeVBO;
public:
    Plane();
    void render();

};


#endif //LEARNOPENGL_PLANE_H
