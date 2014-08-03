#include <iostream>
#include "ventana.h"
#include "maya.h"
#include "pieza.h"
#include "camara.h"
#include "secuencia.h"

#define WIDTH 1280
#define HEIGHT 720

int main()
{
    Ventana ventana(WIDTH,HEIGHT,"Saludaciones mundo pirulo");


    unsigned int contador=0;

    Secuencia cSec(WIDTH,HEIGHT);
    cSec.setCam(glm::vec3(0,0,-4),70.0f,(float)WIDTH/(float)HEIGHT,0.01f,1000.0f);
    cSec.addElemento("./res/modelos/cubo.obj","./res/shader/basicShader","./res/texturas/bricks.jpg","./res/anim/cubo.yawnim");
    cSec.addElemento("./res/modelos/cubo.obj","./res/shader/basicShader","./res/texturas/grass.jpg","./res/anim/cubo2.yawnim");

    while(!ventana.IsClosed())
    {
        ventana.Clear(0.0,0.2,0.5,1.0);
        //principal.OrbitRight(4,0.75);

        ventana.Update();

        contador++;
    }
    return 0;
}
