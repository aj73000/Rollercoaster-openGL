//
// Created by arthur on 3/2/24.
//

#ifndef LEARNOPENGL_CENTRIPETAL_CATMULL_ROM_SPLINE_H
#define LEARNOPENGL_CENTRIPETAL_CATMULL_ROM_SPLINE_H


/*
 * Resources:
 *  https://en.wikipedia.org/wiki/Spline_interpolation
 *  https://en.wikipedia.org/wiki/Spline_(mathematics)
 */


#include <glm/vec3.hpp>
#include <cmath>
#include <iostream>
#include "../Vector/Vertex.h"

#include "../CoasterCart/Cart.h"

class Spline{
    static double distance(const glm::vec3 &vec, const glm::vec3 &vec1)
    {
        return sqrt(pow((vec1.x-vec.x),2) + pow((vec1.y-vec.y),2)+ pow(vec1.z-vec.z,2));
    }

    static float lerp(float a, float b, float t)
    {
        return a + t * (b - a);
    }

public:
    static void spline(const Vertex& p0, const Vertex& p1, const Vertex& p2, const Vertex& p3, float t, Cart* cart,float alpha = 1);

    /**
 *
 * name: setupSpline
 * @param filePath
 * @param trackFilePath
 * description: Generates the points for the spline to go over. This is all the rotation maths as well
 * return type: void
 */
    static std::vector<Vertex> setupSpline(const char* filePath, const char* trackFilePath);
};
#endif //LEARNOPENGL_CENTRIPETAL_CATMULL_ROM_SPLINE_H
