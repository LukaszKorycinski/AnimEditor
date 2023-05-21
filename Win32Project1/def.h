#include <windows.h>
#include <mmsystem.h>
#include <windowsx.h>
#include <iostream>
#include <fstream>
#include <stdio.h>		
#include <gl\gl.h>			
#include <gl\glu.h>			
//#include <gl\glaux.h>
//#include <gl\glext.h>
//#include <gl\glfw.h>
//#include <gl\wglext.h>
#include "soil\SOIL.h"

#include <stdarg.h> 
#include <cassert>
#include <string>
#include <math.h>
#include <time.h>
#include <vector>

#include "glm/glm.hpp"

#include "glm/vec3.hpp" 
#include "glm/vec4.hpp" 
#include "glm/mat4x4.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "glm/gtc/matrix_transform.hpp"

using namespace std;

HDC			hDC=NULL;
HGLRC		hRC=NULL;		
HWND		hWnd=NULL;
HINSTANCE	hInstance;	


int tryb=0;//0-tekstury 1-siatka/dodawanie koœci


float maxf(float a, float b) {if(a>b)return a;else return b;}
float minf(float a, float b) {if(a<b)return a;else return b;}
int maxi(int a, int b) {if(a>b)return a;else return b;}

bool fullscreen=0;


bool	keys[256];	
#define VK_PLUS  43
#define VK_MINUS 45
#define VK_0 48
#define VK_1 49
#define VK_2 50
#define VK_3 51
#define VK_4 52
#define VK_5 53
#define VK_6 54
#define VK_7 55
#define VK_8 56
#define VK_9 57
#define VK_A 65
#define VK_B 66
#define VK_C 67
#define VK_D 68
#define VK_E 69
#define VK_F 70
#define VK_G 71
#define VK_H 72
#define VK_I 73
#define VK_J 74
#define VK_K 75
#define VK_L 76
#define VK_M 77
#define VK_N 78
#define VK_O 79
#define VK_P 80
#define VK_Q 81
#define VK_R 82
#define VK_S 83
#define VK_T 84
#define VK_U 85
#define VK_V 86
#define VK_W 87
#define VK_X 88
#define VK_Y 89
#define VK_Z 90





#define WM_MOUSEWHEEL 0x020A
#define GET_WHEEL_DELTA_WPARAM(wParam) ((short)HIWORD(wParam))

float PI = 3.14159265f;

const float piover180 = 0.0174532925f;

int endapp=0;
float kursorPosX, kursorPosY;

int szerokosc=800, wysokosc=700;





class Vector2f
{
public:
float x,y;
};

class Vector4f
{
public:
float x,y,z,w;
Vector4f()
{x=y=z=w=0.0f;}
Vector4f(float a, float b, float c, float d )
{
x=a;
y=b;
z=c;
w=d;
}
};


class Vector2i
{
public:
int x,y;
Vector2i()
{
x=y=0;
}
Vector2i(int a,int b)
{
x=a;y=b;
}
};

class Vector4i
{
public:
int x,y,z,w;
Vector4i()
{
x=y=z=w=0;
}
Vector4i(int a,int b,int c, int d)
{
x=a;y=b;z=c;w=d;
}
};

Vector2f Rotate(float r, float angle)
{
Vector2f wynik;
angle =  (PI * angle) / 180  ;
wynik.x=sin(angle)*10;
wynik.y=cos(angle)*10;
return wynik;
}

class fps
{
public:

int FPS, FPStmp;
float fFPS;
int sek, sekTMP;


fps()
	{
	FPS=0;fFPS=0.0f;
	sek=int(time(NULL));
	}

void Call()
	{
		sek=int(time(NULL));
		if(sek==sekTMP)
			FPStmp++;
		else
			{
			FPS=FPStmp;
			fFPS=float(FPS);
			FPStmp=0;
			sekTMP=int(time(NULL));
			}
	}

};
fps Fps;



class loop
{
public:
DWORD old, curr;
float lOOp;

void callOld()
{
old=timeGetTime();
}

void callCurr()
{
curr=timeGetTime();
}


void callLoop()
{
lOOp=float(curr-old);
}

};

loop Loop;

