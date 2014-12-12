#include "secuencia.h"

Secuencia::Secuencia(int width, int height)
{
    //cam=new Camara(glm::vec3(0,0,0),70.0f,(float)width/(float)height,0.01f,1000.0f);
}

Secuencia::~Secuencia()
{
    //dtor
}

void Secuencia::addElemento(const std::string& modelName,const std::string& fileName,const std::string& texName,  const glm::vec3& p, const glm::vec3& r, const glm::vec3& s, const std::string& animName)
{
    Pieza* piez=new Pieza(modelName,fileName,texName,p,r,s);
    elementos.push_back(piez);

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
void Secuencia::setrVel(unsigned int vel)
{
    rewVel=vel;
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->getrVel()=vel;
    }
}
void Secuencia::setfVel(unsigned int vel)
{
    fwVel=vel;
    for(unsigned int e=0;e<elementos.size();e++)
    {
        elementos[e]->getfVel()=vel;
    }
}

void Secuencia::clearSec()
{
    for(unsigned int e=0;e<elementos.size();e++)
    {
        delete elementos[e];
    }
    elementos.clear();
    keyframes.clear();

    setrVel(1);
    setfVel(2);

    delete cam;

    orbita[0]=orbita[1]=0;
}

void Secuencia::run(Ventana *v,int frames)
{
    int contador=0;

    while(contador<frames)
    {
        for(unsigned int e=0;e<keyframes.size();e++)
        {
            if(contador==keyframes[e].x)
            {
                switch(keyframes[e].y)
                {
                    case 0:
                        setfVel(keyframes[e].z);
                        break;
                    case 1:
                        setrVel(keyframes[e].z);
                        break;
                    case 2:
                        if(keyframes[e].z>0){Ffwd();}
                        else{Rewind();}
                        break;
                }
            }
        }

        v->Clear(clearColor[0],clearColor[1],clearColor[2],1.0);
        Update();

        if(orbita[0]!=0)
        {
            getCam()->OrbitRight(orbita[0],orbita[1]);
        }

        v->Update();

        contador++;
    }
    clearSec();
}

void Secuencia::setMovCam(int tipo, float param1, float param2)
{
    switch(tipo)
    {
        case 0:
            orbita[0]=param1;
            orbita[1]=param2;
            break;
    }
}

void Secuencia::setKeyFrame(int nframe, int accion, int magnitud)
{
    keyframe i;
    i.x=nframe;i.y=accion,i.z=magnitud;
    keyframes.push_back(i);
}
