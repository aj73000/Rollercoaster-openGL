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
    for(int i = 0; i < objects.size()-1 ; i++)
    {
        Object* a = objects[i];
        i == 0 ? a->setIsGrounded(false) : a->setIsGrounded(a->getisGrounded());
        for(int j = i+1;j < objects.size();j++)
        {
            Object* b = objects[j];
            b->setIsGrounded(false);
            //Check if they can even collide before checking all positions
            glm::vec3 bPos = (b->getTranslationMatrix()*glm::vec4(b->getVertexes()[0],0))+glm::vec4(b->getPosition(),0);
            glm::vec3 aPos = (a->getTranslationMatrix()*glm::vec4(a->getVertexes()[0],0))+glm::vec4(a->getPosition(),0);

            float distance = sqrt(pow(a->getPosition().x- b->getPosition().x,2)+pow(a->getPosition().y- b->getPosition().y,2)+pow(a->getPosition().z- b->getPosition().z,2));
            float sum = sqrt(pow(a->getPosition().x-aPos.x,2)+pow(a->getPosition().y-aPos.y,2)+pow(a->getPosition().z-aPos.z,2))
                        +sqrt(pow(b->getPosition().x-bPos.x,2)+pow(b->getPosition().y-bPos.y,2)+pow(b->getPosition().z-bPos.z,2));
            //Detect for collision
            if(distance <= sum)
            {
                for(glm::vec3 position : b->getVertexes())
                    if(a->collisionDetect(glm::inverse(a->getTranslationMatrix())*((b->getTranslationMatrix()*glm::vec4(position,0))+glm::vec4(b->getPosition(),0)-glm::vec4(a->getPosition(),0)),*b))
                    {
                        a->resolveCollision(deltaTime,b);
                        break;
                    }
                for(glm::vec3 position : a->getVertexes())
                    if(b->collisionDetect(glm::inverse(b->getTranslationMatrix())*((a->getTranslationMatrix()*glm::vec4(position,0))+glm::vec4(a->getPosition(),0)-glm::vec4(b->getPosition(),0)),*a))
                    {
                        b->resolveCollision(deltaTime,a);
                        break;
                    }
            }
        }
    }
}

void PhysicsCollision::update(float deltaTime)
{
    //Simulate gravity
    for(Object* obj : objects)
    {
        if((bool)obj->getMass())
        {
            //Then its grounded
            if(obj->getisGrounded())
            {
                if(std::abs(obj->getVelocity().x)+std::abs(obj->getVelocity().y)+std::abs(obj->getVelocity().z) < 0.005f)
                    obj->setVelocity({0,0,0});
                else
                {
                    obj->setVelocity( obj->getVelocity() + (obj->getForce()/obj->getMass()*deltaTime));
                    obj->setVelocity(obj->getVelocity()*frictionConstant*obj->getMass());
                }
            }
            else
                obj->setForce(glm::vec3(obj->getForce().x,obj->getForce().y+(obj->getMass()*m_gravity),obj->getForce().z));
            obj->setVelocity( obj->getVelocity() + (obj->getForce()/obj->getMass()*deltaTime));
            obj->setPosition(obj->getPosition() + (obj->getVelocity()*deltaTime));
            obj->setForce(glm::vec3(0,0,0));
        }
    }
}