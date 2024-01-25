
#define WIN32_LEAN_AND_MEAN //No agrega librerías que no se vayan a utilizar

#include <Windows.h>
#include <stdio.h>
#include <dinput.h>
#include <gdiplus.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream> 
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#include "GamePadRR.h"
#include <memory.h>
#pragma comment(lib, "XInput.lib")

GamePadRR* Gpad;

//ESTO ES DEL GAMEPAD
//GamePadRR* Gpad;
//Gpad = new GamePadRR(1);
//#include "GamePadRR.h"
//#include <memory.h>
//#pragma comment(lib, "XInput.lib")


using namespace std;
using namespace Gdiplus;


bool cambio = true;
bool cambiox2 = true;
bool cambiox3 = true;
bool cambioy1 = true;
const int ANCHO_VENTANA = 800;
const int ALTO_VENTANA = 600;
const int BPP = 4;
const int TICK = 105;
int fanx1 = 200;
int fanx2 = 300;
int fanx3 = 550;
int fany1 = 100;
int fany2 = 200;
const unsigned int BLUE = 0xFF0000FF;
const unsigned int GREEN = 0xFF00FF00;
const unsigned int RED = 0xFFFF0000;
int movimiento = 0;
int movFondo = 0;
int indice = 0;
int indMov = 0;
bool escala;
bool colora = FALSE;
bool coloraa = FALSE;
bool coloraav = FALSE;
bool coloraavr = FALSE;

bool colorv = FALSE;
int contador = 0;
int contadora = 0;
int contadorav = 0;
int contadoravr = 0;
int count = 0;
int score=0;


bool pantallainicial=true;

struct POSITION {
	int X;
	int Y;
};

struct DIMENSION {
	int ANCHO;
	int ALTO;
};

struct Input
{
	enum Keys
	{
		Backspace = 0x08, Tab,
		Clear = 0x0C, Enter,
		Shift = 0x10, Control, Alt,
		Escape = 0x1B,
		Space = 0x20, PageUp, PageDown, End, Home, Left, Up, Right, Down,
		Zero = 0x30, One, Two, Three, Four, Five, Six, Seven, Eight, Nine,
		A = 0x41, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
		NumPad0 = 0x60, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
		F1 = 0x70, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12
	};
}input;

struct Colisiones {
	int cantidad = 1;
	int ScaleX;
	int ScaleY;
	int HitBoxAncho = 64;
	int HitboxAlto = 19;
	int HitboxX = 480;
	int HitboxY = 380;
	int HitboxScaleX;
	int HitboxScaleY;
}MisColisiones,MisColisiones2;

struct ColisionEnemigo {
	int* puntero;
	const unsigned int color= 0xFFFFFFFF;
	int anchow;
	int altow;
	int PosX;
	int PosY;
	int anchohit=20;
	int altohit=30;
	int PosX2=2;
	int PosY2=2;

}MiEnemigo,MiPersonaje;


bool mirror;
bool punto=false;
bool mirrorEne;
int *ptrBuffer;
int direccionGiro;
unsigned char * ptrBack;
unsigned char * ptrSprite;
unsigned char * ptrcora;
unsigned char* ptrenemigo;
unsigned char* ptrlose;
unsigned char* ptrwin;
unsigned char* ptrcoin;
unsigned char* ptrpause;

DIMENSION dmnBack;
DIMENSION dmnSprite;
DIMENSION dmncora;
DIMENSION dmnenemigo;
DIMENSION dmnlose;
DIMENSION dmnwin;
DIMENSION dmncoin;
DIMENSION dmnpause;

POSITION posFigura;
POSITION newP;
POSITION posEnemigo;
POSITION posCoin;


bool KEYS[256];
int segundos;
int minutos;
bool jumping = false;
int jumanim = 105;
int korv = 0;
int pc = 0;
int pi = 0;
int pt = 0;
const unsigned int TRANSPARENCY = 0xFF00FF00;
const unsigned int WHITE = 0xFFFFFFFF;
int contajeinc = 0;
int cajuela = 0;
int si = 0;
int medidas1 = 520;
int medidas2 = 540;
int medidas3 = 550;
bool obstaculo = false;
bool ganar = false;
int mensaje = 0;
int newcon = 0;
int caso,caso2;
bool explota = false;
bool randomnum = false;
bool randomnum2 = false;
bool colision1 = false;
bool colision2 = false;
bool animacion = false;
bool pausa = false;
int korv2 = 0, jumanim2 = 105;
bool mambo = false;
int c=0;
bool enemigo = false;
bool pantallaganador = 0;
bool pantallaperdedor = 0;
bool yapuestogrr = 0;
char Fullpath[MAX_PATH];
int picar = 0;
bool puntuacionscreen = 0;
bool acabar = 0;
int tamaño=0,k=0,sise=60;
bool terminarimprimir=0;
string nombre="";
fstream Archivo;
ofstream archivo;
ifstream txt;
int Fuente2 = 30;
COLORREF colorn = RGB(0, 0, 0);
char nombres[6][6] = {};
int puntajes[6] = {};
bool empiezajuego = false;


//Definicion de funciones
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
void MainRender(HWND hWnd);
void Init();
void KeysEvents();
unsigned char * CargaImagen(WCHAR rutaImagen[], DIMENSION * dmn);
POSITION setPosition(int x, int y);
void DibujaFondo(int *buffer, int *imagen, DIMENSION dmn, bool mirror);
void DibujaSprite(int *buffer, int *sprite, DIMENSION dmn, POSITION pos);
void DibujaSpriteEne(int* buffer, int* sprite, DIMENSION dmn, POSITION pos);
void dibujar_cronometro(HDC hdc);
void puntuaje(HDC hdc);
void jump();
void jump2();
void TranScaleblt(int* punteroDestino, int* punteroOrigen, int inicioXDestino, int inicioYDestino, int inicioXOrigen, int inicioYOrigen, int ancho, int alto, int anchodefondo, int anchodeorigen, int escalaX, int escalaY);
void DibujaHitbox(int* ptrBuffer,
	unsigned int color, int anchoWnd, int altoWnd, int HitboxX, int HitboxY, int HitboxAncho, int HitboxAlto, int escalaX, int escalaY);
void RenderizaObstaculos();
void RenderizaPersonaje();
void RenderizaEnemigo();
void Pasacaminando();
bool CheckCollision(ColisionEnemigo box1, ColisionEnemigo box2);


//Musica
void Pausa();
void Reproduce(const char audio[MAX_PATH]);
void Cerrar();

void puntuacione(HDC hdc);
void guardartxt();
void guardarPer();
void leer_Per();


enum DireccionGiro {
	ARRIBA, DERECHA, ABAJO, IZQUIERDA
};

