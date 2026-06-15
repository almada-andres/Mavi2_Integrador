#pragma once

#include <box2d.h>
#include "raylib.h"

class PuenteGrua
{
    private:
            b2World* m_world;

            b2Body* m_riel;
            b2Body* m_carro;
            b2Body* m_plataforma;

            b2PrismaticJoint* m_jointHorizontal;

            b2DistanceJoint* m_cableIzquierdo;
            b2DistanceJoint* m_cableDerecho;

            Texture2D texturaPlataforma;
            Texture2D texturaCarro;
            Texture2D texturaRiel;

    public:
            PuenteGrua(b2World* world,float x,float y);

            ~PuenteGrua();

            void MoverIzquierda();
            void MoverDerecha();
            void Detener();

            void Draw();

            b2Body* GetPlataforma() const{return m_plataforma;}
};