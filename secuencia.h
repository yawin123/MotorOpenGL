#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "pieza.h"

class Secuencia
{
    public:
        Secuencia(int width, int height);
        virtual ~Secuencia();

        void addElemento(const std::string& modelName,const std::string& fileName,const std::string& texName, const std::string& animName="");
        void setCam(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
        inline Camara* getCam(){return cam;}
        void Frame(int f);
        void Update();

        void Rewind();
        void Ffwd();
        void Play();
        void Pause();
        void Stop();
        void Loop();
    protected:
    private:
        std::vector<Pieza*> elementos;
        Camara *cam;
};

#endif // SECUENCIA_H