int WINAPI wWinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PWSTR pCmdLine,
	int nCmdShow)
{
	WNDCLASSEX wc;									// Windows Class Structure
	HWND hWnd;
	MSG msg;

	TCHAR szAppName[] = TEXT("MyWinAPIApp");
	TCHAR szAppTitle[] = TEXT("Aplicación en Lenguaje Ensamblador / C++");

	hInstance = GetModuleHandle(NULL);				// Grab An Instance For Our Window

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;	// Redraw On Size, And Own DC For Window.
	wc.lpfnWndProc = (WNDPROC)WndProc;					// WndProc Handles Messages
	wc.cbClsExtra = 0;									// No Extra Window Data
	wc.cbWndExtra = 0;									// No Extra Window Data
	wc.hInstance = hInstance;							// Set The Instance	
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);			// Load The Default Icon
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Load The Arrow Pointer
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);			// No Background Required For GL
	wc.lpszMenuName = NULL;									// We Don't Want A Menu	
	wc.lpszClassName = szAppName;							// Set The Class Name
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc))									// Attempt To Register The Window Class
	{
		MessageBox(NULL,
			"Fallo al registrar clase (Failed To Register The Window Class).",
			"ERROR",
			MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE | WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,	// Extended Style For The Window
		szAppName,							// Class Name
		szAppTitle,							// Window Title
		WS_OVERLAPPEDWINDOW |				// Defined Window Style
		WS_CLIPSIBLINGS |					// Required Window Style
		WS_CLIPCHILDREN,					// Required Window Style
		0, 0,								// Window Position
		ANCHO_VENTANA,						// Calculate Window Width
		ALTO_VENTANA,						// Calculate Window Height
		NULL,								// No Parent Window
		NULL,								// No Menu
		hInstance,							// Instance
		NULL);								// Pass this class To WM_CREATE								

	if (hWnd == NULL) {
		MessageBox(NULL,
			"Error al crear ventana (Window Creation Error).",
			"ERROR",
			MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}

	SetForegroundWindow(hWnd);						// Slightly Higher Priority
	Init();
	ShowWindow(hWnd, nCmdShow);
	SetFocus(hWnd);

	SetTimer(hWnd, TICK, TICK, NULL);
	SetTimer(hWnd, 2, 1000, NULL);
	ZeroMemory(&msg, sizeof(MSG));
	Gpad = new GamePadRR(1);

	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return(int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)									// Check For Windows Messages
	{
	case WM_TIMER:
		if (wParam == TICK)
		{
			MainRender(hWnd);
		}
		if (wParam == 2)
		{
			if (empiezajuego == true) {
				if (pausa != true) {
					segundos++;
					if (segundos == 60) {
						segundos = 0;
						minutos++;
					}
					if (minutos == 60) {
						minutos = 0;
					}
				}
			}
			//InvalidateRect(hWnd, NULL, TRUE);
		}
		break;
	case WM_PAINT:
	{
		HDC hdc;
		PAINTSTRUCT ps;
		hdc = BeginPaint(hWnd, &ps);

		BITMAP bm;
		HBITMAP h_CMC = CreateBitmap(ANCHO_VENTANA, ALTO_VENTANA, 1, 32, ptrBuffer);
		HDC hdcMem = CreateCompatibleDC(hdc);
		HBITMAP hbmOld = (HBITMAP)SelectObject(hdcMem, h_CMC);
		GetObject(h_CMC, sizeof(bm), &bm);

		BitBlt(hdc, 0, 0, ANCHO_VENTANA, ALTO_VENTANA, hdcMem, 0, 0, SRCCOPY);

		SetBkColor(hdc, RGB(171, 126, 167));
		if (pantallainicial == false) {
			HFONT fuente2 = CreateFont(Fuente2, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET,
				OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, FIXED_PITCH | FF_DONTCARE, TEXT("Courier"));
			SelectObject(hdc, fuente2);
			SetTextColor(hdc, colorn);
			SetBkMode(hdc, TRANSPARENT); 

			TextOutW(hdc, 595 ,20, L"TIEMPO", 7);
			TextOutW(hdc, 295, 20, L"SCORE", 6);

			dibujar_cronometro(hdc);
			puntuaje(hdc);
		}
		if (puntuacionscreen != false) {
			COLORREF W = RGB(255, 255, 255);
			SetTextColor(hdc,W);
			SetBkMode(hdc, TRANSPARENT);

			puntuacione(hdc);
		}

		DeleteObject(h_CMC);
		SelectObject(hdcMem, hbmOld);
		DeleteDC(hdcMem);
		DeleteObject(hbmOld);
	}
	break;
	case WM_KEYDOWN:
	{
		KEYS[wParam] = true;
	}
	break;
	case WM_KEYUP:
	{
		KEYS[wParam] = false;
	}
	break;
	case WM_CLOSE:
	{
		DestroyWindow(hWnd);
	}
	break;
	case WM_DESTROY: //Send A Quit Message
	{
		KillTimer(hWnd, TICK);
		PostQuitMessage(0);
	}
	break;
	default:
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}

	return 0;
}

/* Inicializacion de variables y reserva de espacio en memoria. COLORCAR VARIABLES DE MOV FANTASMAS
*/
void Init()
{
	leer_Per();
	Reproduce("C:\\Users\\dpere\\source\\repos\\LEENS_PIA\\canciones\\INTROPUNTUAJE.mp3");
	posFigura.X = 20;
	posFigura.Y = 430;
	// INICIALIZANDO EL VALOR CON 0
	newP.X = 10;
	newP.Y = 70;

	posEnemigo.X = 600;
	posEnemigo.Y = 430;

	posCoin.X = 135;
	posCoin.Y = 430;

	for (int i = 0; i < 256; i++)
	{
		KEYS[i] = false;
	}
	mirror = false;

	MisColisiones.ScaleX = 2;
	MisColisiones.ScaleY = 2;
	MisColisiones.HitboxScaleX = 2;
	MisColisiones.HitboxScaleY = 2;

	ptrBuffer = new int[ANCHO_VENTANA * ALTO_VENTANA];
	ptrBack = CargaImagen(L"ay2.bmp", &dmnBack); //puntero a la imagen
	ptrSprite = CargaImagen(L"green2.png", &dmnSprite);
	ptrcora = CargaImagen(L"heart.bmp", &dmncora);
	ptrenemigo = CargaImagen(L"enemigo.png", &dmnenemigo);
	ptrlose = CargaImagen(L"lose.png", &dmnlose);
	ptrwin = CargaImagen(L"win.png", &dmnwin);
	ptrcoin = CargaImagen(L"coin.png", &dmncoin);
	ptrpause = CargaImagen(L"pausa.png", &dmnpause);
}

/* Funcion principal. Encargada de hacer el redibujado en pantalla cada intervalo (o "tick") del timer que se haya creado.
@param hWnd. Manejador de la ventana.
*/

void MainRender(HWND hWnd)
{
	
	if (pausa != true) {
			KeysEvents();
			DibujaFondo(ptrBuffer, (int*)ptrBack, dmnBack, mirror);
			if (pantallainicial == false) {
				TranScaleblt(ptrBuffer, (int*)ptrcora,
					5, 5,
					0, 5,
					63, 55,
					800, 64, 1, 1);
				TranScaleblt(ptrBuffer, (int*)ptrcora,
					70, 5,
					0, 5,
					63, 55,
					800, 64, 1, 1);
				TranScaleblt(ptrBuffer, (int*)ptrcora,
					135, 5,
					0, 5,
					63, 55,
					800, 64, 1, 1);
				RenderizaObstaculos();
				RenderizaPersonaje();
				/*RenderizaEnemigo();*/
			}
			if (jumping == true) {
				jump();
			}
			if (obstaculo == true) {
				if (mambo == true) {
					animacion = true;
				}
				else {
					jump2();
				}

				if (explota == false && animacion == true) {

					TranScaleblt(ptrBuffer, (int*)ptrlose,
						0, 0,
						0, 0,
						ANCHO_VENTANA, ALTO_VENTANA,
						800, dmnlose.ANCHO,
						1, 1);
					pantallaperdedor = 1;
				}

			}
			if (newcon >= 2330) {
				if (explota == false) {
					TranScaleblt(ptrBuffer, (int*)ptrwin,
						0, 0,
						0, 0,
						ANCHO_VENTANA, ALTO_VENTANA,
						800, dmnwin.ANCHO,
						1, 1);
					pantallaganador = 1;
				}
				ganar = true;
				pantallainicial = true;
			}
		}
	else {
			KeysEvents();
			DibujaFondo(ptrBuffer, (int*)ptrBack, dmnBack, mirror);
			if (pantallainicial == false) {
				TranScaleblt(ptrBuffer, (int*)ptrcora,
					5, 5,
					0, 5,
					63, 55,
					800, 64, 1, 1);
				TranScaleblt(ptrBuffer, (int*)ptrcora,
					70, 5,
					0, 5,
					63, 55,
					800, 64, 1, 1);
				TranScaleblt(ptrBuffer, (int*)ptrcora,
					135, 5,
					0, 5,
					63, 55,
					800, 64, 1, 1);
				RenderizaPersonaje();

			}
		}
	
	InvalidateRect(hWnd, NULL, FALSE);
	UpdateWindow(hWnd);
}

POSITION setPosition(int x, int y) {
	POSITION p;
	p.X = x;
	p.Y = y;
	return p;
}

void KeysEvents()
{
	if (puntuacionscreen != 1) {
		if (pantallaganador == 1 && yapuestogrr == 0) {
			Cerrar();
			Reproduce("C:\\Users\\dpere\\source\\repos\\LEENS_PIA\\canciones\\GANAR.mp3");
			yapuestogrr = 1;
		}
		if (pantallaperdedor == 1 && yapuestogrr == 0) {
			Cerrar();
			Reproduce("C:\\Users\\dpere\\source\\repos\\LEENS_PIA\\canciones\\GAMEOVER.mp3");
			yapuestogrr = 1;
		}
		if (enemigo == true) {
			if (CheckCollision(MiEnemigo, MiPersonaje)) {
				if (mensaje == 0) {
					obstaculo = true;
				}
			}
		}



		if (obstaculo != true&&pausa==false) {
			if (KEYS[input.W] || KEYS[input.Up] || Gpad->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_Y)
			{
				jumping = true;
				if (mirror == false) {
					if (si == 0 && contajeinc == 0) {
						pc += 5;
					}
					else {
						pt++;
						if (pt == si) {
							si = 0;
							pt = 0;
						}
					}
				}
				else {
					si++;
					contajeinc += 11;
				}

				if (CheckCollision(MiEnemigo, MiPersonaje)) {
					if (mensaje == 0) {
						obstaculo = true;
					}
				}


			}

			if (jumping != true) {
				if (KEYS[input.D] || KEYS[input.Right] || Gpad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT || Gpad->GetState().Gamepad.sThumbLX > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					mirror = false;
					Pasacaminando();

					if (CheckCollision(MiEnemigo, MiPersonaje)) {
						if (mensaje == 0) {
							obstaculo = true;
						}
					}

					if (pi == 0) {
						pc++;
					}
					else {
						pt++;
						if (pt == pi) {
							pc++;
							pi = 0;
							pt = 0;
						}
					}

					movimiento += 1;
					if (movimiento == 3) {
						movimiento = 0;
					}

					if (posFigura.X != 440) {
						posFigura.X += 10;
						newcon += 10;
					}


					//Límite movimiento
					if (movFondo <= 2710) {
						//Movimento fondo
						if (posFigura.X == 440) {
							movFondo += 10;
							newcon += 10;
						}

						__asm {
							mov eax, indMov
							cmp eax, 4
							jna FondoMov
							xor eax, eax
							mov indMov, eax
							FondoMov :
							cld
								mov eax, indMov
								add eax, 1
								mov indMov, eax
						}
					}
					else {
						__asm {
							mov eax, indice
							cmp eax, 15
							jna FondoMov2
							xor eax, eax
							mov indice, eax

							FondoMov2 :

							cld
								mov eax, indice
								add eax, 1
								mov indice, eax
						}
					}
				}

				if (KEYS[input.A] || KEYS[input.Left] || Gpad->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT || Gpad->GetState().Gamepad.sThumbLX < -XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
				{
					pi++;
					Pasacaminando();

					if (CheckCollision(MiEnemigo, MiPersonaje)) {
						if (mensaje == 0) {
							obstaculo = true;
						}
					}

					mirror = true;
					movimiento += 1;
					if (movimiento == 3) {
						movimiento = 0;
					}

					//Codificación del movimiento de la escena
					//Limitar movimiento del fondo
					if (movFondo != 800) {
						//Movimento fondo
						if (posFigura.X == 440) {
							movFondo -= 10;
							newcon -= 10;
						}
						if (posFigura.X == 400 && movFondo == 800) {
							//posFigura.X -= 10;
						}

						__asm {

							mov eax, indMov
							cmp eax, 4
							jna FondoMova
							xor eax, eax
							mov indMov, eax
							FondoMova :
							cld
								mov eax, indMov
								sub eax, 1
								mov indMov, eax
						}
					}
					else {
						__asm {
							mov eax, indice
							cmp eax, 15
							jna FondoMov2a
							xor eax, eax
							mov indice, eax

							FondoMov2a :

							cld
								mov eax, indice
								sub eax, 1
								mov indice, eax
						}
					}
				}
			}
		}

		if (KEYS[input.Enter]|| Gpad->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_START) {
			c++;

			if ((ganar == true || obstaculo == true) && c != 1) {
				pantallainicial = true;
				explota = true;
				movFondo = 3500;
				puntuacionscreen = 1;
				Cerrar();
				Reproduce("C:\\Users\\dpere\\source\\repos\\LEENS_PIA\\canciones\\INTROPUNTUAJE.mp3");

			}
			else {
				movFondo = 800;
				pantallainicial = false;
				empiezajuego = true;
				Cerrar();
				Reproduce("C:\\Users\\dpere\\source\\repos\\LEENS_PIA\\canciones\\JUEGO.mp3");
			}
		}

		if (KEYS[input.P]|| Gpad->GetState().Gamepad.wButtons == XINPUT_GAMEPAD_B) {
			pausa = true;
			picar++;
			Pausa();
			if (picar == 2) {
				pausa = false;
				picar = 0;
				mciSendString("play audio", NULL, 0, 0);
				/*Reproduce("C:\\Users\\dpere\\source\\repos\\xd\\canciones\\JUEGO.mp3");*/
			}
		}
	}
	else {
		if (nombre.size()!=3) {
			if (KEYS[input.A]) {
				nombre += "A";
			}
			if (KEYS[input.B]) {
				nombre += "B";
			}
			if (KEYS[input.C]) {
				nombre += "C";
			}
			if (KEYS[input.D]) {
				nombre += "D";
			}
			if (KEYS[input.E]) {
				nombre += "E";
			}
			if (KEYS[input.F]) {
				nombre += "F";
			}
			if (KEYS[input.G]) {
				nombre += "G";
			}
			if (KEYS[input.H]) {
				nombre += "H";
			}
			if (KEYS[input.I]) {
				nombre += "I";
			}
			if (KEYS[input.J]) {
				nombre += "J";
			}
			if (KEYS[input.K]) {
				nombre += "K";
			}
			if (KEYS[input.L]) {
				nombre += "L";
			}
			if (KEYS[input.M]) {
				nombre += "M";
			}
			if (KEYS[input.N]) {
				nombre += "N";
			}
			if (KEYS[input.O]) {
				nombre += "O";
			}
			if (KEYS[input.P]) {
				nombre += "P";
			}
			if (KEYS[input.Q]) {
				nombre += "Q";
			}
			if (KEYS[input.R]) {
				nombre += "R";
			}
			if (KEYS[input.S]) {
				nombre += "S";
			}
			if (KEYS[input.T]) {
				nombre += "T";
			}
			if (KEYS[input.U]) {
				nombre += "U";
			}
			if (KEYS[input.V]) {
				nombre += "V";
			}
			if (KEYS[input.W]) {
				nombre += "W";
			}
			if (KEYS[input.X]) {
				nombre += "X";
			}
			if (KEYS[input.Y]) {
				nombre += "Y";
			}
			if (KEYS[input.Z]) {
				nombre += "Z";
			}
		}
		else {
			if (KEYS[input.Enter]) {
				acabar = 1;
			}
		}
	}
	
}

/* Funcion para cargar imagenes y obtener un puntero al area de memoria reservada para la misma.
@param rutaImagen.			Nombre o ruta de la imagen a cargar en memoria.
@return unsigned char *.	Direccion base de la imagen.
*/
unsigned char * CargaImagen(WCHAR rutaImagen[], DIMENSION * dmn)
{
	unsigned char * ptrImagen;
	GdiplusStartupInput gdiplusStartupInput;
	ULONG_PTR  gdiplusToken;
	GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

	Bitmap *bitmap = new Bitmap(rutaImagen);
	BitmapData *bitmapData = new BitmapData;

	dmn->ANCHO = bitmap->GetWidth();
	dmn->ALTO = bitmap->GetHeight();

	Rect rect(0, 0, dmn->ANCHO, dmn->ALTO);

	//Reservamos espacio en memoria para la imagen
	bitmap->LockBits(&rect, ImageLockModeRead, PixelFormat32bppRGB, bitmapData);

	//"pixels" es el puntero al area de memoria que ocupa la imagen
	unsigned char* pixels = (unsigned char*)bitmapData->Scan0;

	//"tamaño" lo usaremos para reservar los bytes que necesita la imagen. 
	//Para calcular la cantidad de bytes total necesitamos multiplicamos el area de la imagen * 4. 
	//Se multiplica por 4 debido a que cada pixel ocupa 4 bytes de memoria. Noten el 3er parametro de la funcion LockBits, dos lineas de codigo arriba.
	//PixelFormat32bppARGB -> Specifies that the format is 32 bits per pixel; 8 bits each are used for the alpha, red, green, and blue components.
	//Mas info: https://msdn.microsoft.com/en-us/library/system.drawing.imaging.pixelformat(v=vs.110).aspx
	int tamaño;
	tamaño = dmn->ANCHO * dmn->ALTO * 4;
	//hagamos un try de la reserva de memoria
	try
	{
		ptrImagen = new unsigned char[tamaño];
	}
	catch (...)
	{
		return NULL;
	}

	//Después de este for, ptrImagen contiene la direccion en memoria de la imagen.
	for (int i = 0, j = tamaño; i < j; i++)
	{
		ptrImagen[i] = pixels[i];
	}

	//Es necesario liberar el espacio en memoria, de lo contrario marcaria una excepcion de no hay espacio de memoria suficiente.
	bitmap->UnlockBits(bitmapData);
	delete bitmapData;
	delete bitmap;

	GdiplusShutdown(gdiplusToken);

	return ptrImagen;
}


#pragma region LENS_CODE

void DibujaFondo(int * buffer, int * imagen, DIMENSION dmn, bool mirror) {
	int w = dmn.ANCHO;
	int h = dmn.ALTO;
	int total = w * h;
	int tmp = 0;
	__asm {
		/*mov eax, imagew
		mul BPP
		add esi, eax
		mov eax, spriteW
		sub esi, eax
		mov eax, ANCHO_VENTANA
		mul BPP
		add esi, eax
		mov eax, spriteW


		mov esi, imagen
		mov edi, buffer

		mov eax, w
		mov ebx, h
		mul ebx
		mov ecx, eax
		rep movsd */

		cld
			//Pinta pixel x pixel
			mov esi, imagen
			mov eax, movFondo
			mul BPP
			add esi, eax
			mov edi, buffer
			mov ecx, ALTO_VENTANA

		PintarA :
		push ecx
			mov ecx, ANCHO_VENTANA

		PintarL :
		mov eax, [esi]
			mov[edi], eax
			add edi, BPP
			add esi, BPP
			loop PintarL
			mov eax, 4300 //Tamaño de la imagen
			mul BPP
			add esi, eax
			mov eax, ANCHO_VENTANA
			mul BPP
			sub esi, eax
			pop ecx
			loop PintarA

	}
}

//Funcion para desplegar los sprites en pantalla
// @param *buffer. Puntero al buffer, area de memoria destinada para el despliegue de las imagenes previamente cargadas
// @param *sprite. Puntero a la imagen almacenada en memoria.
// @param dmn. Objeto de tipo DIMENSION que contiene el ancho y alto del sprite a desplegar.
// @param pos. Posicionar el sprite dentro de la pantalla.
void DibujaSprite(int *buffer, int *sprite, DIMENSION dmn, POSITION pos) {
	int x = pos.X; int y = pos.Y;
	int width = dmn.ANCHO;
	int ancho = width / 3;
	int height = dmn.ALTO;
	int tmp = 2;
	int z = 0;
	int anchoc = ancho*tmp;

	//OR eax, 0x000000F0
	if (!escala) {
		if (!mirror) {
			__asm {
				//CAMINA HACIA DELANTE SIN AGRANDAR
				mov esi, sprite
					mov edi, buffer

					mov eax, x
					mul BPP
					add edi, eax
					mov eax, y
					mul BPP
					mul ANCHO_VENTANA
					add edi, eax


					mov eax, movimiento
					mul ancho
					mul BPP
					add esi, eax
					cmp esi, 155
					jne salto
					mov eax, width
					sub eax, ancho
					mul BPP
					sub esi, eax

				salto :


				mov ecx, height
				dib_alto :
				push ecx

					mov ecx, ancho
				dib_ancho :
				mov eax, [esi] //Eliminación de fondo y colores

					cmp colora, 1
					jnz u
					OR eax, 0x000000F0

					cmp colorv, 1
					jnz uu
					OR eax, GREEN
				u :
			uu :


				cmp eax, 0xFFFFFFFF
				jz sss
				cmp eax, 0x00000000
				jz ss2
				mov[edi], eax
			ss2 :
		   sss :
			   add esi, BPP
			   add edi, BPP
			   loop dib_ancho
			   mov eax, ANCHO_VENTANA
			   sub eax, ancho
			   mul BPP
			   add edi, eax
			   mov eax, width
			   sub eax, ancho
			   mul BPP
			   add esi, eax

			   pop ecx
			   loop dib_alto

			}

		}
		else {
			__asm {
				//CAMINA HACIA ATRAS SIN AGRANDAR
				mov esi, sprite
					mov edi, buffer

					mov eax, x
					mul BPP
					add edi, eax
					mov eax, y
					mul BPP
					mul ANCHO_VENTANA
					add edi, eax

					mov eax, movimiento
					mul ancho
					mul BPP
					add esi, eax
					cmp esi, 155
					jne salto2
					mov eax, width
					sub eax, ancho
					mul BPP
					sub esi, eax
				salto2 :


				mov ecx, height
				dib_alto2 :
				push ecx
					mov eax, ancho
					mul BPP
					add esi, eax
					sub esi, BPP
					mov ecx, ancho
				dib_ancho2 :
				mov eax, [esi] //Eliminación de fondo y colores

					cmp colora, 1
					jnz u2
					OR eax, 0x000000F0
					cmp colorv, 1
					jnz uu2
					OR eax, GREEN
				uu2 :
			u2 :
				cmp eax, 0xFFFFFFFF
				jz s
				cmp eax, 0x00000000
				jz s2
				mov[edi], eax
			s2 :
		   s :
			   sub esi, BPP
			   add edi, BPP
			   loop dib_ancho2
			   mov eax, ANCHO_VENTANA
			   sub eax, ancho
			   mul BPP
			   add edi, eax
			   mov eax, width
			   mul BPP
			   add esi, eax
			   add esi, BPP

			   pop ecx
			   loop dib_alto2

			}
		}
	}
}

void DibujaSpriteEne(int* buffer, int* sprite, DIMENSION dmn, POSITION pos) {
	int x = pos.X; int y = pos.Y;
	int width = dmn.ANCHO;
	int ancho = width / 3;
	int height = dmn.ALTO;
	int tmp = 2;
	int z = 0;
	int anchoc = ancho * tmp;

	//OR eax, 0x000000F0
	if (!escala) {
		if (!mirrorEne) {
			__asm {
				//CAMINA HACIA DELANTE SIN AGRANDAR
				mov esi, sprite
				mov edi, buffer

				mov eax, x
				mul BPP
				add edi, eax
				mov eax, y
				mul BPP
				mul ANCHO_VENTANA
				add edi, eax


				mov eax, movimiento
				mul ancho
				mul BPP
				add esi, eax
				cmp esi, 155
				jne salto
				mov eax, width
				sub eax, ancho
				mul BPP
				sub esi, eax

				salto :


				mov ecx, height
					dib_alto :
				push ecx

					mov ecx, ancho
					dib_ancho :
				mov eax, [esi] //Eliminación de fondo y colores

					cmp colora, 1
					jnz u
					OR eax, 0x000000F0

					cmp colorv, 1
					jnz uu
					OR eax, GREEN
					u :
			uu:


				cmp eax, 0xFFFFFFFF
					jz sss
					cmp eax, 0x00000000
					jz ss2
					mov[edi], eax
					ss2 :
			sss:
				add esi, BPP
					add edi, BPP
					loop dib_ancho
					mov eax, ANCHO_VENTANA
					sub eax, ancho
					mul BPP
					add edi, eax
					mov eax, width
					sub eax, ancho
					mul BPP
					add esi, eax

					pop ecx
					loop dib_alto

			}

		}
		else {
			__asm {
				//CAMINA HACIA ATRAS SIN AGRANDAR
				mov esi, sprite
				mov edi, buffer

				mov eax, x
				mul BPP
				add edi, eax
				mov eax, y
				mul BPP
				mul ANCHO_VENTANA
				add edi, eax

				mov eax, movimiento
				mul ancho
				mul BPP
				add esi, eax
				cmp esi, 155
				jne salto2
				mov eax, width
				sub eax, ancho
				mul BPP
				sub esi, eax
				salto2 :


				mov ecx, height
					dib_alto2 :
				push ecx
					mov eax, ancho
					mul BPP
					add esi, eax
					sub esi, BPP
					mov ecx, ancho
					dib_ancho2 :
				mov eax, [esi] //Eliminación de fondo y colores

					cmp colora, 1
					jnz u2
					OR eax, 0x000000F0
					cmp colorv, 1
					jnz uu2
					OR eax, GREEN
					uu2 :
			u2:
				cmp eax, 0xFFFFFFFF
					jz s
					cmp eax, 0x00000000
					jz s2
					mov[edi], eax
					s2 :
			s:
				sub esi, BPP
					add edi, BPP
					loop dib_ancho2
					mov eax, ANCHO_VENTANA
					sub eax, ancho
					mul BPP
					add edi, eax
					mov eax, width
					mul BPP
					add esi, eax
					add esi, BPP

					pop ecx
					loop dib_alto2

			}
		}
	}
}

void TranScaleblt(int* punteroDestino, int* punteroOrigen, int inicioXDestino, int inicioYDestino, int inicioXOrigen, int inicioYOrigen, int ancho, int alto, int anchodefondo, int anchodeorigen, int escalaX, int escalaY) {
	//blt = block transfer, transferencia de bloque de imagen
	int bytesporlineafondo = anchodefondo * 4;
	int bytesporlineaorigen = anchodeorigen * 4;
	int bytesporlineaimagen = ancho * 4;

	__asm {

		mov edi, punteroDestino //movemos la direccion del bitmap a edi, para poder escribir en el
		//Conseguimos el pixel inicial donde empezaremos a dibujar
		mov eax, inicioYDestino
		mul bytesporlineafondo //inicioY * bytesporlineafondo, asi iniciamos en la linea donde queremos 
		mov ebx, eax //ebx contendra el resultado anterior
		mov eax, 4
		mul inicioXDestino //inicioX*4, para asi encontrar la columna donde queremos empezar a dibujar
		add eax, ebx //posicion de columna + posicion de linea
		add edi, eax //Sumamos el desplazamiento anterior al inicio de nuestra imagen para empezar a trabajar en la posicion deseada
		mov esi, punteroOrigen //movemos la direccion de la imagen a dibujar a esi, para poder escribir de ella
		//Conseguimos el pixel inicial DEL CUAL empezaremos a dibujar
		mov eax, inicioYOrigen
		mul bytesporlineaorigen //inicioY * bytesporlineaorigen, asi iniciamos en la linea donde queremos 
		mov ebx, eax //ebx contendra el resultado anterior
		mov eax, 4
		mul inicioXOrigen //inicioX*4, para asi encontrar la columnda de donde queremos empezar a leer
		add eax, ebx //posicion de columna + posicion de linea
		add esi, eax //Sumamos el desplazamiento anterior al inicio de nuestra imagen para empezar a trabajar en la posicion deseada
		mov eax, [esi]
		mov ecx, alto //movemos a ecx la cantidad de lineas que dibujaremos
		lazollenarY :
		push ecx
			mov ecx, escalaY
			escaladoY :
		push ecx //guardamos el valor anterior de ecx, porque lo reemplazaremos en un nuevo ciclo
			mov ecx, ancho //la cantidad de columnas que dibujaremos
			lazollenarX :
		//mueve un pixel de la direccion apuntada por esi a la apuntada por edi, e incrementa esi y edi por 4
		push ecx
			mov ecx, escalaX
			escaladoX :
		cmp eax, [esi]
			je nodibujar
			mov edx, [esi]
			mov[edi], edx
			nodibujar :
		add edi, 4
			loop escaladoX
			add esi, 4
			pop ecx
			loop lazollenarX
			add edi, bytesporlineafondo //le sumamos la cantidad de bytes de la linea del fondo para pasar a la siguiente linea
			push eax
			mov eax, bytesporlineaimagen
			mul escalaX
			sub edi, eax //y retrocedemos una cantidad igual al a su ancho para dibujar desde la posicion X inicial y que no quede escalonado
			pop eax
			sub esi, bytesporlineaimagen
			pop ecx
			loop escaladoY
			//Lo mismo para esi
			add esi, bytesporlineaorigen
			pop ecx //recuperamos el valor del contador del ciclo exterior
			loop lazollenarY
	}
}

void DibujaHitbox(int* ptrBuffer,
	unsigned int color, int anchoWnd, int altoWnd, int HitboxX, int HitboxY, int HitboxAncho, int HitboxAlto, int escalaX, int escalaY)
{
	HitboxAncho = HitboxAncho * escalaX;
	HitboxAlto = HitboxAlto * escalaY;
	__asm {
		mov edi, ptrBuffer

		mov eax, HitboxY
		mul BPP
		mul anchoWnd
		add edi, eax

		mov eax, HitboxX
		mul BPP
		add edi, eax

		mov eax, color

		mov ecx, HitboxAlto
		lazo_alto :
		push ecx
			mov ecx, HitboxAncho
			lazo_ancho :
		mov[edi], eax
			add edi, BPP
			//stosd
			loop lazo_ancho
			push eax
			mov eax, anchoWnd
			sub eax, HitboxAncho
			mul BPP
			add edi, eax
			pop eax
			pop ecx
			loop lazo_alto
	}
}


#pragma endregion

void actualizar_cronometro() {
	while (true) {
		Sleep(1000); // espera 1 segundo
		segundos++;
		if (segundos == 60) {
			segundos = 0;
			minutos++;
		}
		if (minutos == 60) {
			minutos = 0;

		}
	}
}
void dibujar_cronometro(HDC hdc) {
	string tiempo;

	if (minutos > 0)
	{
		tiempo.append(to_string(minutos));
		tiempo.append(":");
		tiempo.append(to_string(segundos));
	}
	else
	{
		tiempo = to_string(segundos);
	}

TextOut(hdc, 700, 20, (LPCSTR)tiempo.c_str(), tiempo.size());
}
void puntuaje(HDC hdc) {
	score = pc;

	/*score = newcon;*/
	string puntos;
	puntos = to_string(score);
	TextOut(hdc, 390, 20, (LPCSTR)puntos.c_str(), puntos.size());
}
void jump() {
	if (jumping == true)
	{
		if (korv == 10)
		{
			if (posFigura.Y < 430)
			{
				if (jumanim == 105)
					jumanim = 122;
				posFigura.Y += 20;

			}
			else
			{
				korv = 0;
				jumping = false;
				jumanim = 105;
			}
		}
		else
		{
			posFigura.Y -= 20;
			korv++;
		}
		if (mirror == true) {
			movFondo -= 5;
			newcon -= 5;
		}
		else {
			movFondo += 5;
			newcon += 5;
		}
	}
	Pasacaminando();
}
void RenderizaObstaculos() {
	if (randomnum2 == false) {
		srand(time(NULL));
		caso2 = rand() % 3;
		randomnum2 = true;
	}
	switch (caso2) {

	case 0: {
	
		if (colision1 == false) {

			TranScaleblt(ptrBuffer, (int*)ptrcoin,
				110, posCoin.Y,
				0, 5,
				63, 55,
				800, 64, 1, 1);
			if (posFigura.X == 110) {
				colision1 = true;
				pc = +50;

			}
		}
	
	
	}
		  break;
	case 1: {
	
	
		if (colision2 == false) {
			TranScaleblt(ptrBuffer, (int*)ptrcoin,
				320, posCoin.Y,
				0, 5,
				63, 55,
				800, 64, 1, 1);

			if (posFigura.X == 320) {
				colision2 = true;
				pc += 50;
			}
		}
	
	
	}
		  break;
	case 2: {
	
	
	
	if (colision1 == false) {

		TranScaleblt(ptrBuffer, (int*)ptrcoin,
			110, posCoin.Y,
			0, 5,
			63, 55,
			800, 64, 1, 1);
		if (posFigura.X == 110) {
			colision1 = true;
			pc = +25;

		}
	}

	if (colision2==false) {
		TranScaleblt(ptrBuffer, (int*)ptrcoin,
			320, posCoin.Y,
			0, 5,
			63, 55,
			800, 64, 1, 1);

		if (posFigura.X == 320) {
			colision2 = true;
			pc += 25;
		}
	}
	
	
	
	}
		  break;
	}




}
void RenderizaPersonaje() {
	MiPersonaje.puntero = ptrBuffer;
	MiPersonaje.anchow = ANCHO_VENTANA;
	MiPersonaje.altow = ALTO_VENTANA;
	MiPersonaje.PosX = posFigura.X;
	MiPersonaje.PosY = posFigura.Y;

	/*DibujaHitbox(MiPersonaje.puntero, MiPersonaje.color, MiPersonaje.anchow, MiPersonaje.altow, MiPersonaje.PosX, MiPersonaje.PosY, MiPersonaje.anchohit,MiPersonaje.altohit,
		MiPersonaje.PosX2, MiPersonaje.PosY2);*/
	DibujaSprite(ptrBuffer, (int*)ptrSprite, dmnSprite, posFigura);
}
void RenderizaEnemigo() {

	MiEnemigo.puntero = ptrBuffer;
	MiEnemigo.anchow = ANCHO_VENTANA;
	MiEnemigo.altow = ALTO_VENTANA;
	MiEnemigo.PosX = posEnemigo.X;
	MiEnemigo.PosY = posEnemigo.Y;

	if (randomnum == false) {
		srand(time(NULL));
		caso = rand() % 3;
		randomnum = true;
	}	

	switch (caso) {

	case 0: {
		if (newcon >= 670 && newcon <= 900) {
			enemigo = true;
			/*DibujaHitbox(MiEnemigo.puntero, MiEnemigo.color, MiEnemigo.anchow, MiEnemigo.altow, MiEnemigo.PosX, MiEnemigo.PosY, MiEnemigo.anchohit, MiEnemigo.altohit,
				MiEnemigo.PosX2, MiEnemigo.PosY2);*/
			DibujaSpriteEne(ptrBuffer, (int*)ptrenemigo, dmnenemigo, posEnemigo);

			if (punto == false) {
				if (posEnemigo.X == 600) {
					punto = true;
					mirrorEne = true;
				}
				else {
					posEnemigo.X += 10;
					mirrorEne = false;
				}
			}
			else {
				posEnemigo.X -= 10;
				if (posEnemigo.X == 300) {
					punto = false;
				}
			}
		}
		 else if (newcon >= 1470 && newcon <= 1655) {
			enemigo = true;
			/*DibujaHitbox(MiEnemigo.puntero, MiEnemigo.color, MiEnemigo.anchow, MiEnemigo.altow, MiEnemigo.PosX, MiEnemigo.PosY, MiEnemigo.anchohit, MiEnemigo.altohit,
				MiEnemigo.PosX2, MiEnemigo.PosY2);*/
			DibujaSpriteEne(ptrBuffer, (int*)ptrenemigo, dmnenemigo, posEnemigo);

			if (punto == false) {
				if (posEnemigo.X == 600) {
					punto = true;
					mirrorEne = true;
				}
				else {
					posEnemigo.X += 10;
					mirrorEne = false;
				}
			}
			else {
				posEnemigo.X -= 10;
				if (posEnemigo.X == 300) {
					punto = false;
				}
			}
		}
		 else { 
			enemigo = false; 
		}
	

	} break;

	case 1: {
		if (newcon >= 670 && newcon <= 900) {
			enemigo = true;
			/*DibujaHitbox(MiEnemigo.puntero, MiEnemigo.color, MiEnemigo.anchow, MiEnemigo.altow, MiEnemigo.PosX, MiEnemigo.PosY, MiEnemigo.anchohit, MiEnemigo.altohit,
				MiEnemigo.PosX2, MiEnemigo.PosY2);*/
			DibujaSpriteEne(ptrBuffer, (int*)ptrenemigo, dmnenemigo, posEnemigo);

			if (punto == false) {
				if (posEnemigo.X == 600) {
					punto = true;
					mirrorEne = true;
				}
				else {
					posEnemigo.X += 10;
					mirrorEne = false;
				}
			}
			else {
				posEnemigo.X -= 10;
				if (posEnemigo.X == 300) {
					punto = false;
				}
			}
		}

		else if (newcon >= 1470 && newcon <= 1655) {
			enemigo = true;
			/*DibujaHitbox(MiEnemigo.puntero, MiEnemigo.color, MiEnemigo.anchow, MiEnemigo.altow, MiEnemigo.PosX, MiEnemigo.PosY, MiEnemigo.anchohit, MiEnemigo.altohit,
				MiEnemigo.PosX2, MiEnemigo.PosY2);*/
			DibujaSpriteEne(ptrBuffer, (int*)ptrenemigo, dmnenemigo, posEnemigo);

			if (punto == false) {
				if (posEnemigo.X == 600) {
					punto = true;
					mirrorEne = true;
				}
				else {
					posEnemigo.X += 10;
					mirrorEne = false;
				}
			}
			else {
				posEnemigo.X -= 10;
				if (posEnemigo.X == 300) {
					punto = false;
				}
			}
		}	

		else if (newcon >= 1895 && newcon <= 2225) {
			enemigo = true;
			/*DibujaHitbox(MiEnemigo.puntero, MiEnemigo.color, MiEnemigo.anchow, MiEnemigo.altow, MiEnemigo.PosX, MiEnemigo.PosY, MiEnemigo.anchohit, MiEnemigo.altohit,
				MiEnemigo.PosX2, MiEnemigo.PosY2);*/
			DibujaSpriteEne(ptrBuffer, (int*)ptrenemigo, dmnenemigo, posEnemigo);

			if (punto == false) {
				if (posEnemigo.X == 600) {
					punto = true;
					mirrorEne = true;
				}
				else {
					posEnemigo.X += 10;
					mirrorEne = false;
				}
			}
			else {
				posEnemigo.X -= 10;
				if (posEnemigo.X == 300) {
					punto = false;
				}
			}
		}

		else {
			enemigo = false;
		}
		

	} break;

	case 2: {
		if (newcon >= 1470 && newcon <= 1655) {
			enemigo = true;
			/*DibujaHitbox(MiEnemigo.puntero, MiEnemigo.color, MiEnemigo.anchow, MiEnemigo.altow, MiEnemigo.PosX, MiEnemigo.PosY, MiEnemigo.anchohit, MiEnemigo.altohit,
				MiEnemigo.PosX2, MiEnemigo.PosY2);*/
			DibujaSpriteEne(ptrBuffer, (int*)ptrenemigo, dmnenemigo, posEnemigo);

			if (punto == false) {
				if (posEnemigo.X == 600) {
					punto = true;
					mirrorEne = true;
				}
				else {
					posEnemigo.X += 10;
					mirrorEne = false;
				}
			}
			else {
				posEnemigo.X -= 10;
				if (posEnemigo.X == 300) {
					punto = false;
				}
			}
		}
		
		else if (newcon >= 1895 && newcon <= 2225) {
			enemigo = true;
			/*DibujaHitbox(MiEnemigo.puntero, MiEnemigo.color, MiEnemigo.anchow, MiEnemigo.altow, MiEnemigo.PosX, MiEnemigo.PosY, MiEnemigo.anchohit, MiEnemigo.altohit,
				MiEnemigo.PosX2, MiEnemigo.PosY2);*/
			DibujaSpriteEne(ptrBuffer, (int*)ptrenemigo, dmnenemigo, posEnemigo);

			if (punto == false) {
				if (posEnemigo.X == 600) {
					punto = true;
					mirrorEne = true;
				}
				else {
					posEnemigo.X += 10;
					mirrorEne = false;
				}
			}
			else {
				posEnemigo.X -= 10;
				if (posEnemigo.X == 300) {
					punto = false;
				}
			}
		}

		else {
			enemigo = false;
		}

	} break;

	}

}
void Pasacaminando() {
	if (jumping != true) {
		if (newcon >= 570 && newcon <= 640) {
			if (mensaje == 0) {
				obstaculo = true;
				/*obstaculo = true;*/
			}
		}

		if (newcon >= 1375 && newcon <= 1430 ) {
			if (mensaje == 0) {
				obstaculo = true;
			}
		}

		if (newcon >= 1776 && newcon <= 1845) {
			if (mensaje == 0) {
				obstaculo = true;
			}
		}

	}
}
void jump2() {
	if (animacion == false) {
		if (korv2 == 10)
		{
			if (posFigura.Y < 500)
			{
				if (jumanim2 == 105)
					jumanim2 = 122;
				posFigura.Y += 20;

			}
			else
			{
				korv2 = 0;
				animacion = true;
				pantallainicial = true;
				jumanim2 = 105;
			}
		}
		else
		{
			posFigura.Y -= 20;
			korv2++;
		}
	}
}
bool CheckCollision(ColisionEnemigo box1, ColisionEnemigo box2) {
	//if (box1.PosX + box1.anchohit >= box2.PosX && // colisión en el eje x
	//	box1.PosX <= box2.PosX + box2.anchohit &&
	//	box1.PosY + box1.altohit >= box2.PosY && // colisión en el eje y
	//	box1.PosY <= box2.PosY + box2.altohit) {
	//	return true;
	//}
	//return false;
	
		if (mambo == false) {
			// Comprobar si las cajas A y B se superponen en el eje x
			bool superposicion_x = (box1.PosX < box2.PosX + box2.anchohit) && (box1.PosX + box1.anchohit > box2.PosX);

			// Si se superponen en el eje x, comprobar si también se superponen en el eje y
			bool superposicion_y = (box1.PosY < box2.PosY + box2.altohit) && (box1.PosY + box1.altohit > box2.PosY);

			if (superposicion_x && superposicion_y) {
				return superposicion_x && superposicion_y;
				mambo = true;
			}
		}
	

}


void Pausa() {
	mciSendString("pause audio", NULL, 0, 0);
}
void Cerrar() {
	mciSendString("close audio", NULL, 0, 0);
}
void Reproduce(const char audio[MAX_PATH]) {
	//HAZ UN BOOL PARA SABER SI PICA 1 O DOS VECES EL BOTON
	//AUDIO ES EL PATH DE LA RUTA DE LA CANCION

	strcat_s(Fullpath, "open \"");
	strcat_s(Fullpath, audio);
	strcat_s(Fullpath, "\" alias audio");
	mciSendString(Fullpath, NULL, 0, 0);
	mciSendString("play audio", NULL, 0, 0);
	strcpy_s(Fullpath, "");
}

void puntuacione(HDC hdc) {
string puntos22;	
int medidas = 0;
puntos22 = to_string(pc);

	string puntos1 = to_string(puntajes[0]);
	string puntos2 = to_string(puntajes[1]);
	string puntos3 = to_string(puntajes[2]);
	string puntos4 = to_string(puntajes[3]);
	string puntos5 = to_string(puntajes[4]);
	
	std::string str1(nombres[0], 5);
	std::string str2(nombres[1], 5);
	std::string str3(nombres[2], 5);
	std::string str4(nombres[3], 5);
	std::string str5(nombres[4], 5);



		TextOut(hdc, 200, 140, (LPCSTR)str1.c_str(), str1.size());
		TextOut(hdc, 500, 140, (LPCSTR)puntos1.c_str(), puntos1.size());

		TextOut(hdc, 200, 195, (LPCSTR)str2.c_str(), str2.size());
		TextOut(hdc, 500, 195, (LPCSTR)puntos2.c_str(), puntos2.size());

		TextOut(hdc, 200, 255, (LPCSTR)str3.c_str(), str3.size());
		TextOut(hdc, 500, 255, (LPCSTR)puntos3.c_str(), puntos3.size());

		TextOut(hdc, 200, 305, (LPCSTR)str4.c_str(), str4.size());
		TextOut(hdc, 500, 305, (LPCSTR)puntos4.c_str(), puntos4.size());

		TextOut(hdc, 200, 360, (LPCSTR)str5.c_str(), str5.size());
		TextOut(hdc, 500, 360, (LPCSTR)puntos5.c_str(), puntos5.size());

		TextOut(hdc, 500, 425, (LPCSTR)puntos22.c_str(), puntos22.size());
		TextOut(hdc, 200, 425, (LPCSTR)nombre.c_str(), nombre.size());
	

	if (acabar == 1) {
		for (int x = 0; x <= 4; x++) {
			if (strcmp(nombres[x], "") == 0) {
				const char* cstr = nombre.c_str();
				strcpy_s(nombres[x],4, cstr);
				puntajes[x] = pc;
				x = 5;
			}
			else {
				medidas++;
			}
		}

		if (medidas == 5) {

			int numeroMenor = puntajes[0];
			for (int i = 1; i < 5; i++) {
				if (puntajes[i] < numeroMenor) {
					numeroMenor = puntajes[i];
				}
			}
			for (int j = 0; j < 5; j++) {
				if (puntajes[j] == numeroMenor) {
					const char* cstr = nombre.c_str();
					strcpy_s(nombres[j], 4, cstr);
					puntajes[j] = pc;
				}
			}

		}

		guardartxt();
		Sleep(500);
		exit(0);
	}

}
void guardartxt() {
	archivo.open("Ranking jugador.txt", ios::out);
	for (int x = 0; x <= 4; x++) {
		archivo<<nombres[x]<<endl;
		archivo<<puntajes[x]<<endl;
		if (strcmp(nombres[x + 1], "") == 0) {
			x = 5;
		}
	}
	archivo.close();
}
void leer_Per() {
	int saltolinea = 0, wp = 0;
	char datodummy[6][6] = {};
	ifstream Archivo;

	Archivo.open("Ranking jugador.txt", ios::out);
	if (Archivo.is_open())
	{
		while (!Archivo.eof())
		{
			while (Archivo>> datodummy[0]) {
				if (saltolinea == 0) {
					strcpy_s(nombres[wp], 4, datodummy[0]);;
					saltolinea++;
				}
				else if (saltolinea == 1) {
					puntajes[wp] = atoi(datodummy[0]);
					saltolinea = 0;	
					wp++;
				}
			}

		}
	}
	Archivo.close();

}
