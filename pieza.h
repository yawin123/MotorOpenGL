#ifndef PIEZA_H
#define PIEZA_H
#include <vector>
#include "shader.h"
#include "maya.h"
#include "transform.h"
#include "textura.h"
#include "camara.h"


class Pieza
{
    public:
        Pieza(Vertice* vertices, unsigned int numVertices,const std::string& fileName,const std::string& texName);
        Pieza(const std::string& modelName,const std::string& fileName,const std::string& texName);
        void Update(const Camara& camara);

        void cargaTrayecto(const std::string& fileName);
        void addTrayecto(const glm::vec3& p,const glm::vec3& r,const glm::vec3& s);
        void addTrayecto(const glm::vec3& tr,unsigned int opc);

        //glm::vec3& Bezier(const glm::vec3& c0,const glm::vec3& c3,const glm::vec2& c1,const glm::vec2& c2,float& t); //Calcula el valor de la curva entre c0 y c3

        void addTrayectoBez(const glm::mat3x3& prs,const glm::mat3x3& vec1,const glm::mat3x3& vec2,unsigned int temp);
        void addTrayectoBez(const glm::mat3& m,const glm::mat2x2& v,unsigned int opc,unsigned int temp);

        void mueve();
        virtual ~Pieza();

        Maya* maya;
        Shader* shader;
        Textura* textura;
        Transform t;

        inline glm::vec3& getPos(){return t.getPos();}
        inline glm::vec3& getRot(){return t.getRot();}
        inline glm::vec3& getScale(){return t.getScale();}
        inline unsigned int& getrVel(){return rewVel;}
        inline bool& getPlay(){return isPlay;}
        inline bool& getLoop(){return isLoop;}

        inline void Rewind(){if(isRewind)isRewind=false; else isRewind=true;  isFfwd=false; }
        inline void Ffwd()  {if(isFfwd) isFfwd=false; else isFfwd=true;  isRewind=false;  }
        inline void Play()  {isPlay=true; }
        inline void Pause() {isPlay=false;}
        inline void Stop()  {isPlay=false;   isFfwd=false;   isRewind=false;   tActual=0;}
        inline void Loop() {if(isLoop) isLoop=false; else isLoop=true;}

        inline void setPos(const glm::vec3& pos){t.setPos(pos);}
        inline void setRot(const glm::vec3& rot){t.setRot(rot);}
        inline void setScale(const glm::vec3& scale){t.setScale(scale);}

    protected:
    private:
        Pieza(const Pieza& other);
        void operator=(const Pieza& other);

        unsigned int indices[3]={0,1,2};

        std::vector<glm::vec3> trayectop;
        std::vector<glm::vec3> trayector;
        std::vector<glm::vec3> trayectos;
        int tActual=0;

        unsigned int rewVel=1, fwVel=2;
        bool isRewind=false;
        bool isFfwd=false;
        bool isPlay=false;
        bool isLoop=false;
};

#endif // PIEZA_H
