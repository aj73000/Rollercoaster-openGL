//
// Created by arthur on 2/27/24.
//

#ifndef LEARNOPENGL_DEPTHMAP_H
#define LEARNOPENGL_DEPTHMAP_H


#include <GL/glew.h>

class DepthMap{

    unsigned int depthMapFBO;
    unsigned int depthMap;
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
public:
    DepthMap();

    void update() const;

    [[nodiscard]] unsigned int get_depthMap_FBO() const
    {
        return this->depthMapFBO;
    }

    [[nodiscard]] unsigned int get_depthMap() const
    {
        return this->depthMap;
    }
};


#endif //LEARNOPENGL_DEPTHMAP_H
