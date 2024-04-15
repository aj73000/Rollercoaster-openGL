//
// Created by arthur on 3/29/24.
//

#include "PhysicsCollision.h"

std::vector<Object*> PhysicsCollision::objects;

bool operator>(const glm::vec4& pos1,const glm::vec4& pos2)
{
    float sum1 = pos1.x+pos1.y+pos1.z;
    float sum2 = pos2.x+pos2.y+pos2.z;
    return sum1>sum2;
}
//glm::vec4 boxMaxPosition = glm::inverse(a->getTranslationMatrix())*(glm::vec4(b->getPosition()+b->getBoundingBox().maxPositions,0)-glm::vec4(a->getPosition(),0));
void PhysicsCollision::detectCollision(float deltaTime)
{
    for(Object* a : objects)
        for(Object* b : objects)
            if(a != b)
                for(glm::vec3 position : b->getVertexes())
                    if(a->collisionDetect(glm::inverse(a->getTranslationMatrix())*((b->getTranslationMatrix()*glm::vec4(position,0))+glm::vec4(b->getPosition(),0)-glm::vec4(a->getPosition(),0))))
                        a->resolveCollision(deltaTime,b);
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