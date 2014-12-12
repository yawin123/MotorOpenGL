#include <iostream>
#include "ventana.h"
#include "maya.h"
#include "pieza.h"
#include "camara.h"
#include "secuencia.h"
#include <vector>
#include <glm/glm.hpp>

#define WIDTH 1280
#define HEIGHT 720

int main()
{
    Ventana ventana(WIDTH,HEIGHT,"Saludaciones mundo pirulo");

    int contador=0;

    Secuencia cSec(WIDTH,HEIGHT);

    //Primera escena
        /*cSec.setCam(glm::vec3(0,0,-4),70.0f,(float)WIDTH/(float)HEIGHT,0.01f,1000.0f);
        cSec.addElemento("./res/modelos/monkey.obj","./res/shader/basicShader","./res/texturas/madera.jpg");
        cSec.setMovCam(0,4,0.75);
        cSec.setClearColor(123.0,98.0,51.0);
        cSec.Loop();
        cSec.Play();
        cSec.run(&ventana,1000);*/

    //Segunda escena
        cSec.setCam(glm::vec3(0,0,-4),70.0f,(float)WIDTH/(float)HEIGHT,0.01f,1000.0f);
        cSec.addElemento("./res/modelos/cubo.obj","./res/shader/basicShader","./res/texturas/madera.jpg",glm::vec3(1,1,3),glm::vec3(50,50,50),glm::vec3(1,1,1),"./res/anim/prueba.yawnim");

        /*cSec.addElemento("./res/modelos/monkey.obj","./res/shader/basicShader","./res/texturas/madera.jpg",glm::vec3(0,0,0),glm::vec3(0,0,0),glm::vec3(0,0,0),"./res/anim/escena1-cubo1.yawnim");
        cSec.addElemento("./res/modelos/monkey.obj","./res/shader/basicShader","./res/texturas/madera.jpg","./res/anim/escena1-cubo2.yawnim");
        cSec.addElemento("./res/modelos/monkey.obj","./res/shader/basicShader","./res/texturas/madera.jpg","./res/anim/escena1-cubo3.yawnim");
        cSec.setKeyFrame(2500,2,-1);
        cSec.setMovCam(0,4,-0.75);*/

        cSec.setClearColor(32,32,32);
        cSec.Loop();
        cSec.Play();
        cSec.run(&ventana,5000);

    return 0;
}
