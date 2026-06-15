#pragma once

#include <box2d.h>
#include "raylib.h"

class Pelota
{
    private:
            b2World* m_world;
            b2Body* m_body;

            float m_radio;

            Texture2D texturaPelota;

    public:
            Pelota(b2World* world, float x, float y);
            ~Pelota();

            void MoverIzquierda();
            void MoverDerecha();
            void Detener();

            void Draw();

            b2Body* GetBody() const { return m_body; }
};