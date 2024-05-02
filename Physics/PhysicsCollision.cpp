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
    for(Object* d : objects)
        d->setIsGrounded(false);
    for(int i = 0; i < objects.size()-1 ; i++)
    {
        Object* a = objects[i];
        for(int j = 0;j < objects.size();j++)
        {
            //Don't check an object with itself
            if(i != j)
            {
                Object* b = objects[j];
                //b->setIsGrounded(false);
                //Check if they can even collide before checking all positions
                glm::vec3 bPos = (b->getTranslationMatrix()*glm::vec4(b->getVertexes()[0],0))+glm::vec4(b->getPosition(),0);
                glm::vec3 aPos = (a->getTranslationMatrix()*glm::vec4(a->getVertexes()[0],0))+glm::vec4(a->getPosition(),0);

                double distance = sqrt(pow(a->getPosition().x- b->getPosition().x,2)+pow(a->getPosition().y- b->getPosition().y,2)+pow(a->getPosition().z- b->getPosition().z,2));
                double sumOfLongestDistance = sqrt(pow(a->getPosition().x-aPos.x,2)+pow(a->getPosition().y-aPos.y,2)+pow(a->getPosition().z-aPos.z,2))
                            +sqrt(pow(b->getPosition().x-bPos.x,2)+pow(b->getPosition().y-bPos.y,2)+pow(b->getPosition().z-bPos.z,2));
                //Detect for collision
                if(distance <= sumOfLongestDistance)
                {
                    //Check with a as the AABB and b as the OBB
                    //Add a max and min {max,min}
                    std::vector<glm::vec3> positions;
                    positions.reserve(10);
                    positions.push_back(a->getVertexes()[0]);
                    positions.push_back(a->getVertexes()[1]);
                    for(glm::vec3 position : b->getVertexes())
                        positions.emplace_back(glm::inverse(a->getTranslationMatrix())*((b->getTranslationMatrix()*glm::vec4(position,0))+glm::vec4(b->getPosition(),0)-glm::vec4(a->getPosition(),0)));
                    if(specifiedCheck(positions,a))
                    {
                        positions.clear();
                        positions.push_back(b->getVertexes()[0]);
                        positions.push_back(b->getVertexes()[1]);
                        for(glm::vec3 position : a->getVertexes())
                            positions.emplace_back(glm::inverse(b->getTranslationMatrix())*((a->getTranslationMatrix()*glm::vec4(position,0))+glm::vec4(a->getPosition(),0)-glm::vec4(b->getPosition(),0)));

                        //If both hold true then there is a collision between the two objects
                        if(specifiedCheck(positions,b))
                            a->resolveCollision(deltaTime,b);
                    }
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

void PhysicsCollision::sort(std::vector<glm::vec3> &points, const char *sortIndex)
{
    switch(tolower(*sortIndex))
    {
        case 'x':
            for(unsigned short i = 0 ; i< points.size() - 1;i++)
            {
                unsigned short minPosition = i;
                for(unsigned short j =  i+1 ; j < points.size();j++)
                {
                    minPosition = points[j].x < points[minPosition].x ? j : minPosition;
                }
                if(minPosition != i)
                {
                    glm::vec3 temp = points[i];
                    points[i] = points[minPosition];
                    points[minPosition] = temp;
                }
            }
            break;
        case 'y':
            for(unsigned short i = 0 ; i< points.size() - 1;i++)
            {
                unsigned short minPosition = i;
                for(unsigned short j =  i+1 ; j < points.size();j++)
                {
                    minPosition = points[j].y < points[minPosition].y ? j : minPosition;
                }
                if(minPosition != i)
                {
                    glm::vec3 temp = points[i];
                    points[i] = points[minPosition];
                    points[minPosition] = temp;
                }
            }
            break;
        case 'z':
            for(unsigned short i = 0 ; i< points.size() - 1;i++)
            {
                unsigned short minPosition = i;
                for(unsigned short j =  i+1 ; j < points.size();j++)
                {
                    minPosition = points[j].z < points[minPosition].z ? j : minPosition;
                }
                if(minPosition != i)
                {
                    glm::vec3 temp = points[i];
                    points[i] = points[minPosition];
                    points[minPosition] = temp;
                }
            }
            break;
    }
}

bool PhysicsCollision::isOverlap(std::vector<glm::vec3> &points, Object *a)
{
    // The smaller value of the two will always be the min
    // So if the first is the min and the second is the max then there is no overlap between the two objects

    //vertex[0] = min , vertex[1] = max
    return !( (points[0] == a->getVertexes()[0] && points[1] == a->getVertexes()[1]) ||
            (points[points.size()-2] == a->getVertexes()[0] && points[points.size()-1] == a->getVertexes()[1]) );
}

bool PhysicsCollision::specifiedCheck(std::vector<glm::vec3> &positions, Object *ob)
{

    PhysicsCollision::sort(positions,"x");
    if(PhysicsCollision::isOverlap(positions,ob))
    {
        PhysicsCollision::sort(positions,"y");
        if(PhysicsCollision::isOverlap(positions,ob))
        {
            PhysicsCollision::sort(positions,"z");
            if(PhysicsCollision::isOverlap(positions,ob))
            {
                return true;
            }
        }
    }
    return false;
}
