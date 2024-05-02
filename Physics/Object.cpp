//
// Created by arthur on 4/1/24.
//

#include "Object.h"

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
