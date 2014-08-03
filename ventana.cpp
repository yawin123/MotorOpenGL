#include "ventana.h"
#include <GL/glew.h>
#include <iostream>

Ventana::Ventana(int width, int height, const std::string& title)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE,8);     //Ponemos el atributo de "Rojo" a 8 bits;
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,8);   //Ponemos el atributo de "Verde" a 8 bits;
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,8);    //Ponemos el atributo de "Azul" a 8 bits;
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,8);   //Ponemos el atributo de "Alfa" a 8 bits;
    SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,32); //Ponemos el atributo de "Tamaño de buffer" a 32 bits;
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,16);  //Ponemos el atributo de "Profundidad de buffer" a 16;
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,1); //Ponemos el atributo de "Doble buffer" a true;

    m_ventana=SDL_CreateWindow(title.c_str(),SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,width,height,SDL_WINDOW_OPENGL);  //Creamos la ventana;
    m_glContexto=SDL_GL_CreateContext(m_ventana); //Añadimos un contexto (¿lienzo?) a la ventana;

    /* Ni idea, preguntar a alguien */
        GLenum status=glewInit();
        if(status!=GLEW_OK)
        {
            std::cerr<<"Glew ha fallado al inicializarse"<<std::endl;
        }
        m_isClosed=false;
    /*------------------------------*/

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

Ventana::~Ventana()
{
    SDL_GL_DeleteContext(m_glContexto);  //Borramos el contexto (¿lienzo?);
    SDL_DestroyWindow(m_ventana);        //Destruímos la ventana;
    SDL_Quit();                         //Paramos SDL;
}

void Ventana::Clear(float r, float g, float b, float a)
{
    glClearColor(r,g,b,a);          //Ponemos la ventana con el color inidicado en los parámetros;
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);   //Ni idea;
}

bool Ventana::IsClosed()
{
    return m_isClosed;
}

void Ventana::Update()
{
    SDL_GL_SwapWindow(m_ventana);    //¿Activa el cambio de buffer?;
    SDL_Event e;                    //Creamos un evento;

    /* Ni idea ----------------------*/
        while(SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT)
            {
                m_isClosed=true;
            }
        }
    /*------------------------------*/
}
