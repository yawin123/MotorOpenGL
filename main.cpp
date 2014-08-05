#include <iostream>
#include "ventana.h"
#include "maya.h"
#include "pieza.h"
#include "camara.h"
#include "secuencia.h"
#include <vector>

#define WIDTH 1280
#define HEIGHT 720

int main()
{
    Ventana ventana(WIDTH,HEIGHT,"Saludaciones mundo pirulo");


    int contador=0;

    Secuencia cSec(WIDTH,HEIGHT);
    cSec.setCam(glm::vec3(0,0,-4),70.0f,(float)WIDTH/(float)HEIGHT,0.01f,1000.0f);
    cSec.addElemento("./res/modelos/cubo.obj","./res/shader/basicShader","./res/texturas/bricks.jpg","./res/anim/triangulo.yawnim");
    cSec.addElemento("./res/modelos/cubo.obj","./res/shader/basicShader","./res/texturas/madera.jpg","./res/anim/triangulo2.yawnim");
    cSec.addElemento("./res/modelos/untitled.obj","./res/shader/basicShader","./res/texturas/grass.jpg");
    cSec.Loop();
    cSec.Play();



    //Una cosita de debug
        /*std::vector<Pieza*> p;
        for(int i=-5;i<5;i++)
        {
            for(int j=-5;j<5;j++)
            {
                for(int z=-5;z<5;z++)
                {
                    Pieza* p2=new Pieza("./res/modelos/cubo.obj","./res/shader/basicShader","./res/texturas/bricks.jpg");
                    p.push_back(p2);
                    p[p.size()-1]->getPos()=glm::vec3(i,j,z);
                    p[p.size()-1]->getScale()=glm::vec3(0.01,0.01,0.01);
                }
            }
        }
        for(unsigned int e=0;e<p.size();e++)
        {
            p[e]->Update(*cSec.getCam());
        }*/
    ///////////////////////////////////////
    while(!ventana.IsClosed())
    {
        //if(contador%25==0){cSec.Frame(contador); std::cout<<contador<<std::endl;}

        ventana.Clear(0.0,0.2,0.5,1.0);


        cSec.Update();
        cSec.getCam()->OrbitRight(4,0.75);

        ventana.Update();

        contador++;
    }
    return 0;
}
