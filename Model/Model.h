//
// Created by arthur on 2/20/24.
//

#ifndef LEARNOPENGL_MODEL_H
#define LEARNOPENGL_MODEL_H

#include "../shaders/Shader.h"
#include "../Texture/Texture.h"
#include "../Mesh/Mesh.h"
#include "vector"

#include "../Cube/Cube.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stb/stb_image.h>


class Model
{
public:

    explicit Model(const char *path)
    {
        loadModel(path);
    }
    void Draw(Shader &shader);

private:
    // model data
    std::vector<Mesh> meshes;
    std::string directory;
    std::vector<Texture> textures_loaded;

    void loadModel(std::string path);
    void processNode(aiNode *node, const aiScene *scene);
    Mesh processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,std::string typeName);

};

#endif //LEARNOPENGL_MODEL_H
