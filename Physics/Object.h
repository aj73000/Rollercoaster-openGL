//
// Created by arthur on 4/1/24.
//

#ifndef ROLLERCOASTER_OPENGL_OBJECT_H
#define ROLLERCOASTER_OPENGL_OBJECT_H

#include "../Camera/Camera.h"
#include "../Cube/Cube.h"

class Object {
public:
    [[nodiscard]] const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    void setVelocity(const glm::vec3 &velocity);

    void setForce(const glm::vec3 &force);

    [[nodiscard]] float getMass() const;

    [[nodiscard]] const glm::vec3 &getVelocity() const;

    [[nodiscard]] const glm::vec3 &getForce() const;

    void setMass(float mass);

    [[nodiscard]] const Cube &getBoundingBox() const;

    void setBoundingBox(const Cube &boundingBox);

    [[nodiscard]] const glm::mat4 &getTranslationMatrix() const;

    void setTranslationMatrix(const glm::mat4 &translationMatrix);

    [[nodiscard]] bool collisionDetect(const glm::vec4& position,const Object& obj) const;

    virtual void resolveCollision(float& deltaTime,Object* obj)
    {
        obj->setIsGrounded(true);
        obj->setVelocity(glm::vec3(obj->getVelocity().x,0,obj->getVelocity().z));
    };

protected:
    glm::vec3 Position = glm::vec3(0,0,0);
    glm::vec3 Velocity = glm::vec3(0,0,0);
    glm::vec3 Force = glm::vec3(0,0,0);
    std::vector<glm::vec3> vertexes;
    float mass = 0;
    bool isGrounded = false;
public:
    bool getisGrounded() const;

    void setIsGrounded(bool isGrounded);

public:
    [[nodiscard]] const std::vector<glm::vec3> &getVertexes() const;
protected:
    Cube boundingBox;
    glm::mat4 translationMatrix;
};
#endif //ROLLERCOASTER_OPENGL_OBJECT_H