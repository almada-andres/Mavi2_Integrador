#include "Game.h"

Game::Game()
{
    InitWindow(screenWidth,screenHeight,"Trabajo Integrador");

    SetTargetFPS(60);

    //Sprites
    texturaFondo = LoadTexture("Assets/fondo.png");
    texturaSuelo = LoadTexture("Assets/suelo.png");
    texturaPlataforma = LoadTexture("Assets/plataforma.png");
    texturaBandera = LoadTexture("Assets/bandera.png");

    //Sonidos
    InitAudioDevice();

    sonidoGrua = LoadSound("Assets/grua.wav");
    sonidoVictoria = LoadSound("Assets/victoria.wav");
    sonidoDerrota = LoadSound("Assets/derrota.wav");

    b2Vec2 gravity(0.0f, 250.0f);

    m_world = new b2World(gravity);

    m_victoria = false;
    m_derrota = false;

    InitPhysics();
}

Game::~Game()
{
    delete m_puenteGrua;
    delete m_pelota;
    delete m_world;

    UnloadTexture(texturaFondo);
    UnloadTexture(texturaSuelo);
    UnloadTexture(texturaPlataforma);
    UnloadTexture(texturaBandera);
    UnloadSound(sonidoGrua);
    UnloadSound(sonidoVictoria);
    UnloadSound(sonidoDerrota);

    CloseAudioDevice();

    CloseWindow();
}

void Game::InitPhysics()
{
    // Suelo
    b2BodyDef sueloDef;
    sueloDef.type = b2_staticBody;
    sueloDef.position.Set(screenWidth / 2.0f, screenHeight - 20.0f);

    m_suelo = m_world->CreateBody(&sueloDef);

    b2PolygonShape sueloShape;
    sueloShape.SetAsBox(screenWidth / 2.0f, 20.0f);

    m_suelo->CreateFixture(&sueloShape, 0.0f);

    //Plataforma Inicio

    b2BodyDef inicioDef;
    inicioDef.type = b2_staticBody;
    inicioDef.position.Set(120.0f, screenHeight - 400.0f);

    m_plataformaInicio = m_world->CreateBody(&inicioDef);

    b2PolygonShape inicioShape;
    inicioShape.SetAsBox(100.0f, 10.0f);

    m_plataformaInicio->CreateFixture(&inicioShape, 0.0f);

    //Plataforma Meta

    b2BodyDef metaDef;
    metaDef.type = b2_staticBody;
    metaDef.position.Set(1050.0f, screenHeight - 400.0f);

    m_plataformaMeta = m_world->CreateBody(&metaDef);

    b2PolygonShape metaShape;
    metaShape.SetAsBox(100.0f, 10.0f);

    m_plataformaMeta->CreateFixture(&metaShape,0.0f);

    //Puente Grua

    m_puenteGrua = new PuenteGrua(m_world, 600.0f, 120.0f);

    //Pelota

    m_pelota = new Pelota(m_world, 120.0f, screenHeight - 450.0f);
}

void Game::Update()
{
    if (!m_victoria && !m_derrota)
    {
        //Controles Pelota

        if (IsKeyDown(KEY_A))
        {
            m_pelota->MoverIzquierda();
        }

        if (IsKeyDown(KEY_D))
        {
            m_pelota->MoverDerecha();
        }

        //Controles Grua

        if (IsKeyDown(KEY_LEFT))
        {
            m_puenteGrua->MoverIzquierda();

            if (!IsSoundPlaying(sonidoGrua))
            {
                PlaySound(sonidoGrua);
            }
        }
        else if (IsKeyDown(KEY_RIGHT))
        {
            m_puenteGrua->MoverDerecha();

            if (!IsSoundPlaying(sonidoGrua))
            {
                PlaySound(sonidoGrua);
            }
        }
        else
        {
            m_puenteGrua->Detener();
            StopSound(sonidoGrua);
        }
    }

    //Derrota

    if (!m_derrota && m_pelota->GetBody()->GetPosition().y > screenHeight - 70)
    {
        m_derrota = true;
        PlaySound(sonidoDerrota);
    }

    //Victoria

    b2Vec2 pelotaPos = m_pelota->GetBody()->GetPosition();

    b2Vec2 metaPos = m_plataformaMeta->GetPosition();

    if (!m_victoria && fabs(pelotaPos.x - metaPos.x) < 20 && fabs(pelotaPos.y - metaPos.y) < 30)
    {
        m_victoria = true;
        PlaySound(sonidoVictoria);
        m_pelota->GetBody()->SetType(b2_staticBody);
    }

    //Reinicio

    if (IsKeyPressed(KEY_R))
    {
        StopSound(sonidoGrua);
        StopSound(sonidoVictoria);
        StopSound(sonidoDerrota);

        Reset();
        return;
    }

    // STEP

    m_world->Step(1.0f / 60.0f,8,3);

}

void Game::Draw()
{
    BeginDrawing();

    //Fondo
    ClearBackground(BLACK);

    DrawTexturePro(texturaFondo,
    { 0, 0, (float)texturaFondo.width,(float)texturaFondo.height},
    { 0, 0, (float)screenWidth, (float)screenHeight},
    { 0,0 },0,WHITE);

    //Suelo
    DrawTexturePro(texturaSuelo,
    { 0, 0,(float)texturaSuelo.width, (float)texturaSuelo.height},
    { 0, (float)(screenHeight - 40), (float)screenWidth, 40},
    { 0,0 },0,WHITE);

    //Plataforma Inicio

    b2Vec2 inicioPos = m_plataformaInicio->GetPosition();

    DrawTexturePro(texturaPlataforma,
    { 0, 0, (float)texturaPlataforma.width, (float)texturaPlataforma.height},
    { inicioPos.x - 100, inicioPos.y - 10, 200, 20},
    { 0,0 }, 0, WHITE);

    //Meta

    b2Vec2 metaPos = m_plataformaMeta->GetPosition();

    DrawTexturePro(texturaPlataforma,
    { 0,0,(float)texturaPlataforma.width, (float)texturaPlataforma.height},
    { metaPos.x - 100, metaPos.y - 10, 200,20},
    { 0,0 }, 0, WHITE);

    //Bandera

    DrawTexturePro(texturaBandera,
    {0,0,(float)texturaBandera.width,(float)texturaBandera.height},
    {metaPos.x - 25, metaPos.y - 80, 50, 70},
    { 0,0 },0, WHITE);

    //Objetos

    m_puenteGrua->Draw();
    m_pelota->Draw();

    //UI

    DrawText("A/D = Mover pelota",20,20,20,BLACK);
    DrawText("Flechas = Mover grua",20,50,20,BLACK);
    DrawText("Objetivo: llevar la pelota hasta el caliz de fuego    -   R para reiniciar",20,80,20,BLACK);

    if (m_derrota)
    {
        DrawText("DERROTA",500,300,50,RED);
    }

    if (m_victoria)
    {
        DrawText("VICTORIA",500, 250, 50, GREEN);
    }

    EndDrawing();
}

void Game::Run()
{
    while (!WindowShouldClose())
    {
        Update();
        Draw();
    }
}

void Game::Reset()
{
    delete m_puenteGrua;
    delete m_pelota;
    delete m_world;

    b2Vec2 gravity(0.0f, 250.0f);

    m_world = new b2World(gravity);

    m_victoria = false;
    m_derrota = false;

    InitPhysics();
}