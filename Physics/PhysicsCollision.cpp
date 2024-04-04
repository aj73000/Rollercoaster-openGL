//
// Created by arthur on 3/29/24.
//

#include "PhysicsCollision.h"

bool PhysicsCollision::detectCollision(Object a, const std::vector<Object>& objects)
{
    for(Object b : objects)
    {
        if(a.collisionDetect((glm::inverse(a.getTranslation())*glm::vec4(b.getPosition(),0))))
            return true;
    }
    return false;
}
