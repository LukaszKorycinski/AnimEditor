#include "3df.h"

class font
{
public:

GLuint    base;
HFONT    fontt,fontt2;         // Identyfikator czicionki windowsowej
HFONT    oldfont;         // U�yte dla Good House Keeping

GLvoid BuildFont(void)         // Buduje nasz� bitmapow� czcionk�
{

    base = glGenLists(96);         // Przechowuje 96 znak�w     

	fontt = CreateFontA(        -20,          // Wysoko�� czcionki  
	0,         // �rednia szeroko�� znaku
    0,         // K�t pochylenia
    0,         // K�t orientacji wzgl�dem linii bazowej
	FW_BOLD,         // Waga czcionki
	FALSE,         // Kursywa
    FALSE,         // Podkre�lenie
    FALSE,         // Pogrubienie
	ANSI_CHARSET,         // Identyfikator zbioru znak�w
	OUT_TT_PRECIS,         // Dok�adno�� prezentacji
	CLIP_DEFAULT_PRECIS,         // Dok�adno�� przyci�cia
	ANTIALIASED_QUALITY,         // Jako�� prezentacji
	FF_DONTCARE|DEFAULT_PITCH,         // Rodzina i podzia�ka czcionki
	"Calibri");         // Nazwa czcionki

	fontt2 = CreateFontA(        -15,          // Wysoko�� czcionki  
	0,         // �rednia szeroko�� znaku
    0,         // K�t pochylenia
    0,         // K�t orientacji wzgl�dem linii bazowej
	FW_BOLD,         // Waga czcionki
	FALSE,         // Kursywa
    FALSE,         // Podkre�lenie
    FALSE,         // Pogrubienie
	ANSI_CHARSET,         // Identyfikator zbioru znak�w
	OUT_TT_PRECIS,         // Dok�adno�� prezentacji
	CLIP_DEFAULT_PRECIS,         // Dok�adno�� przyci�cia
	ANTIALIASED_QUALITY,         // Jako�� prezentacji
	FF_DONTCARE|DEFAULT_PITCH,         // Rodzina i podzia�ka czcionki
	"Arial");         // Nazwa czcionki

	oldfont = (HFONT)SelectObject(hDC, fontt);         // Wybiera czcionk� jak� chcemy
    wglUseFontBitmaps(hDC, 32, 96, base);         // Buduje 96 znak�w zaczynaj�c od znaku 32
    SelectObject(hDC, oldfont);         // Wybiera czcionk� jak� chcemy
    //DeleteObject(font);         // Kasuje czcionk�
} 

GLvoid KillFont(GLvoid)         // Kasuje listy czcionki
{
    DeleteObject(fontt);         // Kasuje czcionk�
    DeleteObject(fontt2);         // Kasuje czcionk�
    glDeleteLists(base, 96);         // Kasuje wszystkie 96 znak�w  
} 

GLvoid glPrint(const char *fmt, ...)         // W�asna procedura GL "Print"
{ 
    char        text[256];         // Przechowuje stringa
    va_list        ap;         // Wska�nik do listy argument�w
    if (fmt == NULL)         // Je�eli nie ma tekstu
        return;         // nie robi nic
    va_start(ap, fmt);         // Przeszukje string w celu znalezienia zmiennych
     vsprintf(text, fmt, ap);         // Konwertuje symbole na aktualne numery
    va_end(ap);         // Rezultaty s� przechowywane w zmiennej text
    glPushAttrib(GL_LIST_BIT);         // Wrzucamy list� na stos  
    glListBase(base - 32);         // Odejmuje pierwsze 32 znaki     
    glCallLists((GLsizei)strlen(text), GL_UNSIGNED_BYTE, text);         // Rysuje nasz tekst            ( NOWE )
    glPopAttrib();         // Zdejmuje ze stosu nasz� list�    
} 





char teksty[15][256];
char tekstyp[15][256];
Vector2f p[15];
int ile,ilep;

font()
{
ile=ilep=0;
}

void invPrint(const char *fmt, ...)
{
va_list ap; 
va_start(ap, fmt);
vsprintf(teksty[ile], fmt, ap);
va_end(ap); 
ile++;
}

void invPrintPos(float x, float y, const char *fmt, ... )
{
p[ilep].x=x;
p[ilep].y=y;
va_list ap; 
va_start(ap, fmt);
vsprintf(tekstyp[ilep], fmt, ap);
va_end(ap); 
ilep++;
}

void PrintAll()
{
oldfont = (HFONT)SelectObject(hDC, fontt);         // Wybiera czcionk� jak� chcemy
wglUseFontBitmaps(hDC, 32, 96, base);         // Buduje 96 znak�w zaczynaj�c od znaku 32
SelectObject(hDC, oldfont);         // Wybiera czcionk� jak� chcemy
glColor3f(1.0f,1.0f,1.0f);

glRasterPos2f(-1.0f, 0.95625f);
for(int i=0;i<ile;i++)
{
    glPushAttrib(GL_LIST_BIT);         // Wrzucamy list� na stos  
    glListBase(base - 32);         // Odejmuje pierwsze 32 znaki     
    glCallLists((GLsizei)strlen(teksty[i]), GL_UNSIGNED_BYTE, teksty[i]);         // Rysuje nasz tekst            ( NOWE )
    glPopAttrib();         // Zdejmuje ze stosu nasz� list�    
}
ile=0;

oldfont = (HFONT)SelectObject(hDC, fontt2);         // Wybiera czcionk� jak� chcemy
wglUseFontBitmaps(hDC, 32, 96, base);         // Buduje 96 znak�w zaczynaj�c od znaku 32
SelectObject(hDC, oldfont);         // Wybiera czcionk� jak� chcemy
glColor3f(0.0f,0.0f,0.0f);
for(int i=0;i<ilep;i++)
{
	glRasterPos2f(p[i].x, p[i].y);
    glPushAttrib(GL_LIST_BIT);         // Wrzucamy list� na stos  
    glListBase(base - 32);         // Odejmuje pierwsze 32 znaki     
    glCallLists((GLsizei)strlen(tekstyp[i]), GL_UNSIGNED_BYTE, tekstyp[i]);         // Rysuje nasz tekst            ( NOWE )
    glPopAttrib();         // Zdejmuje ze stosu nasz� list�    
}
ilep=0;
}

/*
% jest jak znacznik m�wi�cy nie pisz 7.2f na ekranie,
poniewa� to reprezentuje zmienn�. 7.2 oznacza, �e 
maksymalnie zostanie wy�wietlonych 7 cyfr, a po kropce 2. 
W ko�cu f oznacza, �e wy�wietlana zmienna jest typu float.*/
};

font Font;