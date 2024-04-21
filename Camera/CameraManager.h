//
// Created by arthur on 4/12/24.
//

#ifndef ROLLERCOASTER_OPENGL_CAMERAMANAGER_H
#define ROLLERCOASTER_OPENGL_CAMERAMANAGER_H


#include "Camera.h"

class CameraManager{
private:
public:
    static bool isInCart();

    static void setInCart(bool inCart);

private:
    static Camera* cam;
    static bool inCart;
public:
    static void setCamera(Camera& camera);
    static Camera& getCamera();

};


#endif //ROLLERCOASTER_OPENGL_CAMERAMANAGER_H
