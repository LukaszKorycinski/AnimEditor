#include "def.h"


class matrix
{
public:

glm::mat4 MatWorld;
glm::mat4 MatView;
glm::mat4 MatProj;


glm::mat4 mat_worldViewProj;

void init()
{
MatProj = glm::perspective(45.0f, float(szerokosc)/float(wysokosc), 0.1f, 90.0f);

glm::mat4 ViewTranslate; glm::translate(ViewTranslate,  glm::vec3(0.0f, 2.0f, -1.0f));
glm::mat4 ViewRotateX;   glm::rotate(ViewRotateX, 0.0f, glm::vec3(-1.0f, 0.0f, 0.0f));
glm::mat4 ViewRotateY;   glm::rotate(ViewRotateY, 0.0f, glm::vec3( 0.0f, 1.0f, 0.0f));
glm::mat4 View  = ViewTranslate * ViewRotateY * ViewRotateX;
glm::mat4 Model; glm::scale(Model, glm::vec3(0.5f));
MatView=View * Model;
}

};
matrix Matrix;













class cam
{
public:
Vector3f pos;
float Yrot;
float Xrot;
float speed;

cam()
{
speed=0.004f;
Xrot=0.0f;
Yrot=0.0f;
pos=Vector3f(0.0f, -1.0f, -3.0f);

}



void roTranScal()
{
glm::mat4 ModelTrans = glm::translate(glm::mat4(1.0f),        glm::vec3(pos.x, pos.y, pos.z) );
glm::mat4 rotYmodel  = glm::rotate   (glm::mat4(1.0f),  Yrot, glm::vec3(0.0f ,  1.0f, 0.0f ) );
glm::mat4 rotXmodel  = glm::rotate   (glm::mat4(1.0f),  Xrot, glm::vec3(1.0f ,  0.0f, 0.0f ) );

Matrix.MatWorld=rotXmodel*rotYmodel*ModelTrans;
}




void keyPress()
{
//if(keys[VK_SHIFT])
//speed=0.11f;
//else
//speed=0.01f;
//
//if(keys[VK_W])
//pos.y-=speed*Loop.lOOp;
//if(keys[VK_S] && !keys[VK_CONTROL])
//pos.y+=speed*Loop.lOOp;
//
//if(keys[VK_D]==TRUE)
//pos.x-=speed*Loop.lOOp;
//if(keys[VK_A]==TRUE)
//pos.x+=speed*Loop.lOOp;
//
if(keys[VK_Q]==TRUE)
pos.z+=speed*Loop.lOOp;
if(keys[VK_E]==TRUE)
pos.z-=speed*Loop.lOOp;

}

Vector3f GetCameraPosition()
{
return pos;
}

};
cam Cam;
