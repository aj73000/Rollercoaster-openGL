//
// Created by arthur on 4/1/24.
//

#ifndef ROLLERCOASTER_OPENGL_OBJECT_H
#define ROLLERCOASTER_OPENGL_OBJECT_H

#include "../Camera/Camera.h"
#include "../Cube/Cube.h"

class Object {
protected:
    glm::vec3 Position;
    float mass;
    Cube boundingBox;
    glm::mat4 translationMatrix;
public:
    glm::vec3 getPosition()
    {
        return this->Position;
    }
    float getMass()
    {
        return this->mass;
    }
    Cube getBoundingBox()
    {
        return this->boundingBox;
    }
    void setPosition(glm::vec3 Position)
    {
        this->Position = Position;
    }
    glm::mat4 getTranslation()
    {
        return this->translationMatrix;
    }
    void setTranslation(glm::mat4 translation)
    {
        this->translationMatrix = translation;
    }
    bool collisionDetect(glm::vec4 position);
};


#endif //ROLLERCOASTER_OPENGL_OBJECT_H
