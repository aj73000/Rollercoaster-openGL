#include "Cube.h"

#include <iostream>

Cube::Cube()
{
	m_vaoID = 0;
	m_vboID = 0;
	ibo = 0;
}

void Cube::render()
{
    glBindVertexArray(m_vaoID);// select VAO

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glDrawElements(GL_TRIANGLES, numOfTris* numOfVertsPerTriangle, GL_UNSIGNED_INT, nullptr);

    glBindVertexArray(0); //unbind the vertex array object
}

void Cube::constructGeometryRef(float& minX, float& maxX, float& minY, float& maxY, float& minZ, float& maxZ)
{
	// First simple object
	verts[0] = minX;   verts[ 1] = minY;  verts[ 2] = minZ;
	verts[3] = minX;   verts[ 4] =  maxY;  verts[ 5] = minZ;
	verts[6] =  maxX;   verts[ 7] =  maxY;  verts[ 8] = minZ;
	verts[9] =  maxX;   verts[10] = minY;  verts[11] =  minZ;

	verts[12] = minX;   verts[13] = minY;  verts[14] = maxZ;
	verts[15] = minX;   verts[16] =  maxY;  verts[17] = maxZ;
	verts[18] =  maxX;   verts[19] =  maxY;  verts[20] = maxZ;
	verts[21] =  maxX;   verts[22] = minY;  verts[23] = maxZ;

	tris[0]=0; tris[1]=1; tris[2]=2;
	tris[3]=0; tris[4]=2; tris[5]=3;
	tris[6]=4; tris[7]=6; tris[8]=5;
	tris[9]=4; tris[10]=7; tris[11]=6;
	tris[12]=1; tris[13]=5; tris[14]=6;
	tris[15]=1; tris[16]=6; tris[17]=2;
	tris[18]=0; tris[19]=7; tris[20]=4;
	tris[21]=0; tris[22]=3; tris[23]=7;
	tris[24]=0; tris[25]=5; tris[26]=1;
	tris[27]=0; tris[28]=4; tris[29]=5;
	tris[30]=3; tris[31]=2; tris[32]=7;
	tris[33]=2; tris[34]=6; tris[35]=7;

    // VAO allocation
    glGenVertexArrays(1, &m_vaoID);
    glGenBuffers(1, &m_vboID);
    glGenBuffers(1, &ibo);

    // First VAO setup
    glBindVertexArray(m_vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    //initialises data storage of vertex buffer object
    glBufferData(GL_ARRAY_BUFFER, numOfVerts* numOfValuesPerVertex *sizeof(GLfloat), verts, GL_STATIC_DRAW);

    // aPos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, numOfValuesPerVertex, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfTris * numOfVertsPerTriangle * sizeof(unsigned int), tris, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}

void Cube::constructGeometry(float minX, float maxX, float minY, float maxY, float minZ, float maxZ)
{
    // First simple object
    verts[0] = minX;   verts[ 1] = minY;  verts[ 2] = minZ;
    verts[3] = minX;   verts[ 4] =  maxY;  verts[ 5] = minZ;
    verts[6] =  maxX;   verts[ 7] =  maxY;  verts[ 8] = minZ;
    verts[9] =  maxX;   verts[10] = minY;  verts[11] =  minZ;

    verts[12] = minX;   verts[13] = minY;  verts[14] = maxZ;
    verts[15] = minX;   verts[16] =  maxY;  verts[17] = maxZ;
    verts[18] =  maxX;   verts[19] =  maxY;  verts[20] = maxZ;
    verts[21] =  maxX;   verts[22] = minY;  verts[23] = maxZ;

    tris[0]=0; tris[1]=1; tris[2]=2;
    tris[3]=0; tris[4]=2; tris[5]=3;
    tris[6]=4; tris[7]=6; tris[8]=5;
    tris[9]=4; tris[10]=7; tris[11]=6;
    tris[12]=1; tris[13]=5; tris[14]=6;
    tris[15]=1; tris[16]=6; tris[17]=2;
    tris[18]=0; tris[19]=7; tris[20]=4;
    tris[21]=0; tris[22]=3; tris[23]=7;
    tris[24]=0; tris[25]=5; tris[26]=1;
    tris[27]=0; tris[28]=4; tris[29]=5;
    tris[30]=3; tris[31]=2; tris[32]=7;
    tris[33]=2; tris[34]=6; tris[35]=7;

    // VAO allocation
    glGenVertexArrays(1, &m_vaoID);
    glGenBuffers(1, &m_vboID);
    glGenBuffers(1, &ibo);

    // First VAO setup
    glBindVertexArray(m_vaoID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    //initialises data storage of vertex buffer object
    glBufferData(GL_ARRAY_BUFFER, numOfVerts* numOfValuesPerVertex *sizeof(GLfloat), verts, GL_STATIC_DRAW);

    // aPos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, numOfValuesPerVertex, GL_FLOAT, GL_FALSE, 0, nullptr);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numOfTris * numOfVertsPerTriangle * sizeof(unsigned int), tris, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
}