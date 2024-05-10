//
// Created by arthur on 5/7/24.
//

#ifndef ROLLERCOASTER_OPENGL_BOUNDARIES_H
#define ROLLERCOASTER_OPENGL_BOUNDARIES_H


#include "Object.h"

class boundaries : public Object{

    Cube cube;
public:
    boundaries(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
    void resolveCollision(float &deltaTime, Object *obj);

};


#endif //ROLLERCOASTER_OPENGL_BOUNDARIES_H
