#include "cgsh.h"

#define ILE_TEX 7
GLuint tex[ILE_TEX];


void loadtexture()
{

string nazwy_plikow[ILE_TEX];
nazwy_plikow[0]="model/texa.bmp";
nazwy_plikow[1]="model/tex.png";
nazwy_plikow[2]="bmp/bone.bmp";
nazwy_plikow[3]="bmp/unselect.bmp";
nazwy_plikow[4]="bmp/red.bmp";
nazwy_plikow[5]="bmp/siata.bmp";
nazwy_plikow[6]="bmp/plank.bmp";

for(int i=0;i<ILE_TEX;i++)
{
	tex[i] = SOIL_load_OGL_texture
	(
	nazwy_plikow[i].c_str(),
	SOIL_LOAD_AUTO,
	SOIL_CREATE_NEW_ID,
	SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
	);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	/* check for an error during the load process */
	if( 0 == tex[i] )
	{
		MessageBoxA(NULL,"SOIL loading error: '%s'\n",SOIL_last_result(),MB_OK | MB_ICONINFORMATION);
	}
}


}