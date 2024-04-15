#pragma once

#include <vector>
#include "GL/glew.h"
#include "../shaders/Shader.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "memory"


class Cube
{
private:
	GLuint m_vaoID;		    // vertex array object
	GLuint m_vboID;		// two VBOs - used for colours and vertex data
	GLuint ibo;
    GLuint textureID;
    //identifier for the triangle indices

	const static int numOfVerts = 8;
	const static int numOfTris = 12;
	const static int numOfValuesPerVertex = 3;
	const static int numOfVertsPerTriangle = 3;

    int x,y,z;
	
	float verts[numOfVerts*3];
	float cols[numOfVerts*3];
	unsigned int tris[numOfTris *3];
public:
	Cube();
    void constructGeometryRef(float& minX, float& maxX, float& minY, float& maxY, float& minZ, float& maxZ);
    void constructGeometry(float minX, float maxX, float minY, float maxY, float minZ, float maxZ);
	void render();
};