class Vector3f
{
public:
GLfloat x,y,z;

Vector3f()
{
x=0.0f;
y=0.0f;
z=0.0f;
}

Vector3f(float r)
{
x=r;
y=r;
z=r;
}

Vector3f(float r, float g, float b)
{
x=r;
y=g;
z=b;
}

void null()
{
x=0.0f;
y=0.0f;
z=0.0f;
}

void set(float r, float g, float b)
{
x=r;
y=g;
z=b;
}

void normalize()
{
if(fabs(x)+fabs(y)+fabs(z)>0.00001f)
{
Vector3f l;
l.x=l.y=l.z=sqrt(x*x + y*y + z*z);
//v/l;
x/=l.x;
y/=l.y;
z/=l.z;
}
else
x=y=z=0.0f;
}

float iloczyn_skalarny(Vector3f a, Vector3f b)
{
return a.x*b.x + a.y*b.y + a.z*b.z;
}


Vector3f iloczyn_vectorowy(Vector3f a, Vector3f b)
{
Vector3f wynik;
wynik.x=a.y*b.z-a.z*b.y;
wynik.y=a.z*b.x-a.x*b.z;
wynik.z=a.x*b.y-a.y*b.x;
return wynik;
}

Vector3f Vector3f::operator*(const Vector3f& wektor1) const
{
Vector3f wynik;
wynik.x=wektor1.x*x;
wynik.y=wektor1.y*y;
wynik.z=wektor1.z*z;
return wynik;
}

Vector3f Vector3f::operator*(const float& skalar) const
{
Vector3f wynik;
wynik.x=skalar*x;
wynik.y=skalar*y;
wynik.z=skalar*z;
return wynik;
}

Vector3f Vector3f::operator/(const Vector3f& wektor1) const//pamiêtaæ o kolejnoœci dzielenia!
{
Vector3f wynik;
wynik.x=x/wektor1.x;
wynik.y=y/wektor1.y;
wynik.z=z/wektor1.z;
return wynik;
}

Vector3f Vector3f::operator/(const float& skalar) const//pamiêtaæ o kolejnoœci dzielenia!
{
Vector3f wynik;
wynik.x=x/skalar;
wynik.y=y/skalar;
wynik.z=z/skalar;
return wynik;
}

Vector3f Vector3f::operator+(const Vector3f& wektor1) const
{
Vector3f wynik;
wynik.x=wektor1.x+x;
wynik.y=wektor1.y+y;
wynik.z=wektor1.z+z;
return wynik;
}

Vector3f Vector3f::operator-(const Vector3f& wektor1) const
{
Vector3f wynik;
wynik.x=x-wektor1.x;
wynik.y=y-wektor1.y;
wynik.z=z-wektor1.z;
return wynik;
}

Vector3f operator-() const
{ return Vector3f(-x, -y, -z); }

bool operator== (Vector3f i) const
{ return (i.x==x && i.y==y && i.z==z); }


bool operator!= (Vector3f i) const
{ return (i.x!=x || i.y!=y ||i.z!=z); }

};


Vector3f normalize(Vector3f v)
{
float l=sqrt(v.x*v.x + v.y*v.y + v.z*v.z);


if(l>0.0f)
{
v=v/l;
return v;
}
else
return v;
}









int right_key=0; //0-nic 1=wcisniecie 2=wcisniety
int left_key=0; //0-nic 1=wcisniecie 2=wcisniety 3=puszczony
int w_key=0; //0-nic 1=wcisniecie 2=wcisniety
int a_key=0; //0-nic 1=wcisniecie 2=wcisniety
int d_key=0; //0-nic 1=wcisniecie 2=wcisniety
int s_key=0; //0-nic 1=wcisniecie 2=wcisniety
int e_key=0; //0-nic 1=wcisniecie 2=wcisniety
int h_key=0; //0-nic 1=wcisniecie 2=wcisniety
int o_key=0; //0-nic 1=wcisniecie 2=wcisniety
int j_key=0; //0-nic 1=wcisniecie 2=wcisniety
int k_key=0; //0-nic 1=wcisniecie 2=wcisniety
int l_key=0; //0-nic 1=wcisniecie 2=wcisniety
int i_key=0; //0-nic 1=wcisniecie 2=wcisniety
int g_key=0; //0-nic 1=wcisniecie 2=wcisniety
int f_key=0; //0-nic 1=wcisniecie 2=wcisniety
int r_key=0; //0-nic 1=wcisniecie 2=wcisniety
int t_key=0; //0-nic 1=wcisniecie 2=wcisniety
int y_key=0; //0-nic 1=wcisniecie 2=wcisniety
int v_key=0; //0-nic 1=wcisniecie 2=wcisniety
int u_key=0; //0-nic 1=wcisniecie 2=wcisniety
int up_key=0; //0-nic 1=wcisniecie 2=wcisniety
int b_key=0; //0-nic 1=wcisniecie 2=wcisniety
int z_key=0; //0-nic 1=wcisniecie 2=wcisniety
int x_key=0; //0-nic 1=wcisniecie 2=wcisniety
int l_mouse_button=0;int mouse_nad_sth=0;//1-nad menu jakimœ
int r_mouse_button=0;
float space_key=0.0f;
float space_pad=0.0f; //0-nic 1=wcisniecie 2=wcisniety
float esc_key=0.0f; //0-nic 1=wcisniecie 2=wcisniety

