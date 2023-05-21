#include "tex.h"


class Face3df
{
public:
Vector2f TexCoord3df;
Vector3f Normal3df;
Vector3f Vertex3df;
};

class Face2dvtf
{
public:
Vector2f TexCoord3df;
Vector3f Vertex3df;
};

class Face2df
{
public:
Vector3f Normal3df;
Vector3f Vertex3df;
};

class Face1df
{
public:
Vector2f TexCoord3df;
};

class Obiekt3df
{
public:
int NumberFace;
GLuint Tex;
GLuint Alpha;
Vector3f* TexCoord3df;
Vector3f* Normal3df;
Vector3f* Vertex3df;

unsigned int VBOvName;
unsigned int VBOtName;
unsigned int VBOnName;

bool init3dfModel(LPSTR strName, GLuint tex)
{
delete[] TexCoord3df;
delete[] Normal3df;
delete[] Vertex3df;

Tex = tex;
	ifstream load(strName);
	if(!load)
		return 1;
	else
	{
		load >> NumberFace;

TexCoord3df = new Vector3f[NumberFace];
Normal3df   = new Vector3f[NumberFace];
Vertex3df   = new Vector3f[NumberFace];


		for(int i=0; i<NumberFace; i++)
		{
		load >> TexCoord3df[i].x >> TexCoord3df[i].y;          TexCoord3df[i].z=0;
		load >> Normal3df[i].x   >> Normal3df[i].y   >> Normal3df[i].z;
		load >> Vertex3df[i].x   >> Vertex3df[i].y   >> Vertex3df[i].z;
		}
		load.close();


		return 0;
	}
}


void DrawModel(int Texture)
{
glTexCoordPointer( 3, GL_FLOAT, 0,  TexCoord3df); // Set The Vertex Pointer To Our TexCoord Data
glNormalPointer( GL_FLOAT, 0,  Normal3df); // Set The Vertex Pointer To Our TexCoord Data
glVertexPointer( 3, GL_FLOAT, 0,  Vertex3df); // Set The Vertex Pointer To Our Vertex Data

glBindTexture(GL_TEXTURE_2D, Texture);

glDrawArrays( GL_TRIANGLES, 0, NumberFace );
}


};


Obiekt3df f3df,bone3df,point3df;


void init3df()   //.a3df
{
if(f3df.init3dfModel("model/f.a3df", tex[1])==TRUE)
MessageBoxA(NULL, "model/f.a3df", "B³¹d", MB_OK);

if(bone3df.init3dfModel("model/bone.3df", tex[2])==TRUE)
MessageBoxA(NULL, "model/bone.3df", "B³¹d", MB_OK);

if(point3df.init3dfModel("model/point.3df", tex[2])==TRUE)
MessageBoxA(NULL, "model/point.3df", "B³¹d", MB_OK);
}















