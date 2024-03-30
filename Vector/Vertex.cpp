//
// Created by arthur on 2/20/24.
//

#include "Vertex.h"

Vertex::Vertex(glm::vec3 position,float rotation,float pitch,float yaw)
{
    this->Position = position;
    this->Rotation = rotation;
    this->Pitch = pitch;
    this->Yaw = yaw;
}
