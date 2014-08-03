#include "secuencia.h"

Secuencia::Secuencia(int width, int height)
{
    cam=new Camara(glm::vec3(0,0,0),70.0f,(float)width/(float)height,0.01f,1000.0f);
}

Secuencia::~Secuencia()
{
    //dtor
}

void Secuencia::addElemento(const std::string& modelName,const std::string& fileName,const std::string& texName, const std::string& animName)
{
    Pieza* p=new Pieza(modelName,fileName,texName);
    elementos.push_back(p);
    elementos[elementos.size()-1]->cargaTrayecto(animName);
}
void Secuencia::setCam(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{
    cam->getPos()=pos;
}
void Secuencia::Update()
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->Update(cam);
    }
}
