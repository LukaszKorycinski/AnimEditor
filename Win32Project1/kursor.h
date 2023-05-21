#include "font.h"


class cursor
{
public:

Vector3f oldPos;
Vector3f pos;
Vector3f oldpoint;


void logic();


void Draw()
{
POINT m;
GetCursorPos(&m); 
float xKurs = static_cast<float>(m.x);
float yKurs = static_cast<float>(m.y);

pos.x=(xKurs-408)*0.00943901f;
pos.y=(-yKurs+380)*0.00943901f;



cgGLBindProgram(VP);
cgGLBindProgram(FP);

glm::mat4 mat_worldViewProj = Matrix.MatProj * Matrix.MatView * Matrix.MatWorld;

glm::mat4 mat_trans = glm::translate( glm::mat4(1.0f), glm::vec3(pos.x,  pos.y, 0.0f) );
glm::mat4 mat_tmp = mat_worldViewProj * mat_trans;

cgGLSetMatrixParameterfr(  cgGetNamedParameter(VP,"ModelViewProj"), glm::value_ptr(mat_tmp)  );

glAlphaFunc(GL_GREATER,0.5f);
glEnable(GL_ALPHA_TEST);

point3df.DrawModel(tex[4]);
}

};

cursor Cursor;

