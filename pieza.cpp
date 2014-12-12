#include "pieza.h"
#include "textura.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include <cstdlib>

Pieza::Pieza(Vertice* vertices, unsigned int numVertices,const std::string& fileName,const std::string& texName)
{
    maya=new Maya(vertices,numVertices,indices,sizeof(indices)/sizeof(indices[0]));
    shader=new Shader(fileName);
    textura=new Textura(texName);
}
Pieza::Pieza(const std::string& modelName,const std::string& fileName,const std::string& texName, const glm::vec3& p, const glm::vec3& r, const glm::vec3& s)
{
    maya=new Maya(modelName);
    shader=new Shader(fileName);
    textura=new Textura(texName);
    t.getPos().x=p.x; t.getPos().y=p.y; t.getPos().z=p.z;
    t.getRot().x=r.x; t.getRot().y=r.y; t.getRot().z=r.z;
    t.getScale().x=s.x; t.getScale().y=s.y; t.getScale().z=s.z;
}

Pieza::~Pieza()
{
    //dtor
}

void Pieza::Update(const Camara& camara)
{
    if(trayectop.size()>0)
    {
        mueve();
    }

    shader->Bind();
    textura->Bind(0);
    shader->Update(t,camara);
    maya->Draw();
}

void Pieza::addTrayecto(const glm::vec3& p,const glm::vec3& r,const glm::vec3& s)
{
    glm::vec3 finalPosition,finalRotation,finalScale;

    finalPosition.x = t.getPos().x + p.x*std::cos((p.y*M_PI)/180) * std::cos((p.z*M_PI)/180);
    finalPosition.y = t.getPos().y + p.x*std::sin((p.y*M_PI)/180) * std::cos((p.z*M_PI)/180);
    finalPosition.z = t.getPos().z + p.x*std::sin((p.z*M_PI)/180);

    finalRotation.x = t.getRot().x + r.x * std::cos((r.y*M_PI)/180) * std::cos((r.z*M_PI)/180);
    finalRotation.y = t.getRot().y + r.x * std::sin((r.y*M_PI)/180) * std::cos((r.z*M_PI)/180);
    finalRotation.z = t.getRot().z + r.x * std::sin((r.z*M_PI)/180);

    finalScale.x = t.getScale().x + s.x*std::cos((s.y*M_PI)/180) * std::cos((s.z*M_PI)/180);
    finalScale.y = t.getScale().y + s.x*std::sin((s.y*M_PI)/180) * std::cos((s.z*M_PI)/180);
    finalScale.z = t.getScale().z + s.x*std::sin((s.z*M_PI)/180);

    trayectop.push_back(finalPosition);
    trayector.push_back(finalRotation);
    trayectos.push_back(finalScale);
}
void Pieza::addTrayecto(const glm::vec3& tr, unsigned int opc)
{
    switch(opc)
    {
        case 0: //Posición
            if(trayectop.size()>0)
            {
                glm::vec3 aux; aux.x=trayectop[trayectop.size()-1].x+tr.x; aux.y=trayectop[trayectop.size()-1].y+tr.y; aux.z=trayectop[trayectop.size()-1].z+tr.z;
                trayectop.push_back(aux); //Asignamos la misma rotación que en el paso anterior;
                trayector.push_back(trayector[trayector.size()-1]); //Asignamos la misma rotación que en el paso anterior;
                trayectos.push_back(trayectos[trayectos.size()-1]); //Asignamos la misma escala que en el paso anterior;
            }
            else
            {
                glm::vec3 aux; aux.x=getPos().x+tr.x; aux.y=getPos().y+tr.y; aux.z=getPos().z+tr.z;
                trayectop.push_back(aux);
                trayector.push_back(t.getRot());
                trayectos.push_back(t.getScale());
            }
            break;

        case 1: //Rotación
            if(trayectop.size()>0)
            {
                glm::vec3 aux; aux.x=trayector[trayector.size()-1].x+tr.x; aux.y=trayector[trayector.size()-1].y+tr.y; aux.z=trayector[trayector.size()-1].z+tr.z;
                trayectop.push_back(trayectop[trayectop.size()-1]); //Asignamos la misma posición que en el paso anterior;
                trayector.push_back(aux); //Asignamos la misma posición que en el paso anterior;
                trayectos.push_back(trayectos[trayectos.size()-1]); //Asignamos la misma escala que en el paso anterior;
            }
            else
            {
                glm::vec3 aux; aux.x=getRot().x+tr.x; aux.y=getRot().y+tr.y; aux.z=getRot().z+tr.z;
                trayectop.push_back(t.getPos());
                trayector.push_back(aux);
                trayectos.push_back(t.getScale());
            }
            break;

        case 2: //Escala
            if(trayectop.size()>0)
            {
                glm::vec3 aux; aux.x=trayectos[trayectos.size()-1].x+tr.x; aux.y=trayectos[trayectos.size()-1].y+tr.y; aux.z=trayectos[trayectos.size()-1].z+tr.z;
                trayectop.push_back(trayectop[trayectop.size()-1]); //Asignamos la misma posición que en el paso anterior;
                trayector.push_back(trayector[trayector.size()-1]); //Asignamos la misma rotación que en el paso anterior;
                trayectos.push_back(aux); //Asignamos la misma posición que en el paso anterior;
            }
            else
            {
                glm::vec3 aux; aux.x=getScale().x+tr.x; aux.y=getScale().y+tr.y; aux.z=getScale().z+tr.z;
                trayectop.push_back(t.getPos());
                trayector.push_back(t.getRot());
                trayectos.push_back(aux);
            }
            break;
    }
}
void Pieza::cargaTrayecto(const std::string& fileName) //Parseador de animaciones
{
    std::ifstream lector;
    lector.open((fileName).c_str());

    std::string salida;
    std::string linea;

    if(lector.is_open())
    {
        while(lector.good())
        {
            getline(lector,linea);

            unsigned int i,j=0,ding=1,opc;
            std::vector<float> aux;

            opc=linea[0];
            for(i=2;i<linea.size();i++)
            {
                if(ding==1)
                {
                    if(j!=0)
                    {
                        std::string st="";
                        for(int iy=j;iy<i;iy++)
                        {
                            st+=linea[iy];
                        }
                        aux.push_back(std::atof(st.c_str()));
                    }
                    ding=0;
                    j=i;
                }
                if(linea[i]==','|| linea[i]=='|')
                {
                    ding=1;
                }
            }
            switch(opc)
            {
                case 48: //48 ASCII = int 0
                    if(aux.size()>0)
                    {
                        addTrayecto(glm::vec3(aux[0],aux[1],aux[2]),aux[3]);
                    }
                    break;
                case 49: //49 ASCII = int 1
                    if(aux.size()>0)
                    {
                        addTrayecto(glm::vec3(aux[0],aux[1],aux[2]),glm::vec3(aux[3],aux[4],aux[5]),glm::vec3(aux[6],aux[7],aux[8]));
                    }
                    break;
                case 50: //50 ASCII = int 2
                    if(aux.size()>0)
                    {
                        //addTrayectoExt(glm::vec3(aux[0],aux[1],aux[2]),aux[3],aux[4]);
                    }
                    break;
                case 51: //51 ASCII = int 3
                    if(aux.size()>0)
                    {
                        glm::mat3x3 prs;prs[0][0]=aux[0];prs[0][1]=aux[1];prs[0][2]=aux[2];prs[1][0]=aux[3];prs[1][1]=aux[4];prs[1][2]=aux[5];prs[2][0]=aux[6];prs[2][1]=aux[7];prs[2][2]=aux[8];
                        glm::mat3x3 vec1;vec1[0][0]=aux[9];vec1[0][1]=aux[10];vec1[0][2]=aux[11];vec1[1][0]=aux[12];vec1[1][1]=aux[13];vec1[1][2]=aux[14];vec1[2][0]=aux[15];vec1[2][1]=aux[16];vec1[2][2]=aux[17];
                        glm::mat3x3 vec2;vec2[0][0]=aux[18];vec2[0][1]=aux[19];vec2[0][2]=aux[20];vec2[1][0]=aux[21];vec2[1][1]=aux[22];vec2[1][2]=aux[23];vec2[2][0]=aux[24];vec2[2][1]=aux[25];vec2[2][2]=aux[26];
                        addTrayectoBez(prs,vec1,vec2,aux[27]);
                    }
                case 52: //52 ASCII = int 4
                    if(aux.size()>0)
                    {
                        //addTrayectoBez(glm::vec3(aux[0],aux[1],aux[2]),glm::vec3(aux[3],aux[4],aux[5]),glm::vec3(aux[6],aux[7],aux[8]),aux[9],aux[10]);
                    }
                    break;
                case 53: //53 ASCII = int 5
                    if(aux.size()>0)
                    {
                        //addTrayectoBez(glm::vec3(aux[0],aux[1],aux[2]),glm::vec3(aux[3],aux[4],aux[5]),glm::vec3(aux[6],aux[7],aux[8]),glm::vec3(aux[9],aux[10],aux[11]),glm::vec3(aux[12],aux[13],aux[14]),aux[15]);
                    }
                     break;
            }
            aux.clear();

        }
    }
    else
    {
        std::cerr<<"Imposible cargar la animación: "<<fileName<<std::endl;
    }
}
void Pieza::addTrayectoBez(const glm::mat3x3& prs,const glm::mat3x3& vec1,const glm::mat3x3& vec2,unsigned int temp)
{
    //prs0 son las coordenadas de inicio
    //prs1 son las coordenadas relativas a prs0 del vector1
    //prs2 son las coordenadas relativas a prs del vector2
    //prs  son las coordenadas de destino

    glm::mat3x3 prs0;{ //Inicio

        prs0[0][0]=trayectop[trayectop.size()-1].x;
        prs0[0][1]=trayectop[trayectop.size()-1].y;
        prs0[0][2]=trayectop[trayectop.size()-1].z;
        prs0[1][0]=trayector[trayector.size()-1].x;
        prs0[1][1]=trayector[trayector.size()-1].y;
        prs0[1][2]=trayector[trayector.size()-1].z;
        prs0[2][0]=trayectos[trayectos.size()-1].x;
        prs0[2][1]=trayectos[trayectos.size()-1].y;
        prs0[2][2]=trayectos[trayectos.size()-1].z;
    }
    glm::mat3x3 prs4;{ //Destino

        prs4[0][0] = prs0[0][0] + prs[0][0] * std::cos((prs[0][1]*M_PI)/180) * std::cos((prs[0][2]*M_PI)/180);
        prs4[0][1] = prs0[0][1] + prs[0][0] * std::sin((prs[0][1]*M_PI)/180) * std::cos((prs[0][2]*M_PI)/180);
        prs4[0][2] = prs0[0][2] + prs[0][0] * std::sin((prs[0][2]*M_PI)/180);
        prs4[1][0] = prs0[1][0] + prs[1][0] * std::cos((prs[1][1]*M_PI)/180) * std::cos((prs[1][2]*M_PI)/180);
        prs4[1][1] = prs0[1][1] + prs[1][0] * std::sin((prs[1][1]*M_PI)/180) * std::cos((prs[1][2]*M_PI)/180);
        prs4[1][2] = prs0[1][2] + prs[1][0] * std::sin((prs[1][2]*M_PI)/180);
        prs4[2][0] = prs0[2][0] + prs[2][0] * std::cos((prs[2][1]*M_PI)/180) * std::cos((prs[2][2]*M_PI)/180);
        prs4[2][1] = prs0[2][1] + prs[2][0] * std::sin((prs[2][1]*M_PI)/180) * std::cos((prs[2][2]*M_PI)/180);
        prs4[2][2] = prs0[2][2] + prs[2][0] * std::sin((prs[2][2]*M_PI)/180);
    }
    glm::mat3x3 prs1;{
        prs1[0][0]=prs0[0][0]+vec1[0][0]*cosf(vec1[0][1])*cosf(vec1[0][2]);
        prs1[0][1]=prs0[0][1]+vec1[0][0]*sinf(vec1[0][1])*cosf(vec1[0][2]);
        prs1[0][2]=prs0[0][2]+vec1[0][0]*sinf(vec1[0][2]);

        prs1[1][0]=prs0[1][0]+vec1[1][0]*cosf(vec1[1][1])*cosf(vec1[1][2]);
        prs1[1][1]=prs0[1][1]+vec1[1][0]*sinf(vec1[1][1])*cosf(vec1[1][2]);
        prs1[1][2]=prs0[1][2]+vec1[1][0]*sinf(vec1[1][2]);

        prs1[2][0]=prs0[2][0]+vec1[2][0]*cosf(vec1[2][1])*cosf(vec1[2][2]);
        prs1[2][1]=prs0[2][1]+vec1[2][0]*sinf(vec1[2][1])*cosf(vec1[2][2]);
        prs1[2][2]=prs0[2][2]+vec1[2][0]*sinf(vec1[2][2]);
    }
    glm::mat3x3 prs2;{
        prs2[0][0]=prs4[0][0]+vec2[0][0]*cosf(vec2[0][1])*cosf(vec2[0][2]);
        prs2[0][1]=prs4[0][1]+vec2[0][0]*sinf(vec2[0][1])*cosf(vec2[0][2]);
        prs2[0][2]=prs4[0][2]+vec2[0][0]*sinf(vec2[0][2]);

        prs2[1][0]=prs4[1][0]+vec2[1][0]*cosf(vec2[1][1])*cosf(vec2[1][2]);
        prs2[1][1]=prs4[1][1]+vec2[1][0]*sinf(vec2[1][1])*cosf(vec2[1][2]);
        prs2[1][2]=prs4[1][2]+vec2[1][0]*sinf(vec2[1][2]);

        prs2[2][0]=prs4[2][0]+vec2[2][0]*cosf(vec2[2][1])*cosf(vec2[2][2]);
        prs2[2][1]=prs4[2][1]+vec2[2][0]*sinf(vec2[2][1])*cosf(vec2[2][2]);
        prs2[2][2]=prs4[2][2]+vec2[2][0]*sinf(vec2[2][2]);
    }

    glm::vec3 B;
    float ut=1.0/(float)temp;

    for(int i=1;i<temp;i++)
    {
        float t=ut*i; //Calculamos el valor de "t";

        //Posición
            B.x=prs0[0][0]*pow(1-t,3) + 3*prs1[0][0]*t*pow(1-t,2) + 3*prs2[0][0]*pow(t,2)*(1-t) + prs4[0][0]*pow(t,3);
            B.y=prs0[0][1]*pow(1-t,3) + 3*prs1[0][1]*t*pow(1-t,2) + 3*prs2[0][1]*pow(t,2)*(1-t) + prs4[0][1]*pow(t,3);
            B.z=prs0[0][2]*pow(1-t,3) + 3*prs1[0][2]*t*pow(1-t,2) + 3*prs2[0][2]*pow(t,2)*(1-t) + prs4[0][2]*pow(t,3);
            trayectop.push_back(B);

        //Rotación
            B.x=prs0[1][0]*pow(1-t,3) + 3*prs1[1][0]*t*pow(1-t,2) + 3*prs2[1][0]*pow(t,2)*(1-t) + prs4[1][0]*pow(t,3);
            B.y=prs0[1][1]*pow(1-t,3) + 3*prs1[1][1]*t*pow(1-t,2) + 3*prs2[1][1]*pow(t,2)*(1-t) + prs4[1][1]*pow(t,3);
            B.z=prs0[1][2]*pow(1-t,3) + 3*prs1[1][2]*t*pow(1-t,2) + 3*prs2[1][2]*pow(t,2)*(1-t) + prs4[1][2]*pow(t,3);
            trayector.push_back(B);

        //Escala
            B.x=prs0[2][0]*pow(1-t,3) + 3*prs1[2][0]*t*pow(1-t,2) + 3*prs2[2][0]*pow(t,2)*(1-t) + prs4[2][0]*pow(t,3);
            B.y=prs0[2][1]*pow(1-t,3) + 3*prs1[2][1]*t*pow(1-t,2) + 3*prs2[2][1]*pow(t,2)*(1-t) + prs4[2][1]*pow(t,3);
            B.z=prs0[2][2]*pow(1-t,3) + 3*prs1[2][2]*t*pow(1-t,2) + 3*prs2[2][2]*pow(t,2)*(1-t) + prs4[2][2]*pow(t,3);
            trayectos.push_back(B);
    }
}
void Pieza::addTrayectoBez(const glm::mat3& m,const glm::mat2x2& v,unsigned int opc,unsigned int temp)
{
    /*glm::mat3 dos,tres;
    glm::mat2 v2={0,0};
    switch(opc)
    {
        case 0:
            if(trayectop.size()>0)
            {
                dos=trayector[trayector.size()-1]; //Asignamos la misma rotación que en el paso anterior;
                tres=trayectos[trayectos.size()-1]; //Asignamos la misma escala que en el paso anterior;
            }
            else
            {
                dos=t.getRot();
                tres=t.getScale();
            }
            addTrayectoBez(p3,p1,p2,dos,tres,temp);                             //Asignamos la nueva posición;
            break;
        case 1:
            if(trayectop.size()>0)
            {
                dos=trayectop[trayectop.size()-1]; //Asignamos la misma posición que en el paso anterior;
                tres=trayectos[trayectos.size()-1]; //Asignamos la misma escala que en el paso anterior;
            }
            else
            {
                dos=t.getPos();
                tres=t.getScale();
            }
            addTrayectoBez(dos,p1,p2,p3,tres,temp);                             //Asignamos la nueva rotación;
            break;
        case 2:
            if(trayectop.size()>0)
            {
                dos=trayectop[trayectop.size()-1]; //Asignamos la misma posición que en el paso anterior;
                tres=trayector[trayector.size()-1]; //Asignamos la misma rotación que en el paso anterior;
            }
            else
            {
                dos=t.getPos();
                tres=t.getRot();
            }
            addTrayectoBez(dos,p1,p2,tres,p3,temp);                             //Asignamos la nueva escala;
            break;
    }*/
}

