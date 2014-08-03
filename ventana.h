#ifndef VENTANA_H
#define VENTANA_H

#include <SDL2/SDL.h>
#include <string>

class Ventana
{
    public:
        Ventana(int width, int height, const std::string& title);

        void Clear(float r, float g, float b, float a);
        void Update();
        bool IsClosed();

        virtual ~Ventana();
    protected:
    private:
        Ventana(const Ventana& other);
        void operator=(const Ventana& other);

        SDL_Window* m_ventana;
        SDL_GLContext m_glContexto;
        bool m_isClosed;
};

#endif // VENTANA_H
