#include "shader.h"
#include <fstream>
#include <iostream>

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);
static std::string cargaShader(const std::string& fileName);
static GLuint creaShader(const std::string& text, GLenum shaderType);

Shader::Shader(const std::string& fileName)
{
    m_programa=glCreateProgram();
    m_shaders[0]=creaShader(cargaShader(fileName+".vs"),GL_VERTEX_SHADER); //Shader de vertices
    m_shaders[1]=creaShader(cargaShader(fileName+".fs"),GL_FRAGMENT_SHADER); //Shader de pixel

    for(unsigned int i=0;i<NUM_SHADER;i++)
    {
        glAttachShader(m_programa,m_shaders[i]);
        std::cout<<"Atacheado el shader "<<i<<std::endl;
    }

    glBindAttribLocation(m_programa,0,"position");
    glBindAttribLocation(m_programa,1,"texCoord");
    glBindAttribLocation(m_programa,2,"normal");

    std::cerr<<"Linkando el shader: ";
    glLinkProgram(m_programa);
    CheckShaderError(m_programa,GL_LINK_STATUS,true,"Error, el programa ha fallado al linkear el shader: ");

    std::cerr<<"Validando el shader: ";
    glValidateProgram(m_programa);
    CheckShaderError(m_programa,GL_VALIDATE_STATUS,true,"Error, el programa es inválido: ");

    m_uniforms[TRANSFORM_U]=glGetUniformLocation(m_programa,"transform");
}

Shader::~Shader()
{
    for(unsigned int i=0;i<NUM_SHADER;i++)
    {
        glDetachShader(m_programa,m_shaders[i]);
        glDeleteShader(m_shaders[i]);
    }

    glDeleteProgram(m_programa);
}

void Shader::Bind()
{
    glUseProgram(m_programa);
}

void Shader::Update(const Transform& transform, const Camara& camara)
{
    glm::mat4 model=camara.GetViewProjection() * transform.getModel();
    glUniformMatrix4fv(m_uniforms[TRANSFORM_U],1,GL_FALSE,&model[0][0]);
}

static std::string cargaShader(const std::string& fileName)
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
            salida.append(linea+"\n");
        }
    }
    else
    {
        std::cerr<<"Imposible cargar el shader: "<<fileName<<std::endl;
    }

    return salida;
}

static GLuint creaShader(const std::string& text, GLenum shaderType)
{
  GLuint shader=glCreateShader(shaderType);
  if(shader==0)
  {
    std::cerr<<"Error en la creación del shader. Info adicional: "<< shaderType <<std::endl;
    return 0 ; // Si falla esto no podemos seguir
  }

  const GLchar* shaderSourceStrings[1];
  shaderSourceStrings[0]=text.c_str();

  glShaderSource(shader,1,shaderSourceStrings,NULL);
  glCompileShader(shader);

  std::cerr<<"Comprobando errores en "<< shader <<": ";
  CheckShaderError(shader,GL_COMPILE_STATUS,false,"Error, ha fallado la compilacion del shader: ");

  return shader;
}

static void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
{
    GLint success=0;
    GLchar error[1024]={0};

    if(isProgram)
    {
        glGetProgramiv(shader,flag,&success);
    }
    else
    {
        glGetShaderiv(shader,flag,&success);
    }

    if(success==GL_FALSE)
    {
        if(isProgram)
        {
            glGetProgramInfoLog(shader,sizeof(error),NULL,error);
        }
        else
        {
            glGetShaderInfoLog(shader,sizeof(error),NULL,error);
        }

        std::cerr<<errorMessage<<": "<<error<<"'"<<std::endl;
    }
    else
    {
        std::cerr<<"Ok"<<std::endl;
    }
}
