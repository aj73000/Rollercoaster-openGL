//
// Created by arthur on 4/1/24.
//

#include "Object.h"

bool Object::collisionDetect(const glm::vec4& minPosition,const glm::vec4& maxPosition) const
{
    //Detect for collision
    if( boundingBox.minPositions.x <= maxPosition.x &&
        boundingBox.maxPositions.x >= minPosition.x &&
        boundingBox.minPositions.y <= maxPosition.y &&
        boundingBox.maxPositions.y >= minPosition.y &&
        boundingBox.minPositions.z <= maxPosition.z &&
        boundingBox.maxPositions.z >= minPosition.z)
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
    return translationMatrix;
}

void Object::setTranslationMatrix(const glm::mat4 &translationMatrix) {
    Object::translationMatrix = translationMatrix;
}
