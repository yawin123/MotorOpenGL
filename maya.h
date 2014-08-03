#ifndef MAYA_H
#define MAYA_H

#include <glm/glm.hpp>
#include <GL/glew.h>
#include "obj_loader.h"


class Vertice
{
    public:
        Vertice(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& norm)
        {
            this->pos=pos;
            this->texCoord = texCoord;
            this->normal=norm;
        }

        inline glm::vec3* getPos(){return &pos;}
        inline glm::vec2* getTexCoord(){return &texCoord;}
        inline glm::vec3* getNormal(){return &normal;}
    protected:
    private:
        glm::vec3 pos;
        glm::vec2 texCoord;
        glm::vec3 normal;
};

class Maya
{
    public:
        Maya(const std::string& fileName);
        Maya(Vertice* vertices, unsigned int numVertices, unsigned int* indices, unsigned int numIndices);
        void Draw();
        virtual ~Maya();
    protected:
    private:
        Maya(const Maya& other);
        Maya& operator=(const Maya& other);

        void InitMesh(const IndexedModel& modelo);
        enum
        {
            POSICION_VB,
            TEXCOORD_VB,
            NORMAL_VB,

            INDEX_VB,
            NUM_BUFFERS
        };

        GLuint m_vertexArrayObject;
        GLuint m_vertexArrayBuffers[NUM_BUFFERS];
        unsigned int m_drawCount;
};

#endif // MAYA_H
