//
// Created by arthur on 5/7/24.
//

#include "boundaries.h"

void boundaries::resolveCollision(float &deltaTime, Object *obj)
{
    std::cout << "Colliding with world box" << std::endl;
}

boundaries::boundaries(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    cube.constructGeometry(minX,  maxX,  minY,  maxY, minZ, maxZ);

    vertexes.emplace_back(minX,minY,minZ);
    vertexes.emplace_back(maxX,maxY,maxZ);
    vertexes.emplace_back(minX,maxY,minZ);
    vertexes.emplace_back(maxX,minY,minZ);
    vertexes.emplace_back(maxX,maxY,minZ);
    vertexes.emplace_back(minX,minY,maxZ);
    vertexes.emplace_back(minX,maxY,maxZ);
    vertexes.emplace_back(maxX,minY,maxZ);
}
