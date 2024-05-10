//
// Created by arthur on 4/22/24.
//

#ifndef ROLLERCOASTER_OPENGL_DEPTHMAP_H
#define ROLLERCOASTER_OPENGL_DEPTHMAP_H


#include <GL/glew.h>
#include "../shaders/Shader.h"

class DepthMap {
public:
    DepthMap(Shader* shader);
    void bindFBO();
    unsigned int depthMap;
private:
    unsigned int depthMapFBO;
    const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;
};


#endif //ROLLERCOASTER_OPENGL_DEPTHMAP_H
