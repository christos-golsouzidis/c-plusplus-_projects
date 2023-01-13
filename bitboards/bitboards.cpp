// bitboards.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "bitboards.h"

#define MAX_LOADSTRING 100
#define RET_CL 0x400


char hexstr[0x11] = {
	0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,
	0x30,0x30,0x30,0x30,0x30,0x30,0x30,0x30,0};
	
char ihexstr[0x18] = {
	0x30,0x30,0x20,
	0x30,0x30,0x20,
	0x30,0x30,0x20,
	0x30,0x30,0x20,
	0x30,0x30,0x20,
	0x30,0x30,0x20,
	0x30,0x30,0x20,
	0x30,0x30,0};

char bitstr[]= {0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0xD,0xA,
				0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0xD,0xA,
				0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0xD,0xA,
				0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0xD,0xA,
				0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0xD,0xA,
				0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0xD,0xA,
				0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0xD,0xA,
				0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0x30,',',0xD,0xA,
				0};


// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

HWND hwndmain[8];
void gethex(void);
void shift(long);
void clearall(void);




//classes
class SQUARE
{
public:
	long left;
	long top;
	long centx;
	long centy;
	long value;
	long color;
	void setgeometry(long,long);
}bit[8][8];

void SQUARE::setgeometry(long p1, long p2)
{
	left = p1;
	top = p2;
	centx = p1+25;
	centy = p2+25;
}




// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void paintbitboard(HDC);
void lbdn(LPARAM, LPARAM);
void __stdcall zeromem(LPVOID,long);
void __stdcall copymem(LPVOID, LPVOID, long);

void __stdcall zeromem(LPVOID offset_dest, long par_length)
{
	__asm
	{
		xor eax,eax
		mov edi,offset_dest
		mov ecx,par_length
		rep stosb
	}
}

void __stdcall copymem(LPVOID offset_dest, LPVOID offset_src, long par_length)
{
	__asm
	{
		xor eax,eax
		mov edi,offset_dest
		mov esi,offset_src
		mov ecx,par_length
		rep movsb
	}
}


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	long c1,c2;

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_BITBOARDS, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_BITBOARDS));

	c1=0;
	c2=0;
	while(c1<8)
	{
		while(c2<8)
		{
			bit[c1][c2].setgeometry(20+50*c1,60+50*c2);

			c2++;
		}
		c2=0;
		c1++;
	}

	
	hwndmain[1] = CreateWindowA("edit",(LPCSTR)hexstr,
		WS_CHILD|WS_VISIBLE|WS_BORDER,
		20,20,200,30,hwndmain[0],0,hInst,0);
		
	hwndmain[2] = CreateWindowA("edit",(LPCSTR)ihexstr,
		WS_CHILD|WS_VISIBLE|WS_BORDER,
		220,20,200,30,hwndmain[0],0,hInst,0);
	
	hwndmain[3] = CreateWindowA("button","CL",
		WS_CHILD|WS_VISIBLE,
		420,20,30,30,hwndmain[0],(HMENU)RET_CL,hInst,0);
	
	hwndmain[4] = CreateWindowA("edit",(LPCSTR)bitstr,
		WS_CHILD|WS_VISIBLE|WS_BORDER|ES_MULTILINE,
		460,80,300,300,hwndmain[0],0,hInst,0);


	InvalidateRect(hwndmain[0],0,1);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}


void paintbitboard(HDC p1)
{
	HBRUSH blight;
	HBRUSH bdark;	

	long c1=0,c2=0;


#define COLOR_LIGHT	0xffeeee
#define COLOR_DARK	0x804040

	

	blight = CreateSolidBrush(COLOR_LIGHT);
	bdark = CreateSolidBrush(COLOR_DARK);
		
	while (c1<8)
	{
		while (c2<8)
		{		
			if (bit[c1][c2].value == 0)
			{
				SelectObject(p1,blight);
				Rectangle(p1, bit[c1][c2].left, bit[c1][c2].top,
					bit[c1][c2].left+50+1,
					bit[c1][c2].top+50+1);
			}
			else
			{
				SelectObject(p1,bdark);
				Rectangle(p1, bit[c1][c2].left, bit[c1][c2].top,
					bit[c1][c2].left+50+1,
					bit[c1][c2].top+50+1);
			}
			c2++;
		}
		c2 = 0;
		c1++;
	}
	
	c1 = DeleteObject(blight);
	c1 = DeleteObject(bdark);
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_BITBOARDS));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_BITBOARDS);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}


BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   hwndmain[0] = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      100,100,800,580, NULL, NULL, hInstance, NULL);

   if (!hwndmain[0])
   {
      return FALSE;
   }

   ShowWindow(hwndmain[0], nCmdShow);
   UpdateWindow(hwndmain[0]);

   return TRUE;
}


void lbdn(LPARAM x, LPARAM y)
{

	long c1=0,c2=0;

	while(c1<8)
	{
		while(c2<8)
		{
			if(	x>bit[c1][c2].left &&
				y>bit[c1][c2].top &&
				x<bit[c1][c2].left+50 &&
				y<bit[c1][c2].top+50)
			{
				bit[c1][c2].value = bit[c1][c2].value ^ 1;
				return;
			}
			c2++;
		}
		c2=0;
		c1++;
	}

}


