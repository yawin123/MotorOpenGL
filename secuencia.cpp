#include "secuencia.h"

Secuencia::Secuencia(int width, int height)
{
    //cam=new Camara(glm::vec3(0,0,0),70.0f,(float)width/(float)height,0.01f,1000.0f);
}

Secuencia::~Secuencia()
{
    //dtor
}

void Secuencia::addElemento(const std::string& modelName,const std::string& fileName,const std::string& texName, const std::string& animName)
{
    Pieza* p=new Pieza(modelName,fileName,texName);
    elementos.push_back(p);

    if(animName!="")
        elementos[elementos.size()-1]->cargaTrayecto(animName);
}
void Secuencia::setCam(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
{

    cam=new Camara(pos,fov,aspect,zNear,zFar);
}
void Secuencia::Update()
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->Update(*cam);
    }
}

void Secuencia::Play()
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->Play();
    }
}
void Secuencia::Pause()
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->Pause();
    }
}
void Secuencia::Stop()
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->Stop();
    }
}
void Secuencia::Loop()
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->Loop();
    }
}
void Secuencia::Ffwd()
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->Ffwd();
    }
}
void Secuencia::Rewind()
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->Rewind();
    }
}
void Secuencia::Frame(int f)
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->Frame(f);
    }
}
