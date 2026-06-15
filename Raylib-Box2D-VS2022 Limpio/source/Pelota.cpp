#include "Pelota.h"

Pelota::Pelota(b2World* world, float x, float y)
{
    texturaPelota = LoadTexture("Assets/pelota.png");

    m_world = world;
    m_radio = 18.0f;

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x, y);

    m_body = m_world->CreateBody(&bodyDef);

    b2CircleShape shape;
    shape.m_radius = m_radio;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.10f;
    fixtureDef.friction = 0.8f;
    fixtureDef.restitution = 0.1f;

    m_body->CreateFixture(&fixtureDef);
}

Pelota::~Pelota()
{
    UnloadTexture(texturaPelota);
}

void Pelota::MoverIzquierda()
{
    m_body->ApplyForceToCenter(b2Vec2(-30000.0f, 0.0f), true);
}

void Pelota::MoverDerecha()
{
    m_body->ApplyForceToCenter(b2Vec2(30000.0f, 0.0f), true);
}

void Pelota::Detener()
{
}

void Pelota::Draw()
{
    b2Vec2 pos = m_body->GetPosition();

    float angulo = m_body->GetAngle() * RAD2DEG;

    const float escalaVisual = 1.55f;

    float radioVisual = m_radio * escalaVisual;

    DrawTexturePro(texturaPelota,
    {0,0,(float)texturaPelota.width,(float)texturaPelota.height},
    {pos.x,pos.y,radioVisual * 2.0f,radioVisual * 2.0f},
    {radioVisual,radioVisual},angulo,WHITE);
}