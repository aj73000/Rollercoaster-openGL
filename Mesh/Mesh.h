//
// Created by arthur on 2/20/24.
//

#ifndef LEARNOPENGL_MESH_H
#define LEARNOPENGL_MESH_H

#include "../Texture/Texture.h"
#include "../Vector/Vertex.h"
#include "vector"
#include "../shaders/Shader.h"
#include "../Cube/Cube.h"

class Mesh {
public:
    // mesh data
    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture>      textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw(Shader &shader);
private:
    //  render data
    unsigned int VAO, VBO, EBO;

    void setupMesh();
};


#endif //LEARNOPENGL_MESH_H
