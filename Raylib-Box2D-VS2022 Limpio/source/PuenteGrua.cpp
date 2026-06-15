#include "PuenteGrua.h"

PuenteGrua::PuenteGrua(b2World* world, float x, float y)
{
    //Texturas
    texturaPlataforma = LoadTexture("Assets/plataforma.png");
    texturaCarro = LoadTexture("Assets/carro.png");
    texturaRiel = LoadTexture("Assets/riel.png");

    m_world = world;

    //Riel

    b2BodyDef rielDef;
    rielDef.type = b2_staticBody;
    rielDef.position.Set(x, y);

    m_riel = m_world->CreateBody(&rielDef);

    b2PolygonShape rielShape;
    rielShape.SetAsBox(500.0f, 5.0f);

    m_riel->CreateFixture(&rielShape, 0.0f);

    //Carro

    b2BodyDef carroDef;
    carroDef.type = b2_dynamicBody;
    carroDef.position.Set(x, y);

    m_carro = m_world->CreateBody(&carroDef);

    b2PolygonShape carroShape;
    carroShape.SetAsBox(20.0f, 15.0f);

    b2FixtureDef carroFix;
    carroFix.shape = &carroShape;
    carroFix.density = 1.0f;

    m_carro->CreateFixture(&carroFix);

    //Joint Prismatic

    b2PrismaticJointDef prismDef;

    prismDef.Initialize(m_riel,m_carro,m_carro->GetPosition(),b2Vec2(1.0f, 0.0f));

    prismDef.enableLimit = true;
    prismDef.lowerTranslation = -500.0f;
    prismDef.upperTranslation = 500.0f;

    prismDef.enableMotor = true;
    prismDef.maxMotorForce = 100000.0f;
    prismDef.motorSpeed = 0.0f;

    m_jointHorizontal = (b2PrismaticJoint*)m_world->CreateJoint(&prismDef);

    //Plataforma

    b2BodyDef plataformaDef;
    plataformaDef.type = b2_dynamicBody;
    plataformaDef.position.Set(x,y + 180.0f);

    m_plataforma = m_world->CreateBody(&plataformaDef);

    b2PolygonShape plataformaShape;
    plataformaShape.SetAsBox(90.0f,10.0f);

    b2FixtureDef plataformaFix;
    plataformaFix.shape = &plataformaShape;
    plataformaFix.density = 0.8f;
    plataformaFix.friction = 1.0f;

    m_plataforma->CreateFixture(&plataformaFix);

    //Cable Izquierdo

    b2DistanceJointDef cableIzq;

    cableIzq.Initialize(m_carro,m_plataforma,m_carro->GetPosition(),b2Vec2(x - 40.0f,y + 180.0f));

    m_cableIzquierdo =(b2DistanceJoint*) m_world->CreateJoint( &cableIzq);

    //Cable Derecho

    b2DistanceJointDef cableDer;

    cableDer.Initialize(m_carro,m_plataforma, m_carro->GetPosition(),b2Vec2(x + 40.0f,y + 180.0f));

    m_cableDerecho = (b2DistanceJoint*) m_world->CreateJoint(&cableDer);
}

PuenteGrua::~PuenteGrua()
{
    UnloadTexture(texturaPlataforma);
    UnloadTexture(texturaCarro);
    UnloadTexture(texturaRiel);
}

void PuenteGrua::MoverIzquierda()
{
    m_jointHorizontal->SetMotorSpeed(-20.0f);
}

void PuenteGrua::MoverDerecha()
{
    m_jointHorizontal->SetMotorSpeed(20.0f);
}

void PuenteGrua::Detener()
{
    m_jointHorizontal->SetMotorSpeed(0.0f);
}

void PuenteGrua::Draw()
{
    //Riel

    DrawTexturePro(texturaRiel,
    {0,0,(float)texturaRiel.width,(float)texturaRiel.height},
    {m_riel->GetPosition().x - 700.0f,m_riel->GetPosition().y - 10.0f,1400.0f,20.0f},
    { 0,0 }, 0,WHITE);

    //Carro

    b2Vec2 carroPos = m_carro->GetPosition();

    DrawTexturePro(texturaCarro,
    {0,0,(float)texturaCarro.width,(float)texturaCarro.height},
    {carroPos.x - 30.0f, carroPos.y - 20.0f,60.0f,40.0f},
    { 0,0 },0, WHITE);

    //Plataforma

    b2Vec2 platPos = m_plataforma->GetPosition();

    float angulo = m_plataforma->GetAngle() * RAD2DEG;

    DrawTexturePro(texturaPlataforma,
    {0,0,(float)texturaPlataforma.width,(float)texturaPlataforma.height},
    {platPos.x,platPos.y,180.0f,20.0f},
    {90.0f,10.0f},angulo,WHITE);

    //Cables

    DrawLineV({ carroPos.x, carroPos.y },{ platPos.x - 40, platPos.y },GREEN);

    DrawLineV({ carroPos.x, carroPos.y },{ platPos.x + 40, platPos.y },GREEN);

    //Destacar Joints

    DrawCircleV({ carroPos.x, carroPos.y },8,RED);

    DrawCircleV({ platPos.x - 40, platPos.y },6,LIME);

    DrawCircleV({ platPos.x + 40, platPos.y },6,LIME);
}