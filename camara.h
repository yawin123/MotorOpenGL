#ifndef CAMARA_H
#define CAMARA_H

#include <vector>
#include "camara.h"
#include "pieza.h"
#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

class Camara
{
    public:
        Camara(const glm::vec3& pos, float fov, float aspect, float zNear, float zFar)
        {
            m_perspectiva=glm::perspective(fov,aspect,zNear,zFar);
            m_posicion=pos;
            m_delante=glm::vec3(0.0f,0.0f,1.0f);
            m_arriba=glm::vec3(0.0f,1.0f,0.0f);
        }

        inline glm::mat4 GetViewProjection() const
        {
            return m_perspectiva * glm::lookAt(m_posicion,m_posicion+m_delante,m_arriba);
        }

        inline void OrbitRight(float radio, float angle)
        {
            MoveForward(radio);
            RotateY(angle);
            MoveForward(-radio);
        }
        inline void MoveForward(float amt)
        {
            m_posicion += m_delante * amt;
        }
        inline void MoveRight(float amt)
        {
            m_posicion += glm::cross(m_arriba, m_delante) * amt;
        }

        inline void RotateY(float angle)
        {
            static const glm::vec3 arriba(0.0f, 1.0f, 0.0f);
            glm::mat4 rotation = glm::rotate(angle, arriba);

            m_delante = glm::vec3(glm::normalize(rotation * glm::vec4(m_delante, 0.0)));
            m_arriba = glm::vec3(glm::normalize(rotation * glm::vec4(m_arriba, 0.0)));
        }

        inline glm::vec3& getPos(){return m_posicion;}
    protected:
    private:
        glm::mat4 m_perspectiva;
        glm::vec3 m_posicion;
        glm::vec3 m_delante;
        glm::vec3 m_arriba;
};

#endif // CAMARA_H