void Pieza::mueve()
{
    if(!isRewind)
    {
        if(isFfwd)
        {
            if(isPlay)tActual+=fwVel;
        }
        else
        {
            if(isPlay)tActual++;
        }

        if(tActual>trayectop.size()-1)
        {
            if(!isLoop)
                tActual=trayectop.size()-1;
            else
                tActual=0;
        }
    }
    else
    {
        if(isPlay)tActual-=rewVel;

        if(tActual<0)
        {
            if(isLoop)
                tActual=trayectop.size()-1;
            else
                tActual=0;
        }
    }


    t.setPos(trayectop[tActual]);
    t.setRot(trayector[tActual]);
    t.setScale(trayectos[tActual]);
}

void Pieza::Frame(long int i)
{
    if(isLoop)
    {
        if(i<0)
        {
            while(i<0)
            {
                i=(trayectop.size()-1)-abs(i);
            }
        }
        else
        {
            if(i>trayectop.size()-1)
            {
                while(i>trayectop.size()-1)
                {
                    i-=trayectop.size()-1;
                }
            }
        }
    }
    else
    {
        if(i<1)
        {
            i=1;
        }
        else
        {
            if(i>trayectop.size()-1)
            {
                i=trayectop.size()-1;
            }
        }
    }

    tActual=i;
}
