#ifndef SECUENCIA_H
#define SECUENCIA_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include "ventana.h"
#include "pieza.h"

struct keyframe
{
    int x, y, z;
};

class Secuencia
{
    public:
        Secuencia(int width, int height);
        virtual ~Secuencia();

        void addElemento(const std::string& modelName,const std::string& fileName,const std::string& texName, const glm::vec3& p, const glm::vec3& r, const glm::vec3& s, const std::string& animName="");
        void setCam(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar);
        inline Camara* getCam(){return cam;}
        void Frame(int f);
        void Update();
        void clearSec();

        void Rewind();
        void Ffwd();
        void Play();
        void Pause();
        void Stop();
        void Loop();

        void run(Ventana *v, int frames=1000);

        unsigned int rVel(){return rewVel;}
        unsigned int fVel(){return fwVel;}
        void setrVel(unsigned int vel);
        void setfVel(unsigned int vel);

        void setMovCam(int tipo,float param1=0.0,float param2=0.0);
        void setKeyFrame(int nframe, int accion, int magnitud);
        inline void setClearColor(float r, float g, float b){clearColor[0]=r;clearColor[1]=g;clearColor[2]=b;}
    protected:
    private:
        std::vector<Pieza*> elementos;
        std::vector<keyframe> keyframes;
        Camara *cam;
        unsigned int rewVel=1, fwVel=2;
        float orbita[2]={0,0};
        float clearColor[3]={255.0,255.0,255.0};
};
#endif // SECUENCIA_H
