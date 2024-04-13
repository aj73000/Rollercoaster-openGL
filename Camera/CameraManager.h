//
// Created by arthur on 4/12/24.
//

#ifndef ROLLERCOASTER_OPENGL_CAMERAMANAGER_H
#define ROLLERCOASTER_OPENGL_CAMERAMANAGER_H


#include "Camera.h"

class CameraManager{
private:
    static Camera* cam;
    static std::vector<Camera> cams;

public:
    static void addCamera(Camera& camera);
    static void setCamera(Camera& camera);
    static Camera& getCamera();

};


#endif //ROLLERCOASTER_OPENGL_CAMERAMANAGER_H
