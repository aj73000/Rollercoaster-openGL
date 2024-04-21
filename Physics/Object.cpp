//
// Created by arthur on 4/1/24.
//

#include "Object.h"

bool operator<=(const glm::vec4& pos1,const glm::vec3& pos2)
{
    if(pos1.x <= pos2.x)
        if(pos1.y <= pos2.y)
            if(pos1.z <= pos2.z)
                return true;
    return false;
}
bool operator>=(const glm::vec4& pos1,const glm::vec3& pos2)
{
    if(pos1.x >= pos2.x)
        if(pos1.y >= pos2.y)
            if(pos1.z >= pos2.z)
                return true;
    return false;
}

bool Object::collisionDetect(const glm::vec4& position,const Object& obj) const
{
    if(position <= vertexes[1])
        if(position >= vertexes[0])
            return true;
    return false;
}

const glm::vec3 &Object::getVelocity() const {
    return Velocity;
}

const glm::vec3 &Object::getForce() const {
    return Force;
}

const glm::vec3 &Object::getPosition() const {
    return Position;
}

void Object::setPosition(const glm::vec3 &position) {
    Position = position;
}

void Object::setVelocity(const glm::vec3 &velocity) {
    Velocity = velocity;
}

void Object::setForce(const glm::vec3 &force) {
    Force = force;
}

float Object::getMass() const {
    return mass;
}

void Object::setMass(float mass) {
    Object::mass = mass;
}

const Cube &Object::getBoundingBox() const {
    return boundingBox;
}

void Object::setBoundingBox(const Cube &boundingBox) {
    Object::boundingBox = boundingBox;
}

const glm::mat4 &Object::getTranslationMatrix() const {
    return this->translationMatrix;
}

void Object::setTranslationMatrix(const glm::mat4 &translationMatrix)
{
    this->translationMatrix = translationMatrix;
}

const std::vector<glm::vec3> &Object::getVertexes() const {
    return vertexes;
}

bool Object::getisGrounded() const {
    return isGrounded;
}

void Object::setIsGrounded(bool isGrounded) {
    Object::isGrounded = isGrounded;
}
