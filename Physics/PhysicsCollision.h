//
// Created by arthur on 3/29/24.
//

#ifndef LEARNOPENGL_PHYSICSCOLLISION_H
#define LEARNOPENGL_PHYSICSCOLLISION_H

#include "Object.h"

class PhysicsCollision {
public:
    static bool detectCollision(Object a,const std::vector<Object>& objects);
};


#endif //LEARNOPENGL_PHYSICSCOLLISION_H
