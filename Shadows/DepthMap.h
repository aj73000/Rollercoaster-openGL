//
// Created by arthur on 4/22/24.
//

#ifndef ROLLERCOASTER_OPENGL_DEPTHMAP_H
#define ROLLERCOASTER_OPENGL_DEPTHMAP_H


#include <GL/glew.h>

class DepthMap {

    DepthMap()
    {
        unsigned int depthMapFBO;
        glGenFramebuffers(1, &depthMapFBO);
        const unsigned int SHADOW_WIDTH = 1024, SHADOW_HEIGHT = 1024;

        unsigned int depthMap;
        glGenTextures(1, &depthMap);
        glBindTexture(GL_TEXTURE_2D, depthMap);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT,
                     SHADOW_WIDTH, SHADOW_HEIGHT, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glBindFramebuffer(GL_FRAMEBUFFER, depthMapFBO);
        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthMap, 0);
        glDrawBuffer(GL_NONE);
        glReadBuffer(GL_NONE);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }

};


#endif //ROLLERCOASTER_OPENGL_DEPTHMAP_H