int num_press=0;
void numPressed()
{
if(keys[VK_0])num_press=0;
if(keys[VK_1])num_press=1;
if(keys[VK_2])num_press=2;
if(keys[VK_3])num_press=3;
if(keys[VK_4])num_press=4;
if(keys[VK_5])num_press=5;
if(keys[VK_6])num_press=6;
if(keys[VK_7])num_press=7;
if(keys[VK_8])num_press=8;
if(keys[VK_9])num_press=9;
if(keys[VK_F5])num_press=10;
if(keys[VK_F6])num_press=11;
if(keys[VK_F7])num_press=12;
if(keys[VK_F8])num_press=13;
if(keys[VK_F9])num_press=14;
}

void key()
{
if(HIBYTE(GetKeyState(VK_LBUTTON)) )
if(l_mouse_button==0)
l_mouse_button=1;
else
l_mouse_button=2;

if(!HIBYTE(GetKeyState(VK_LBUTTON)))
if(l_mouse_button==2)
l_mouse_button=3;
else
l_mouse_button=0;
//////////////////////////

if(HIBYTE(GetKeyState(VK_RBUTTON)) && r_mouse_button==0)
r_mouse_button=1;
else
if(HIBYTE(GetKeyState(VK_RBUTTON)))
r_mouse_button=2;

if(r_mouse_button==2 && !HIBYTE(GetKeyState(VK_RBUTTON)))
r_mouse_button=3;
else
if(!HIBYTE(GetKeyState(VK_RBUTTON)))
r_mouse_button=0;
//////////////////////////
if(keys[VK_ESCAPE] && esc_key==0)
esc_key=1;
else
esc_key=2;
if(!keys[VK_ESCAPE])
esc_key=0;
//////////////////////////
if(keys[VK_RIGHT] && right_key==0)
right_key=1;
else
right_key=2;
if(!keys[VK_RIGHT])
right_key=0;
//////////////////////////
if(keys[VK_X] && x_key==0)
x_key=1;
else
x_key=2;
if(!keys[VK_X])
x_key=0;
//////////////////////////
if(keys[VK_Z] && z_key==0)
z_key=1;
else
z_key=2;
if(!keys[VK_Z])
z_key=0;
//////////////////////////
if(keys[VK_E] && e_key==0)
e_key=1;
else
e_key=2;
if(!keys[VK_E])
e_key=0;
//////////////////////////
if(keys[VK_I] && i_key==0)
i_key=1;
else
i_key=2;
if(!keys[VK_I])
i_key=0;
//////////////////////////
if(keys[VK_O] && o_key==0)
o_key=1;
else
o_key=2;
if(!keys[VK_O])
o_key=0;
//////////////////////////
if(keys[VK_B] && b_key==0)
b_key=1;
else
b_key=2;
if(!keys[VK_B])
b_key=0;
//////////////////////////
if(keys[VK_LEFT] && left_key==0)
left_key=1;
else
left_key=2;
if(!keys[VK_LEFT])
left_key=0;
//////////////////////////
if(keys[VK_W] && w_key==0)
w_key=1;
else
w_key=2;
if(!keys[VK_W])
w_key=0;
//////////////////////////
if(keys[VK_A] && a_key==0)
a_key=1;
else
a_key=2;
if(!keys[VK_A])
a_key=0;
//////////////////////////
if(keys[VK_R] && r_key==0)
r_key=1;
else
r_key=2;
if(!keys[VK_R])
r_key=0;
//////////////////////////
if(keys[VK_T] && t_key==0)
t_key=1;
else
t_key=2;
if(!keys[VK_T])
t_key=0;
//////////////////////////
if(keys[VK_Y] && y_key==0)
y_key=1;
else
y_key=2;
if(!keys[VK_Y])
y_key=0;
//////////////////////////
if(keys[VK_D] && d_key==0)
d_key=1;
else
d_key=2;
if(!keys[VK_D])
d_key=0;
//////////////////////////
if(keys[VK_S] && s_key==0)
s_key=1;
else
s_key=2;
if(!keys[VK_S])
s_key=0;
/////////////////////////
if(keys[VK_H] && h_key==0)
h_key=1;
else
h_key=2;
if(!keys[VK_H])
h_key=0;
/////////////////////////
if(keys[VK_U] && u_key==0)
u_key=1;
else
u_key=2;
if(!keys[VK_U])
u_key=0;
/////////////////////////
if(keys[VK_J] && j_key==0)
j_key=1;
else
j_key=2;
if(!keys[VK_J])
j_key=0;
/////////////////////////
if(keys[VK_K] && k_key==0)
k_key=1;
else
k_key=2;
if(!keys[VK_K])
k_key=0;
/////////////////////////
if(keys[VK_L] && l_key==0)
l_key=1;
else
l_key=2;
if(!keys[VK_L])
l_key=0;
/////////////////////////
if(keys[VK_G] && g_key==0)
g_key=1;
else
g_key=2;
if(!keys[VK_G])
g_key=0;
////////////////////////
if(keys[VK_F] && f_key==0)
f_key=1;
else
f_key=2;
if(!keys[VK_F])
f_key=0;
////////////////////////
if(keys[VK_V] && v_key==0)
v_key=1;
else
v_key=2;
if(!keys[VK_V])
v_key=0;
////////////////////////
if( keys[VK_SPACE] && space_key==0)
space_key=1;
else
space_key=2;
if(!keys[VK_SPACE])
space_key=0;
//////////////////////////
if(keys[VK_UP] && up_key==0)
up_key=1;
else
up_key=2;
if(!keys[VK_UP])
up_key=0;
//////////////////////////
}










