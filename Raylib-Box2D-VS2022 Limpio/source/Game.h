#pragma once

#include "raylib.h"
#include <box2d.h>

#include "PuenteGrua.h"
#include "Pelota.h"

class Game
{
    private:
            const int screenWidth = 1200;
            const int screenHeight = 700;

            b2World* m_world;

            b2Body* m_suelo;

            b2Body* m_plataformaInicio;
            b2Body* m_plataformaMeta;

            PuenteGrua* m_puenteGrua;
            Pelota* m_pelota;

            bool m_victoria;
            bool m_derrota;

            void InitPhysics();
            void Update();
            void Draw();
            void Reset();

            Texture2D texturaFondo;
            Texture2D texturaSuelo;
            Texture2D texturaPlataforma;
            Texture2D texturaBandera;

            Sound sonidoGrua;
            Sound sonidoVictoria;
            Sound sonidoDerrota;

    public:
            Game();
            ~Game();

            void Run();
};