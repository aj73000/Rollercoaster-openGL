//
// Created by arthur on 3/14/24.
//

#ifndef LEARNOPENGL_CART_H
#define LEARNOPENGL_CART_H

#include "../Model/Model.h"

class Cart : public Model{
public:
    Cart(const char* path) : Model(path){};
    glm::vec3 Position;
    glm::vec3 CamPosition;

    glm::mat4 getModelMatrix()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,Position);

        model = glm::rotate(model,-Yaw,glm::vec3(0,1,0));
        model = glm::rotate(model,Pitch,glm::vec3(0,0,1));
        model = glm::rotate(model,Roll,glm::vec3(1,0,0));

        model = glm::scale(model,glm::vec3(10,10,10));

        return model;
    };
    float Pitch, Yaw = 0,Roll;
};


#endif //LEARNOPENGL_CART_H
