#include "bone.h"


class editedmodel
{
public:
int* Vertexes;//0-unselected 1-selected
int* boneindices;//index kosci
float wave;

void init()
{
wave=0.0f;
Vertexes  = new int[f3df.NumberFace];
boneindices  = new int[f3df.NumberFace];
for(int i=0;i<f3df.NumberFace;i++)
{
	Vertexes[i]=0;
	boneindices[i]=-1;
}
}


void control()
{
if(keys[VK_A] && tryb==1)
	{
	for(int i=0;i<f3df.NumberFace;i++)
	if(Vertexes[i]==1)//jeœli zaznaczony
		{
			for(int j=0;j<Bones.ile;j++)
				if(Bones.selected[j]==1)//jeœ³i koœæ te¿ zaznaczona, to ³¹czy koœæ z zaznaczonymi wierzcholkami
					{
					boneindices[i]=j;
					f3df.TexCoord3df[i].z=j;
					}
		}
	}

if(keys[VK_Z] && tryb==1)
	{
	for(int i=0;i<f3df.NumberFace;i++)
		{
			int out = 0 ;
			for(int j=0;j<Bones.ile;j++)
				if(Bones.selected[j]==1)
					{
					if(boneindices[i]==j && f3df.TexCoord3df[i].z==j)
						{
						 out=1;
						}
					}
			Vertexes[i] = out;
		}
	}

}


void DrawPunkty()
{


cgGLBindProgram(VP);
cgGLBindProgram(FP);

glm::mat4 mat_worldViewProj = Matrix.MatProj * Matrix.MatView * Matrix.MatWorld;


for(int i=0;i<f3df.NumberFace;i++)
if(tryb==1)
{
glm::mat4 mat_trans = glm::translate( glm::mat4(1.0f), glm::vec3(f3df.Vertex3df[i].x,  f3df.Vertex3df[i].y, f3df.Vertex3df[i].z) );
glm::mat4 mat_tmp = mat_worldViewProj * mat_trans;

cgGLSetMatrixParameterfr(  cgGetNamedParameter(VP,"ModelViewProj"), glm::value_ptr(mat_tmp)  );

glAlphaFunc(GL_GREATER,0.5f);
glEnable(GL_ALPHA_TEST);

if(Vertexes[i]==0)
point3df.DrawModel(tex[3]);
if(Vertexes[i]==1)
point3df.DrawModel(tex[2]);
}
}













void DrawModeloAnim()
{
cgGLBindProgram(VPbone);
cgGLBindProgram(FPbone);

cgGLSetParameter1f(cgGetNamedParameter(FPbone,"colo"),0.0f);

glm::mat4 mat_worldViewProj = Matrix.MatProj * Matrix.MatView * Matrix.MatWorld;

glm::mat4 mat_tmp = mat_worldViewProj;

cgGLSetMatrixParameterfr(  cgGetNamedParameter(VPbone,"ModelViewProj"), glm::value_ptr(mat_tmp)  );



glm::mat4 matbone_tmp[ILE_BONE];
float tmpboneMatrix[16*ILE_BONE];// ILE_BONE macierzy koœci

wave+=0.001f*Loop.lOOp;
if(wave>Bones.ileanim)
	wave=0.0f;

for(int i=0;i<ILE_BONE;i++)
{
float rotation2 = Geom.interpolate(Bones.RotAnim[i][int(wave)].z, Bones.RotAnim[i][int(wave)+1].z, wave-int(wave) );
Vector3f translation2 =  Geom.interpolate(Bones.TransAnim[i][int(wave)], Bones.TransAnim[i][int(wave)+1], wave-int(wave));

//glm::mat4 mat_rot1tmp = glm::rotate( glm::mat4(1.0f), Bones.Rot[i].z, glm::vec3(0.0f,  0.0f, 1.0f) );
glm::mat4 mat_trans1tmp = glm::translate( glm::mat4(1.0f), glm::vec3( Bones.Trans[i].x,   Bones.Trans[i].y, 0.0f) );
glm::mat4 mat_rot2tmp = glm::rotate( glm::mat4(1.0f), rotation2, glm::vec3(0.0f,  0.0f, 1.0f) );
glm::mat4 mat_trans2tmp = glm::translate( glm::mat4(1.0f), glm::vec3( translation2.x,   translation2.y, 0.0f) );

//matbone_tmp[i] = mat_rot2tmp * mat_trans2tmp ;
matbone_tmp[i] = mat_trans1tmp * mat_trans2tmp * mat_rot2tmp * glm::inverse(mat_trans1tmp);
//matbone_tmp[i] = matbone_tmp[i] * mat_translatTmp * mat_rotateTmp * glm::inverse( matbone_tmp[i]);

glm::vec4 t0 = matbone_tmp[i][0];
glm::vec4 t1 = matbone_tmp[i][1];
glm::vec4 t2 = matbone_tmp[i][2];
glm::vec4 t3 = matbone_tmp[i][3];
int j=0;
tmpboneMatrix[16*i+j]=t0[0];j++;
tmpboneMatrix[16*i+j]=t0[1];j++;
tmpboneMatrix[16*i+j]=t0[2];j++;
tmpboneMatrix[16*i+j]=t0[3];j++;

tmpboneMatrix[16*i+j]=t1[0];j++;
tmpboneMatrix[16*i+j]=t1[1];j++;
tmpboneMatrix[16*i+j]=t1[2];j++;
tmpboneMatrix[16*i+j]=t1[3];j++;

tmpboneMatrix[16*i+j]=t2[0];j++;
tmpboneMatrix[16*i+j]=t2[1];j++;
tmpboneMatrix[16*i+j]=t2[2];j++;
tmpboneMatrix[16*i+j]=t2[3];j++;

tmpboneMatrix[16*i+j]=t3[0];j++;
tmpboneMatrix[16*i+j]=t3[1];j++;
tmpboneMatrix[16*i+j]=t3[2];j++;
tmpboneMatrix[16*i+j]=t3[3];j++;
}


cgGLSetParameterArray4f( cgGetNamedParameter(VPbone, "boneMatrix"), 0, 4*ILE_BONE,  tmpboneMatrix);


glAlphaFunc(GL_GREATER,0.5f);
glEnable(GL_ALPHA_TEST);

f3df.DrawModel(tex[1]);
}









void DrawModelo()
{
if(tryb==1){
glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
}
control();

cgGLBindProgram(VPbone);
cgGLBindProgram(FPbone);

cgGLSetParameter1f(cgGetNamedParameter(FPbone,"colo"),0.0f);

int texture = tex[1]; 
if(tryb==1){
	cgGLSetParameter1f(cgGetNamedParameter(FPbone,"colo"),1.0f);
	texture = tex[6];

}

glm::mat4 mat_worldViewProj = Matrix.MatProj * Matrix.MatView * Matrix.MatWorld;

glm::mat4 mat_tmp = mat_worldViewProj;

cgGLSetMatrixParameterfr(  cgGetNamedParameter(VPbone,"ModelViewProj"), glm::value_ptr(mat_tmp)  );


glm::mat4 matbone_tmp[ILE_BONE];
float tmpboneMatrix[16*ILE_BONE];// ILE_BONE macierzy koœci

for(int i=0;i<ILE_BONE;i++)
{
//glm::mat4 mat_rot1tmp = glm::rotate( glm::mat4(1.0f), Bones.Rot[i].z, glm::vec3(0.0f,  0.0f, 1.0f) );
glm::mat4 mat_trans1tmp = glm::translate( glm::mat4(1.0f), glm::vec3( Bones.Trans[i].x,   Bones.Trans[i].y, 0.0f) );
glm::mat4 mat_rot2tmp = glm::rotate( glm::mat4(1.0f), Bones.RotAnim[i][Bones.actual_klatka].z, glm::vec3(0.0f,  0.0f, 1.0f) );
glm::mat4 mat_trans2tmp = glm::translate( glm::mat4(1.0f), glm::vec3( Bones.TransAnim[i][ Bones.actual_klatka].x,   Bones.TransAnim[i][ Bones.actual_klatka].y, 0.0f) );


matbone_tmp[i] = mat_trans1tmp * mat_trans2tmp * mat_rot2tmp * glm::inverse(mat_trans1tmp);

glm::vec4 t0 = matbone_tmp[i][0];
glm::vec4 t1 = matbone_tmp[i][1];
glm::vec4 t2 = matbone_tmp[i][2];
glm::vec4 t3 = matbone_tmp[i][3];
int j=0;
tmpboneMatrix[16*i+j]=t0[0];j++;
tmpboneMatrix[16*i+j]=t0[1];j++;
tmpboneMatrix[16*i+j]=t0[2];j++;
tmpboneMatrix[16*i+j]=t0[3];j++;

tmpboneMatrix[16*i+j]=t1[0];j++;
tmpboneMatrix[16*i+j]=t1[1];j++;
tmpboneMatrix[16*i+j]=t1[2];j++;
tmpboneMatrix[16*i+j]=t1[3];j++;

tmpboneMatrix[16*i+j]=t2[0];j++;
tmpboneMatrix[16*i+j]=t2[1];j++;
tmpboneMatrix[16*i+j]=t2[2];j++;
tmpboneMatrix[16*i+j]=t2[3];j++;

tmpboneMatrix[16*i+j]=t3[0];j++;
tmpboneMatrix[16*i+j]=t3[1];j++;
tmpboneMatrix[16*i+j]=t3[2];j++;
tmpboneMatrix[16*i+j]=t3[3];j++;
}






cgGLSetParameterArray4f( cgGetNamedParameter(VPbone, "boneMatrix"), 0, 4*ILE_BONE,  tmpboneMatrix);


glAlphaFunc(GL_GREATER,0.5f);
glEnable(GL_ALPHA_TEST);

f3df.DrawModel(texture);

glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
}

};
editedmodel Editedmodel;













