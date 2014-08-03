#ifndef SHADER_H
#define SHADER_H

#include <string>
#include <GL/glew.h>
#include "transform.h"
#include "camara.h"

class Shader
{
    public:
        Shader(const std::string& fileName);

        void Bind();
        void Update(const Transform& transform, const Camara& camara);

        virtual ~Shader();
    protected:
    private:
        static const unsigned int NUM_SHADER=2;

        Shader(const Shader& other);
        Shader& operator=(const Shader& other);

        enum
        {
            TRANSFORM_U,
            NUM_UNIFORMS
        };

        GLuint m_programa;
        GLuint m_shaders[NUM_SHADER];
        GLuint m_uniforms[NUM_UNIFORMS];
};

#endif // SHADER_H