class geom
{
public:

float distanc2D(Vector3f V1, Vector3f V2)
{
if(fabs(V1.z-V2.z)>0.25f)
return 999999.0f;
return sqrt(   (V2.x-V1.x)*(V2.x-V1.x) + (V2.y-V1.y)*(V2.y-V1.y)   );
}

float interpolate (float f1, float f2, float waga)
{
float out=f1*(1.0f-waga) + f2*waga;
return out;
}

Vector3f interpolate (Vector3f v1, Vector3f v2, float waga)
{
Vector3f out(v1.x*(1.0f-waga) + v2.x*waga, v1.y*(1.0f-waga) + v2.y*waga, v1.z*(1.0f-waga) + v2.z*waga);
return out;
}


};
geom Geom;












class matrix4x4
{
public:
float m[16];

matrix4x4()
{
m[0]=1;m[1]=0;m[2]=0;m[3]=0;
m[4]=0;m[5]=1;m[6]=0;m[7]=0;
m[8]=0;m[9]=0;m[10]=1;m[11]=0;
m[12]=0;m[13]=0;m[14]=0;m[15]=1;
}

};

matrix4x4 M_translate(matrix4x4 m,Vector3f p)
{
matrix4x4 Out;

for(int i=0;i<16;i++)
{
Out.m[i]=m.m[i];
}

Out.m[12]=p.x;
Out.m[13]=p.y;
Out.m[14]=p.z;
return Out;
}




