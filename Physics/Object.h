//
// Created by arthur on 4/1/24.
//

#ifndef ROLLERCOASTER_OPENGL_OBJECT_H
#define ROLLERCOASTER_OPENGL_OBJECT_H

#include "../Camera/Camera.h"
#include "../Cube/Cube.h"

class Object {
public:
    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    void setVelocity(const glm::vec3 &velocity);

    void setForce(const glm::vec3 &force);

    float getMass() const;

    const glm::vec3 &getVelocity() const;

    const glm::vec3 &getForce() const;

    void setMass(float mass);

    const Cube &getBoundingBox() const;

    void setBoundingBox(const Cube &boundingBox);

    const glm::mat4 &getTranslationMatrix() const;

    void setTranslationMatrix(const glm::mat4 &translationMatrix);

    bool collisionDetect(const glm::vec4& position) const;

    virtual void resolveCollision(float& deltaTime,Object* obj)
    {
        obj->setPosition(obj->getPosition() + (-obj->getVelocity()*deltaTime));
        obj->setVelocity(glm::vec3(obj->getVelocity().x,0,obj->getVelocity().z));
    };

protected:
    glm::vec3 Position = glm::vec3(0,0,0);
    glm::vec3 Velocity = glm::vec3(0,0,0);
    glm::vec3 Force = glm::vec3(0,0,0);
    std::vector<glm::vec3> vertexes;
    float mass = 0;
public:
    const std::vector<glm::vec3> &getVertexes() const;
protected:
    Cube boundingBox;
    glm::mat4 translationMatrix;
};
#endif //ROLLERCOASTER_OPENGL_OBJECT_H