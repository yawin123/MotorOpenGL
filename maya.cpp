#include "maya.h"
#include "obj_loader.h"
#include <vector>
#include <iostream>

Maya::Maya(const std::string& fileName)
{
    IndexedModel modelo = OBJModel(fileName).ToIndexedModel();
    InitMesh(modelo);

}
Maya::Maya(Vertice* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices)
{
    IndexedModel modelo;

    for(unsigned int i=0;i<numVertices;i++)
    {
        modelo.positions.push_back(*vertices[i].getPos());
        modelo.texCoords.push_back(*vertices[i].getTexCoord());
        modelo.normals.push_back(*vertices[i].getNormal());
    }
    for(unsigned int i=0;i<numIndices;i++)
    {
        modelo.indices.push_back(indices[i]);
    }

    InitMesh(modelo);
}

Maya::~Maya()
{
    glDeleteVertexArrays(1,&m_vertexArrayObject);
}

void Maya::InitMesh(const IndexedModel& modelo)
{
    m_drawCount=modelo.indices.size();

    glGenVertexArrays(1,&m_vertexArrayObject);
    glBindVertexArray(m_vertexArrayObject);

    glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
    glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[POSICION_VB]);
    glBufferData(GL_ARRAY_BUFFER,modelo.positions.size()*sizeof(modelo.positions[0]),&modelo.positions[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
    glBufferData(GL_ARRAY_BUFFER, modelo.texCoords.size() * sizeof(modelo.texCoords[0]), &modelo.texCoords[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,0,0);

    glBindBuffer(GL_ARRAY_BUFFER,m_vertexArrayBuffers[NORMAL_VB]);
    glBufferData(GL_ARRAY_BUFFER,modelo.normals.size()*sizeof(modelo.normals[0]),&modelo.normals[0],GL_STATIC_DRAW);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,0,0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_vertexArrayBuffers[INDEX_VB]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, modelo.indices.size() * sizeof(modelo.indices[0]), &modelo.indices[0],GL_STATIC_DRAW);

    glBindVertexArray(0);
}

void Maya::Draw()
{
    glBindVertexArray(m_vertexArrayObject);
    glDrawElements(GL_TRIANGLES,m_drawCount,GL_UNSIGNED_INT,0);
        std::cout<<"2"<<std::endl;
    //glDrawArrays(GL_TRIANGLES,0,m_drawCount);
    glBindVertexArray(0);
}
