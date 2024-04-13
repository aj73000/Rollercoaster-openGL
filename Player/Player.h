//
// Created by arthur on 4/1/24.
//

#ifndef ROLLERCOASTER_OPENGL_PLAYER_H
#define ROLLERCOASTER_OPENGL_PLAYER_H

#include "../Model/Model.h"

class Player : public Model{
public:
    Camera PlayerCam = (glm::vec3(0,0,-20)+(glm::vec3(10,10,10)*glm::vec3(-0.347193,0.10059,-0.274781)));
    glm::mat4 getModelMatrix(Camera& cam)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, Position);
        model = glm::rotate(model , glm::radians(90.0f)+glm::radians(cam.Yaw) , glm::vec3(0,1,0));
        model = glm::rotate(model, glm::radians(cam.Pitch),glm::vec3(0,0,1));
        setTranslationMatrix(model);
        return model;
    }
    Player(const char *path,glm::vec3 position) : Model(path)
    {
        setMass(1);
        setPosition(position);
    };

    void resolveCollision(float& deltaTime,Object* obj) override;
};


#endif //ROLLERCOASTER_OPENGL_PLAYER_H
