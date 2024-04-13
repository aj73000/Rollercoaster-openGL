//
// Created by arthur on 3/29/24.
//

#include "PhysicsCollision.h"

std::vector<Object*> PhysicsCollision::objects;

void PhysicsCollision::detectCollision(float deltaTime)
{
    for(Object* a : objects)
        for(Object* b : objects)
            if(a != b)
            {
                glm::vec4 boxMinPosition = glm::inverse(a->getTranslationMatrix())*(glm::vec4(b->getPosition()+b->getBoundingBox().minPositions,0)-glm::vec4(a->getPosition(),0));
                glm::vec4 boxMaxPosition =glm::inverse(a->getTranslationMatrix())*(glm::vec4(b->getPosition()+b->getBoundingBox().maxPositions,0)-glm::vec4(a->getPosition(),0));
                if(a->collisionDetect(boxMinPosition,boxMaxPosition))
                    a->resolveCollision(deltaTime,b);
            }


}

void PhysicsCollision::update(float deltaTime)
{
    //Simulate gravity
    for(Object* obj : objects)
    {
        if((bool)obj->getMass())
        {
            obj->setForce(glm::vec3(0,obj->getForce().y+(obj->getMass()*m_gravity),0));
            obj->setVelocity( obj->getVelocity() + (obj->getForce()/obj->getMass()*deltaTime));
            obj->setPosition(obj->getPosition() + (obj->getVelocity()*deltaTime));
            obj->setForce(glm::vec3(0,0,0));
        }
    }
}