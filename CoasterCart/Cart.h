//
// Created by arthur on 3/14/24.
//

#ifndef LEARNOPENGL_CART_H
#define LEARNOPENGL_CART_H

#include "../Model/Model.h"
#include "../Camera/CameraManager.h"

class Cart : public Model{
public:
    Camera cam;
    Cart(glm::vec3& position,const char* path) : Model(path)
    {
        this->setPosition(position);
        cam ={this->Position};
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
    void update()
    {
        glm::vec4 camPos = glm::vec4(0,0.093f,0,0);
        glm::mat4 mat = glm::mat4(1);
        mat = glm::rotate(mat, -this->Yaw, glm::vec3(0, 1, 0));
        mat = glm::rotate(mat, this->Pitch, glm::vec3(0, 0, 1));
        mat = glm::rotate(mat,this->Roll,glm::vec3(1,0,0));
        camPos = mat * camPos;
        camPos += glm::vec4(this->getPosition(),0);
        cam.Position = camPos;
        cam.Pitch = glm::degrees(this->Pitch);
        cam.Yaw = -90-glm::degrees(this->Yaw);
        cam.Roll = glm::degrees(this->Roll);
    }
    void resolveCollision(float& deltaTime, Object* obj) override;
};


#endif //LEARNOPENGL_CART_H
