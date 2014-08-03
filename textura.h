#ifndef TEXTURA_H
#define TEXTURA_H

#include <string>
#include <GL/glew.h>

class Textura
{
    public:
        Textura(const std::string& fileName);
        void Bind(unsigned int unit);

        virtual ~Textura();
    protected:
    private:
        Textura(const Textura& other){}
        void operator=(const Textura& other){}

        GLuint m_texture;

};

#endif // TEXTURA_H