void shift(long p1)
{
	long c1=0;
	long c2=0;
	long r1;
	long q1[8];

	switch(p1)
	{
	case 0x25:
		while(c1<8)
		{
			q1[c1] = bit[0][c1].value;
			c2=0;
			while(c2<7)
			{
				bit[c2][c1].value = bit[c2+1][c1].value;
				c2++;
			}
			bit[7][c1].value = q1[c1];
			c1++;
		}
	case 0x27:
		while(c1<8)
		{
			q1[c1] = bit[7][c1].value;
			c2=6;
			while(c2>=0)
			{
				bit[c2+1][c1].value = bit[c2][c1].value;
				c2--;
			}
			bit[0][c1].value = q1[c1];
			c1++;
		}
	case 0x26:
		while(c1<8)
		{
			q1[c1] = bit[c1][0].value;
			c2=0;
			while(c2<7)
			{
				bit[c1][c2].value = bit[c1][c2+1].value;
				c2++;
			}
			bit[c1][7].value = q1[c1];
			c1++;
		}
	case 0x28:
		while(c1<8)
		{
			q1[c1] = bit[c1][7].value;
			c2=6;
			while(c2>=0)
			{
				bit[c1][c2+1].value = bit[c1][c2].value;
				c2--;
			}
			bit[c1][0].value = q1[c1];
			c1++;
		}



		break;

	}

}

void gethex(void)
{
	long c1=0;
	long c2=0;
	long r1;
	
	zeromem(hexstr,sizeof hexstr);
	zeromem(ihexstr,sizeof ihexstr);

	while (c2<8)
	{
		r1 = bit[c1+3][c2].value*8 + 
			bit[c1+2][c2].value*4 + 
			bit[c1+1][c2].value*2 + 
			bit[c1][c2].value;
		if(r1<=9)
			r1+=0x30;
		else
			r1+=0x37;
		hexstr[0xf-c2*2] = r1;
	
		r1 = bit[c1+7][c2].value*8 + 
			bit[c1+6][c2].value*4 + 
			bit[c1+5][c2].value*2 + 
			bit[c1+4][c2].value;
		if(r1<=9)
			r1+=0x30;
		else
			r1+=0x37;
		hexstr[0xe-c2*2] = r1;

		c2++;

	}

	SendMessageA(hwndmain[1],WM_SETTEXT,(WPARAM)sizeof hexstr,(LPARAM)hexstr);
	
	copymem(ihexstr,"                                                ",sizeof ihexstr);
	
	ihexstr[1] = hexstr[0xf];
	ihexstr[0] = hexstr[0xe];
	
	ihexstr[4] = hexstr[0xd];
	ihexstr[3] = hexstr[0xc];
	
	ihexstr[7] = hexstr[0xb];
	ihexstr[6] = hexstr[0xa];
	
	ihexstr[0xa] = hexstr[9];
	ihexstr[0x9] = hexstr[8];

	ihexstr[0xd] = hexstr[7];
	ihexstr[0xc] = hexstr[6];
	
	ihexstr[0x10] = hexstr[5];
	ihexstr[0x0f] = hexstr[4];
	
	ihexstr[0x13] = hexstr[3];
	ihexstr[0x12] = hexstr[2];
	
	ihexstr[0x16] = hexstr[1];
	ihexstr[0x15] = hexstr[0];

	ihexstr[0x17] = 0;

	SendMessageA(hwndmain[2],WM_SETTEXT,(WPARAM)sizeof ihexstr,(LPARAM)ihexstr);
	InvalidateRect(hwndmain[0],0,1);
}


void getbits(void)
{
	int c1=0,c2=0;

	while(c2<8)
	{
		while(c1<8)
		{
			bitstr[0x12*c2+2*c1] = bit[c1][c2].value + 0x30;

			c1++;
		}
		c1=0;
		c2++;
	}

	
	SendMessageA(hwndmain[4],WM_SETTEXT,(WPARAM)sizeof bitstr,(LPARAM)bitstr);


}


void clearall(void)
{
	long c1=0,c2=0;

	while(c1<8)
	{
		while(c2<8)
		{
			bit[c1][c2].value = 0;

			c2++;
		}
		c2=0;
		c1++;
	}

	gethex();
	getbits();
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wparam, LPARAM lparam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wparam);
		wmEvent = HIWORD(wparam);
		// Parse the menu selections:
		switch (wmId)
		{
		case RET_CL:
			clearall();

			break;


		}
		break;
	case WM_KEYFIRST:
		shift(wparam);
		gethex();
		getbits();
		InvalidateRect(hwndmain[0],0,1);
		break;
	case WM_LBUTTONDOWN:
		if (hWnd == hwndmain[0])
		{
			lbdn(LOWORD(lparam),HIWORD(lparam));
			gethex();
			getbits();
			InvalidateRect(hwndmain[0],0,1);

		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwndmain[0],&ps);

		paintbitboard(hdc);

		EndPaint(hwndmain[0],&ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wparam, lparam);
	}
	return 0;
}
