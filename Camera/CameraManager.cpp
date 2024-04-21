//
// Created by arthur on 4/12/24.
//

#include "CameraManager.h"

Camera* CameraManager::cam = new Camera();
bool CameraManager::inCart = false;

void CameraManager::setCamera(Camera &camera)
{
    cam = &camera;
}

Camera& CameraManager::getCamera()
{
    return *cam;
}

bool CameraManager::isInCart() {
    return inCart;
}

void CameraManager::setInCart(bool inCart) {
    CameraManager::inCart = inCart;
}
