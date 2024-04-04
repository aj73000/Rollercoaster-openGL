//
// Created by arthur on 4/1/24.
//

#include "Object.h"

bool Object::collisionDetect(glm::vec4 position)
{
    //Detect for collision
    if(abs(position.x) <= boundingBox.maxPositions.x)
        if(abs(position.y) <= boundingBox.maxPositions.y)
            if(abs(position.z) <= boundingBox.maxPositions.z)
                return true;
    return false;
}