void cursor::logic()
{


if(keys[VK_V] && tryb == 1)//wciœniête V to zaznaczanie/odznaczanie wierzc
{
if(l_mouse_button==1)
	oldpoint=pos;
if(l_mouse_button==2)
	{
	for(int i=0;i<f3df.NumberFace;i++)
		{
		if( 
			( (f3df.Vertex3df[i].x>oldpoint.x && f3df.Vertex3df[i].x<pos.x) || (f3df.Vertex3df[i].x>pos.x && f3df.Vertex3df[i].x<oldpoint.x) ) &&
			( (f3df.Vertex3df[i].y>oldpoint.y && f3df.Vertex3df[i].y<pos.y) || (f3df.Vertex3df[i].y>pos.y && f3df.Vertex3df[i].y<oldpoint.y) )  
			)
			Editedmodel.Vertexes[i]=1;

		}
	}

if(r_mouse_button==1)
	oldpoint=pos;
if(r_mouse_button==2)
	{
	for(int i=0;i<f3df.NumberFace;i++)
		{
		if( 
			( (f3df.Vertex3df[i].x>oldpoint.x && f3df.Vertex3df[i].x<pos.x) || (f3df.Vertex3df[i].x>pos.x && f3df.Vertex3df[i].x<oldpoint.x) ) &&
			( (f3df.Vertex3df[i].y>oldpoint.y && f3df.Vertex3df[i].y<pos.y) || (f3df.Vertex3df[i].y>pos.y && f3df.Vertex3df[i].y<oldpoint.y) )  
			)
			Editedmodel.Vertexes[i]=0;

		}
	}
}




}








