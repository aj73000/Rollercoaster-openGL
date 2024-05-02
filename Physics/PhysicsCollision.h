//
// Created by arthur on 3/29/24.
//

#ifndef LEARNOPENGL_PHYSICSCOLLISION_H
#define LEARNOPENGL_PHYSICSCOLLISION_H

#include "Object.h"

class PhysicsCollision {
    constexpr static const float m_gravity = -0.01f;
    constexpr static const float frictionConstant = 0.97f;
    static std::vector<Object*> objects;
    static void sort(std::vector<glm::vec3>& points,const char* sortIndex);
    static bool isOverlap(std::vector<glm::vec3>& points,Object* a);
    static bool specifiedCheck(std::vector<glm::vec3>&positions,Object* ob);
public:
    static void addObject(Object* obj)
    {
        objects.push_back(obj);
    };
    static void detectCollision(float deltaTime);
    static void update(float deltaTime);
};


#endif //LEARNOPENGL_PHYSICSCOLLISION_H