class quaterion4f
{
public:
quaterion4f()
{
x=y=z=w=0.0f;
}
quaterion4f(float a,float b, float c, float d)
{
x=a;y=b;z=c;w=d;
}
float x,y,z,w;


float Dot( quaterion4f q1, quaterion4f q2 )
{
  return q1.x*q2.x + q1.y*q2.y + q1.z*q2.z + q1.w*q2.w;
}


void QuaternionRotationZ(float a)
{
  a *= 0.5f;
  x = 0.0f; y = 0.0f; z = sinf(a);
  w = cosf(a);
}


quaterion4f Interpolate(const quaterion4f q0, const quaterion4f q1, float t)
{
quaterion4f Out;
  float cosOmega = Dot(q0, q1);
  quaterion4f new_q1 = q1;
  if (cosOmega < 0.0f)
  {
    new_q1.x = -new_q1.x;
    new_q1.y = -new_q1.y;
    new_q1.z = -new_q1.z;
    new_q1.w = -new_q1.w;
    cosOmega = -cosOmega;
  }

  float k0, k1;
  if (cosOmega > 0.9999f)
  {
    k0 = 1.0f - t;
    k1 = t;
  }
  else
  {
    float sinOmega = sqrtf(1.0f - cosOmega*cosOmega);
    float omega = atan2f(sinOmega, cosOmega);
    float oneOverSinOmega = 1.0f / sinOmega;
    k0 = sinf((1.0f - t) * omega) * oneOverSinOmega;
    k1 = sinf(t*omega) * oneOverSinOmega;
  }
  Out.x = q0.x*k0 + new_q1.x*k1;
  Out.y = q0.y*k0 + new_q1.y*k1;
  Out.z = q0.z*k0 + new_q1.z*k1;
  Out.w = q0.w*k0 + new_q1.w*k1;
return Out;
}





Vector3f CalcQuaternionAxis()//oœ kwateriona
{
Vector3f Out;

  float SinThetaOver25q = 1.0f - w * w;
  if (SinThetaOver25q <= 0.0f)
  {
    Out.x = Out.y = Out.z = 0.0f;
    return Out;
  }
  float OneOverSinThetaOver2 = 1.0f / sqrtf(SinThetaOver25q);
  Out.x = x * OneOverSinThetaOver2;
  Out.y = y * OneOverSinThetaOver2;
  Out.z = z * OneOverSinThetaOver2;
  return Out;
}

// Funkcja pomocnicza
float safe_acos(float x)
{
  if (x <= -1.0f) return 3.14159265f;
  if (x >= 1.0f) return 0.0f;
  return acosf(x);
}

float CalcQuaternionAngle()//k¹t zapisany w kwaterionie
{
  return safe_acos(w) * 2.0f;
}






Vector3f QuaternionI2OToEulerAngles()
{
	Vector3f out;
  float sp = -2.0f * (y*z + w*x);

  if (sp == 1.0f)
  {
    out.x = PI * 2 * sp;
    out.y = atan2f(-x*z - w*y, 0.5f - y*y - z*z);
    out.z = 0.0f;
  }
  else
  {
    out.x = asinf(sp);
    out.y = atan2f(x*z - w*y, 0.5f - x*x - y*y);
    out.z = atan2f(x*y - w*z, 0.5f - x*x - z*z);
  }
  return out;
}






matrix4x4 QuaternionToRotationMatrix()
{
matrix4x4 out;
  float
    xx = x * x, yy = y * y, zz = z * z,
    xy = x * y, xz = x * z,
    yz = y * z, wx = w * x,
    wy = w * y, wz = w * z;

  out.m[0] = 1.0f - 2.0f * ( yy + zz );
  out.m[1] = 2.0f * ( xy + wz );
  out.m[2] = 2.0f * ( xz - wy );
  out.m[3] = 0.0f;
  
  out.m[4] = 2.0f * ( xy - wz );
  out.m[5] = 1.0f - 2.0f * ( xx + zz );
  out.m[6] = 2.0f * ( yz + wx );
  out.m[7] = 0.0f;
  
  out.m[7] = 2.0f * ( xz + wy );
  out.m[8] = 2.0f * ( yz - wx );
  out.m[9] = 1.0f - 2.0f * ( xx + yy );
  out.m[10] = 0.0f;
  
  out.m[11] = 0.0f;
  out.m[12] = 0.0f;
  out.m[13] = 0.0f;
  out.m[14] = 1.0f;


  //out.m[0] = 1.0f - 2.0f * ( yy + zz );
  //out.m[1] = 2.0f * ( xy - wz );
  //out.m[2] = 2.0f * ( xz + wy );
  //out.m[3] = 0.0f;

  //out.m[4] = 2.0f * ( xy + wz );
  //out.m[5] = 1.0f - 2.0f * ( xx + zz );
  //out.m[6] = 2.0f * ( yz - wx );
  //out.m[7] = 0.0f;

  //out.m[8] = 2.0f * ( xz - wy );
  //out.m[9] = 2.0f * ( yz + wx );
  //out.m[10] = 1.0f - 2.0f * ( xx + yy );
  //out.m[11] = 0.0f;

  //out.m[12] = 0.0f;
  //out.m[13] = 0.0f;
  //out.m[14] = 0.0f;
  //out.m[15] = 1.0f;

return out;
}



};