class filea3df
{
public:

void load()
{
ifstream odczyt("modeltxt.a3df");

odczyt>>Bones.ile;
odczyt>>Bones.ileanim;


//for(int i=0;i<Bones.ile;i++)
//{
//for(int i2=0;i2<4;i2++)
//{
//for(int i3=0;i3<4;i3++)
//odczyt>>Bones.bonemMatrix[i][i2][i3];
//}
//}
//
//
//
//for(int i=0;i<Bones.ile;i++)
//{
//for(int j=0;j<Bones.ileanim+1;j++)
//{
//for(int i2=0;i2<4;i2++)
//{
//for(int i3=0;i3<4;i3++)
//odczyt>>Bones.boneAnimMatrix[i][j][i2][i3];
//}
//
//}
//
//}


for(int i=0;i<Bones.ile;i++)
{
odczyt>>Bones.Trans[i].x>>Bones.Trans[i].y>>Bones.Trans[i].z;
odczyt>>Bones.Rot[i].x>>Bones.Rot[i].y>>Bones.Rot[i].z;
}



for(int i=0;i<Bones.ile;i++)
{
for(int j=0;j<Bones.ileanim+1;j++)
{
odczyt>>Bones.TransAnim[i][j].x>>Bones.TransAnim[i][j].y>>Bones.TransAnim[i][j].z;
odczyt>>Bones.RotAnim[i][j].x>>Bones.RotAnim[i][j].y>>Bones.RotAnim[i][j].z;
}
}


for(int i=0;i<f3df.NumberFace;i++)
odczyt>>f3df.TexCoord3df[i].z;

odczyt.close();
}

void save()
{
ofstream zapis("modeltxt.a3df");

zapis<<Bones.ile<<endl;
zapis<<Bones.ileanim<<endl;

for(int i=0;i<Bones.ile;i++)
{
zapis<<Bones.Trans[i].x<<" "<<Bones.Trans[i].y<<" "<<Bones.Trans[i].z<<endl;
zapis<<Bones.Rot[i].x<<" "<<Bones.Rot[i].y<<" "<<Bones.Rot[i].z<<endl;
zapis<<endl;
}

zapis<<endl;

for(int i=0;i<Bones.ile;i++)
{
for(int j=0;j<Bones.ileanim+1;j++)
{
zapis<<Bones.TransAnim[i][j].x<<" "<<Bones.TransAnim[i][j].y<<" "<<Bones.TransAnim[i][j].z<<endl;
zapis<<Bones.RotAnim[i][j].x<<" "<<Bones.RotAnim[i][j].y<<" "<<Bones.RotAnim[i][j].z<<endl;
zapis<<endl;
}
}

zapis<<endl;
for(int i=0;i<f3df.NumberFace;i++)
zapis<<f3df.TexCoord3df[i].z<<" ";


zapis.close();
}





void exporta3df()
{
ofstream zapis("modelindicestxt.a3df");

zapis<<Bones.ile<<endl;
zapis<<Bones.ileanim<<endl;

for(int i=0;i<Bones.ile;i++)
{
zapis<<Bones.Trans[i].x<<" "<<Bones.Trans[i].y<<endl;
zapis<<endl;
}

zapis<<endl;

for(int i=0;i<Bones.ile;i++)
{
for(int j=0;j<Bones.ileanim+1;j++)
{
zapis<<Bones.TransAnim[i][j].x<<" "<<Bones.TransAnim[i][j].y<<endl;
zapis<<Bones.RotAnim[i][j].z<<endl;
zapis<<endl;
}
}






Vector3f* itexcooed = new Vector3f[f3df.NumberFace];//tex coord i index kosci
Vector3f* ivert   = new Vector3f[f3df.NumberFace];
int* indices   = new int[f3df.NumberFace];


int ileindex=0;

for(int i=0;i<f3df.NumberFace;i++)
{
int byl=0;

for(int j=0;j<ileindex;j++)
if(i!=j  &&  
   f3df.TexCoord3df[i].x == itexcooed[j].x && f3df.TexCoord3df[i].y == itexcooed[j].y && f3df.TexCoord3df[i].z == itexcooed[j].z && 
   f3df.Vertex3df[i].x == ivert[j].x && f3df.Vertex3df[i].y == ivert[j].y && f3df.Vertex3df[i].z == ivert[j].z )
	{
		byl=1;
		indices[i]=j;
	}

if(byl==0)
{
itexcooed[ileindex]=f3df.TexCoord3df[i];
ivert[ileindex]=f3df.Vertex3df[i];
indices[i]=ileindex;
ileindex++;
}

}

zapis<<endl;

zapis<<ileindex<<" "<<f3df.NumberFace;//odwrotnie ile face to ilosc indexow ..ile index to ilosc wierzcholkow

zapis<<endl;
for(int i=0;i<ileindex;i++)
{
zapis<< itexcooed[i].x <<" "<< itexcooed[i].y <<" "<< itexcooed[i].z <<endl;
zapis<< ivert[i].x <<" "<< ivert[i].y <<" "<< ivert[i].z <<endl;
}

for(int i=0;i<f3df.NumberFace;i++)
{
zapis<< indices[i] <<endl;

}



}






void logic()
{
if(keys[VK_S] && keys[VK_CONTROL])
	save();
if(keys[VK_E] && keys[VK_CONTROL])
	exporta3df();
if(keys[VK_L] && keys[VK_CONTROL])
	load();
}

};
filea3df Filea3df;













void DrawTlo()
{
cgGLBindProgram(VP);
cgGLBindProgram(FP);

glm::mat4 mat_worldViewProj = Matrix.MatProj * Matrix.MatView * Matrix.MatWorld;


cgGLSetMatrixParameterfr(  cgGetNamedParameter(VP,"ModelViewProj"), glm::value_ptr(mat_worldViewProj)  );
glBindTexture(GL_TEXTURE_2D, tex[5]);

glBegin(GL_QUADS);
glTexCoord2f(0.0f, 1.0f); glVertex3f(-4.0f, 4.0f, -1.2f);
glTexCoord2f(1.0f, 1.0f); glVertex3f( 4.0f, 4.0f, -1.2f);
glTexCoord2f(1.0f, 0.0f); glVertex3f( 4.0f,-4.0f, -1.2f);
glTexCoord2f(0.0f, 0.0f); glVertex3f(-4.0f,-4.0f, -1.2f);
glEnd();
}