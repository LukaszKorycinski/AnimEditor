#include "matrix.h"

#include<Cg/cg.h>
#include<Cg/cgGL.h>




CGcontext    context;      // Kontekst przechowuj¹cy nasze programy Cg
CGprogram    VP, FP, VPbone, FPbone;

CGprofile cgFragmentProfile, cgVertexProfile;

void InvCgInit()
{
context=cgCreateContext();
cgVertexProfile   = cgGLGetLatestProfile(CG_GL_VERTEX);
cgFragmentProfile = cgGLGetLatestProfile(CG_GL_FRAGMENT);         // Pobieramy profil wierzcho³ków 

    if (cgVertexProfile   == CG_PROFILE_UNKNOWN)
    {
        MessageBoxA(NULL, "Nieznany typ profilu Wierzcho³ków", "B³¹d", MB_OK);
    } 

    if (cgFragmentProfile == CG_PROFILE_UNKNOWN)
    {
        MessageBoxA(NULL, "Nieznany typ profilu Fragmentów", "B³¹d", MB_OK);
    } 
    cgGLSetOptimalOptions(cgVertexProfile);
    cgGLSetOptimalOptions(cgFragmentProfile);  


VP      = cgCreateProgramFromFile(context, CG_SOURCE, "CG/VP.cg",    cgVertexProfile,   "main", 0);
FP      = cgCreateProgramFromFile(context, CG_SOURCE, "CG/FP.cg",    cgFragmentProfile, "main", 0);
VPbone      = cgCreateProgramFromFile(context, CG_SOURCE, "CG/VPbone.cg",    cgVertexProfile,   "main", 0);
FPbone      = cgCreateProgramFromFile(context, CG_SOURCE, "CG/FPbone.cg",    cgFragmentProfile, "main", 0);

	if (VP == NULL)
    {
        CGerror Error = cgGetError(); 
        MessageBoxA(NULL, "VP", "B³¹d", MB_OK);
		MessageBoxA(NULL, cgGetErrorString(Error), "B³¹d", MB_OK);
    } 
	if (FP == NULL)
    {
        CGerror Error = cgGetError(); 
        MessageBoxA(NULL, "FP", "B³¹d", MB_OK);
		MessageBoxA(NULL, cgGetErrorString(Error), "B³¹d", MB_OK);
    } 
	if (VPbone == NULL)
    {
        CGerror Error = cgGetError(); 
        MessageBoxA(NULL, "VP", "B³¹d", MB_OK);
		MessageBoxA(NULL, cgGetErrorString(Error), "B³¹d", MB_OK);
    } 
	if (FPbone == NULL)
    {
        CGerror Error = cgGetError(); 
        MessageBoxA(NULL, "FP", "B³¹d", MB_OK);
		MessageBoxA(NULL, cgGetErrorString(Error), "B³¹d", MB_OK);
    } 

cgGLLoadProgram(VP);         // £adujemy program  
cgGLLoadProgram(FP);         // £adujemy program  
cgGLLoadProgram(VPbone);         // £adujemy program  
cgGLLoadProgram(FPbone);         // £adujemy program 
}

void InvCgGlDestroy()
{
cgDestroyContext(context);      
}




