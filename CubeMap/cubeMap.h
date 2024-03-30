//
// Created by arthur on 2/24/24.
//

#ifndef LEARNOPENGL_CUBEMAP_H
#define LEARNOPENGL_CUBEMAP_H

#endif //LEARNOPENGL_CUBEMAP_H

#include "GL/glew.h"
#include "iostream"
#include <vector>
#include "stb/stb_image.h"

class cubeMap
{
    unsigned int cubeMapTexture;
    unsigned int skyboxVAO, skyboxVBO;
    std::vector<std::string> faces;

public:
    void loadCubeMap();

    void Render();

    void innit(std::string path);
};
