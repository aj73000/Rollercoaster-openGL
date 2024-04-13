//
// Created by arthur on 4/12/24.
//

#include "CameraManager.h"

std::vector<Camera> CameraManager::cams;
Camera* CameraManager::cam = new Camera();

void CameraManager::setCamera(Camera &camera)
{
    cam = &camera;
}

Camera& CameraManager::getCamera() {
    return *cam;
}

void CameraManager::addCamera(Camera &camera)
{
    cams.push_back(camera);
}
