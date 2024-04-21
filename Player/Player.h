//
// Created by arthur on 4/1/24.
//

#ifndef ROLLERCOASTER_OPENGL_PLAYER_H
#define ROLLERCOASTER_OPENGL_PLAYER_H

#include "../Model/Model.h"

class Player : public Model{
public:
    Camera PlayerCam = (glm::vec3(0,0,-20)+(glm::vec3(10,10,10)*glm::vec3(-0.347193,0.10059,-0.274781)));
    glm::mat4 getModelMatrix()
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, Position);
        model = glm::rotate(model , glm::radians(90.0f)+glm::radians(PlayerCam.Yaw) , glm::vec3(0,1,0));
        model = glm::rotate(model, glm::radians(-90.0f),glm::vec3(0,0,1));
        model = glm::scale(model,glm::vec3(5,3,3));
        PlayerCam.Position = glm::vec3(Position.x,Position.y+(2*0.08f),Position.z);
        setTranslationMatrix(model);
        return model;
    }
    Player(const char *path,glm::vec3 position) : Model(path)
    {
        setMass(1);
        setPosition(position);
    };

    void resolveCollision(float& deltaTime,Object* obj) override;
    void ProcessKeyboard(Camera_Movement direction);
};


#endif //ROLLERCOASTER_OPENGL_PLAYER_H
