#include "kursor.h"




#define ILE_BONE 8
#define ILE_ANIM 50

class bones
{
public:
int actual_klatka;
int ile,ileanim;
Vector3f Trans[ILE_BONE];
Vector3f Rot[ILE_BONE];

Vector3f TransCopyBufor[ILE_BONE];
Vector3f RotCopyBufor[ILE_BONE];

Vector3f TransAnim[ILE_BONE][ILE_ANIM];
Vector3f RotAnim[ILE_BONE][ILE_ANIM];
//quaterion4f QuatAnim[ILE_BONE][ILE_ANIM];

Vector3f aktualtranslat[ILE_BONE];

//glm::mat4 bonemMatrix[ILE_BONE];

//glm::mat4 boneAnimMatrix[ILE_BONE][ILE_ANIM];
//float boneAnimMatrixfloat[ILE_ANIM][16*6];

int selected[ILE_BONE];//0-unselected 1-selected

bones()
{
actual_klatka=0;
ileanim=0;
ile=0;
}

void edit()
{
if(right_key==1 && tryb==2)
{
actual_klatka++;
if(ileanim<actual_klatka)
	ileanim=actual_klatka;
}
if(left_key==1 && tryb==2)
actual_klatka--;


if(z_key==1 && tryb==2 && actual_klatka==ileanim)//deletowanie klatki
	{
	actual_klatka--;
	ileanim--;
	}

if(keys[VK_X] && tryb==2)//reset klatki
	for(int i=0;i<ILE_BONE;i++)
	{
		TransAnim[i][actual_klatka]=Vector3f(0.0f);
		RotAnim[i][actual_klatka]=Vector3f(0.0f);//quaterion4f();
	}

if(keys[VK_T] && tryb==1)
	for(int i=0;i<ile;i++)
		if(selected[i]==1)
		{
			if(t_key==1)
				Cursor.oldPos=Cursor.pos;
			Trans[i]=Cursor.pos-Cursor.oldPos;
		}
if(keys[VK_R] && tryb==1)
	for(int i=0;i<ile;i++)
		if(selected[i]==1)
			Rot[i].z=Cursor.pos.x*50.0f;

if(keys[VK_T] && tryb==2)
	for(int i=0;i<ile;i++)
		if(selected[i]==1)
		{
			if(t_key==1)
			{
				Cursor.oldPos=Cursor.pos;
				aktualtranslat[i]=TransAnim[i][actual_klatka];
			}
			TransAnim[i][actual_klatka]=aktualtranslat[i]+Cursor.pos-Cursor.oldPos;
		}
if(keys[VK_R] && tryb==2)
	for(int i=0;i<ile;i++)
		if(selected[i]==1)
			RotAnim[i][actual_klatka].z=Cursor.pos.x*50.0f;

if(keys[VK_C] && keys[VK_CONTROL])
for(int i=0;i<ile;i++)
{
TransCopyBufor[i]=TransAnim[i][actual_klatka];
RotCopyBufor[i]=RotAnim[i][actual_klatka];
}

if(keys[VK_V] && keys[VK_CONTROL])
for(int i=0;i<ile;i++)
{
TransAnim[i][actual_klatka]=TransCopyBufor[i];
RotAnim[i][actual_klatka]=RotCopyBufor[i];
}

}

void add()
{
if(space_key==1 && tryb==1)
{
for(int i=0;i<ile;i++)
	selected[i]=0;
selected[ile]=1;
Trans[ile]=Cursor.pos;
ile++;
}
}


void select()
{
if(tryb==1 && keys[VK_B])
	{
	int closer=0;
	for(int i=0;i<ile;i++)
		if(Geom.distanc2D(Cursor.pos,Trans[i])<Geom.distanc2D(Cursor.pos,Trans[closer]))
			closer=i;
	if(r_mouse_button==1)
		selected[closer]=0;//unselected
	if(l_mouse_button==1)
		selected[closer]=1;
	}

if(tryb==2)
	{
	int closer=0;
	for(int i=0;i<ile;i++)
		if(Geom.distanc2D(Cursor.pos,Trans[i])<Geom.distanc2D(Cursor.pos,Trans[closer]))
			closer=i;
	if(r_mouse_button==1)
		selected[closer]=0;//unselected
	if(l_mouse_button==1)
		selected[closer]=1;
	}
}







void Draw()
{
select();
edit();

cgGLBindProgram(VP);
cgGLBindProgram(FP);

glm::mat4 mat_worldViewProj = Matrix.MatProj * Matrix.MatView * Matrix.MatWorld;




for(int i=0;i<ile;i++)
{
glm::mat4 mat_rot = glm::rotate( glm::mat4(1.0f), Rot[i].z, glm::vec3(0.0f,  0.0f, 1.0f) );
glm::mat4 mat_trans = glm::translate( glm::mat4(1.0f), glm::vec3(Trans[i].x,  Trans[i].y, 0.0f) );
//glm::mat4 mat_transminus = glm::translate( glm::mat4(1.0f), glm::vec3(-Trans[i].x,  -Trans[i].y, 0.0f) );

//glm::mat4 mat_tmp = mat_worldViewProj * mat_trans * mat_rot;

//bonemMatrix[i] = mat_trans * mat_rot;

glm::mat4 mat_rot2 = glm::rotate( glm::mat4(1.0f), RotAnim[i][actual_klatka].z, glm::vec3(0.0f,  0.0f, 1.0f) );
glm::mat4 mat_trans2 = glm::translate( glm::mat4(1.0f), glm::vec3(TransAnim[i][actual_klatka].x,  TransAnim[i][actual_klatka].y, 0.0f) );
glm::mat4 mat_scale = glm::scale( glm::mat4(1.0f), glm::vec3(0.3f,  0.3f, 0.3f) );

//QuatAnim[i][actual_klatka].QuaternionRotationZ(RotAnim[i][actual_klatka].z);

//mat_tmp =  mat_tmp * mat_trans2 * mat_rot2;//z modelvier

glm::mat4 mat_tmp = mat_worldViewProj * mat_trans * mat_trans2 * mat_rot * mat_rot2 * mat_scale ;


cgGLSetMatrixParameterfr(  cgGetNamedParameter(VP,"ModelViewProj"), glm::value_ptr(mat_tmp)  );





glAlphaFunc(GL_GREATER,0.5f);
glEnable(GL_ALPHA_TEST);

if(selected[i]==1)
bone3df.DrawModel(tex[2]);
if(selected[i]==0)//unselected
bone3df.DrawModel(tex[3]);
}

}



};

bones Bones;