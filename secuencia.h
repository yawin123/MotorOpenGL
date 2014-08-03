#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "pieza.h"
#include "camara.h"

class Secuencia
{
    public:
        Secuencia(int width, int height);
        virtual ~Secuencia();

        void addElemento(const std::string& modelName,const std::string& fileName,const std::string& texName, const std::string& animName="");
        void setCam(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
        void Update();
    protected:
    private:
        std::vector<Pieza*> elementos;
        Camara* cam;
};

#endif // SECUENCIA_H
