//
// Created by arthur on 2/27/24.
//

#include <stb/stb_image.h>
#include "Plane.h"

Plane::Plane(Shader* shader)
{
    shader->use();
    glGenTextures(1, &grass_texture);
    glBindTexture(GL_TEXTURE_2D, grass_texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int Texwidth,Texheight;
    unsigned char *data = stbi_load("../TerrainTextures/grass.jpg",
                                    &Texwidth, &Texheight, nullptr,0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Texwidth, Texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        shader->setInt("grass_texture",0);
        std::cout << "Loaded texture of size " << Texwidth << " x " << Texheight << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &rock_texture);
    glBindTexture(GL_TEXTURE_2D, rock_texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("../TerrainTextures/rock.jpg",
                                    &Texwidth, &Texheight, nullptr,0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Texwidth, Texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        shader->setInt("rock_texture",1);
        std::cout << "Loaded texture of size " << Texwidth << " x " << Texheight << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    glGenTextures(1, &sand_texture);
    glBindTexture(GL_TEXTURE_2D, sand_texture); // all upcoming GL_TEXTURE_2D operations now have effect on this texture object
    // set the texture wrapping parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    // set texture filtering parameters
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    data = stbi_load("../TerrainTextures/sand.jpg",
                     &Texwidth, &Texheight, nullptr,0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Texwidth, Texheight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        shader->setInt("sand_texture",2);
        std::cout << "Loaded texture of size " << Texwidth << " x " << Texheight << std::endl;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    // vertex generation
    std::vector<float> vertices;
    vertices.reserve(rez*rez*4);
    for(unsigned i = 0; i <= rez-1; i++)
    {
        for(unsigned j = 0; j <= rez-1; j++)
        {
            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(i / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-height/2.0f + height*j/(float)rez); // v.z
            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back(j / (float)rez); // v

            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back(-width/2.0f + width*i/(float)rez); // v.x
            vertices.push_back(i / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v

            vertices.push_back(-height/2.0f + height*(j+1)/(float)rez); // v.z
            vertices.push_back(-width/2.0f + width*(i+1)/(float)rez); // v.x
            vertices.push_back((i+1) / (float)rez); // u
            vertices.push_back((j+1) / (float)rez); // v
        }
    }
    std::cout << "Loaded " << rez*rez << " patches of 4 control points each" << std::endl;
    std::cout << "Processing " <<vertices.size()/4<< " vertices in vertex shader" << std::endl;

    glGenVertexArrays(1, &planeVAO);
    glBindVertexArray(planeVAO);

    glGenBuffers(1, &planeVBO);
    glBindBuffer(GL_ARRAY_BUFFER, planeVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), nullptr);
    glEnableVertexAttribArray(0);
    // texCoord attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(sizeof(float) * 2));
    glEnableVertexAttribArray(1);

    glPatchParameteri(GL_PATCH_VERTICES, NUM_PATCH_PTS);
}

void Plane::render()
{
    // draw mesh
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D,grass_texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D,rock_texture);
    glActiveTexture(GL_TEXTURE2);
    glBindTexture(GL_TEXTURE_2D,sand_texture);
    glBindVertexArray(planeVAO);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
// render the mesh triangle strip by triangle strip - each row at a time
    glDrawArrays(GL_PATCHES, 0, NUM_PATCH_PTS*rez*rez);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glBindVertexArray(0);
}