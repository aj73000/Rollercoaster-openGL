//
// Created by arthur on 3/14/24.
//

#ifndef LEARNOPENGL_CART_H
#define LEARNOPENGL_CART_H

#include "../Model/Model.h"

class Cart : public Model{
public:
    Cart(glm::vec3& position,const char* path) : Model(path)
    {
        this->setPosition(position);
    };
    float Pitch = 0 , Yaw = 0,Roll = 0;
    glm::mat4 getModelMatrix()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model,this->Position);
        model = glm::rotate(model,-this->Yaw,glm::vec3(0,1,0));
        model = glm::rotate(model,this->Pitch,glm::vec3(0,0,1));
        model = glm::rotate(model,this->Roll,glm::vec3(1,0,0));
        model = glm::scale(model,glm::vec3(10,10,10));
        setTranslationMatrix(model);
        return model;
    };
    void resolveCollision(float& deltaTime, Object* obj) override;
};


#endif //LEARNOPENGL_CART_H
