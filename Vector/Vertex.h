//
// Created by arthur on 2/20/24.
//

#ifndef LEARNOPENGL_VERTEX_H
#define LEARNOPENGL_VERTEX_H

#include "glm/glm.hpp"


struct Vertex{

    Vertex(glm::vec3 position,float rotation,float pitch,float yaw);

    Vertex() = default;

    glm::vec3 Position;
    glm::vec3 Normal;
    glm::vec2 TextCoords;

    float  Rotation;
    float Pitch = 0.0f;
    float Yaw;
};


#endif //LEARNOPENGL_VERTEX_H
