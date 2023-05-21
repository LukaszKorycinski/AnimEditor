#include "3df.h"


b2Vec2 gravity(0.0f, -10.0f);
b2World Box2world(gravity);

class fizyka
{
public:
DWORD old, curr;

void init()
{
curr=old=0;
}


void update()
{
//curr=timeGetTime();//0.001 sekundy
//if(old+4<curr)
//{
float32 timeStep=0.0005f*Loop.lOOp;

//timeStep = 0.00001f*float(curr-old);//0.0023f

old=curr;

int32 velocityIterations = 6;
int32 positionIterations = 2;

Box2world.Step(timeStep, velocityIterations, positionIterations);
//}
}

void logic()
{
//float32 timeStep = 1.0f / 120.0f;
//int32 velocityIterations = 6;
//int32 positionIterations = 2;
//
//timeStep=Loop.lOOp*0.0008f;
////if(Loop.lOOp>20.0f/120.0f)
////{
////Box2world.Step(timeStep/3.0f, velocityIterations, positionIterations);//0.003f
////Box2world.Step(timeStep/3.0f, velocityIterations, positionIterations);//0.003f
////Box2world.Step(timeStep/3.0f, velocityIterations, positionIterations);//0.003f
////}
////else
//Box2world.Step(timeStep, velocityIterations, positionIterations);//0.003f
}

};
fizyka Fizyka;