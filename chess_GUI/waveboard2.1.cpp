// waveboard2.1.cpp : Defines the entry point for the application.
//

//#include <ShObjIdl.h>
#include "stdafx.h"
#include "waveboard2.1.h"
#include "variables.cpp"
#include "xfunct.cpp"
#include "waveproc.cpp"
#include <CommCtrl.h>
#include <ShObjIdl.h>


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, sztitle[0], MAX_LOADSTRING);
	LoadString(hInstance, IDC_WAVEBOARD21, szwindowclass[0], MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WAVEBOARD21));

	loadresources();
	engpl[1].id = 1;
	initializeboard(64,64,64);
	resetgame(0);

	SetTimer(hwind[0],0x1a,10,0);

	win_fen();
	win_capture();
	
	ShowWindow(hwind[0],3);
	UpdateWindow(hwind[0]);

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


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	
	copymem(szwindowclass[0],L"0x00",sizeof(L"0x00"));
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WAVEBOARD21));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(4);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WAVEBOARD21);
	wcex.lpszClassName	= szwindowclass[0];
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);
	
	copymem(szwindowclass[1],L"0x10",sizeof(L"0x10"));
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WAVEBOARD21));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(1);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szwindowclass[1];
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);
	
	copymem(szwindowclass[2],L"0x20",sizeof(L"0x20"));
	
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WAVEBOARD21));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(5);
	wcex.lpszMenuName	= 0;
	wcex.lpszClassName	= szwindowclass[2];
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
	RegisterClassEx(&wcex);



	return 0;
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hinst = hInstance; // Store instance handle in our global variable

	hwind[0] = CreateWindow(szwindowclass[0], sztitle[0], WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hwind[0])
	{
		return FALSE;
	}
	ShowWindow(hwind[0], nCmdShow);
	UpdateWindow(hwind[0]);

	return TRUE;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}


void loadresources(void)
{
	handle[WPAWN] = LoadImage(hinst,MAKEINTRESOURCE(0x700),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[BPAWN] = LoadImage(hinst,MAKEINTRESOURCE(0x701),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[_PAWN] = LoadImage(hinst,MAKEINTRESOURCE(0x702),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[WKNIGHT] = LoadImage(hinst,MAKEINTRESOURCE(0x710),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[BKNIGHT] = LoadImage(hinst,MAKEINTRESOURCE(0x711),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[_KNIGHT] = LoadImage(hinst,MAKEINTRESOURCE(0x712),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[WBISHOP] = LoadImage(hinst,MAKEINTRESOURCE(0x720),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[BBISHOP] = LoadImage(hinst,MAKEINTRESOURCE(0x721),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[_BISHOP] = LoadImage(hinst,MAKEINTRESOURCE(0x722),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[WROCK] = LoadImage(hinst,MAKEINTRESOURCE(0x730),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[BROCK] = LoadImage(hinst,MAKEINTRESOURCE(0x731),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[_ROCK] = LoadImage(hinst,MAKEINTRESOURCE(0x732),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[WQUEEN] = LoadImage(hinst,MAKEINTRESOURCE(0x740),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[BQUEEN] = LoadImage(hinst,MAKEINTRESOURCE(0x741),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[_QUEEN] = LoadImage(hinst,MAKEINTRESOURCE(0x742),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[WKING] = LoadImage(hinst,MAKEINTRESOURCE(0x750),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[BKING] = LoadImage(hinst,MAKEINTRESOURCE(0x751),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[_KING] = LoadImage(hinst,MAKEINTRESOURCE(0x752),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[DELIC] =  LoadImage(hinst,MAKEINTRESOURCE(0x760),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[_DELIC] =  LoadImage(hinst,MAKEINTRESOURCE(0x762),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[MOVIC] =  LoadImage(hinst,MAKEINTRESOURCE(0x770),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[_MOVIC] =  LoadImage(hinst,MAKEINTRESOURCE(0x772),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[TIC] =  LoadImage(hinst,MAKEINTRESOURCE(0x780),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
	handle[_TIC] =  LoadImage(hinst,MAKEINTRESOURCE(0x782),IMAGE_BITMAP,0,0,LR_DEFAULTCOLOR);
}


long win_loadenginelist(long p1)
{
	long c1=0;

	if (!engine[0].id_name[0] &&
		!engine[1].id_name[0] &&
		!engine[2].id_name[0] &&
		!engine[3].id_name[0])
		return -1;
	
	zeromem(helpstr,sizeof helpstr);
	if(p1>0)
		copymem(helpstr,L"White`s engine",sizeof L"White`s engine");
	else
		copymem(helpstr,L"Black`s engine",sizeof L"Black`s engine");

	hwind[WIND_ENGLIST] = CreateWindow(szwindowclass[1],helpstr,
		WS_POPUP | WS_CAPTION | WS_VISIBLE,
		620,100,420,240,
		hwind[0],0,hinst,0);
	
	while(c1<4)
	{
		hwind[0x1ff] = CreateWindowA("button",(LPCSTR)engine[c1].id_name,
			WS_CHILD | WS_VISIBLE,
			0,c1*30,420,30,
			hwind[WIND_ENGLIST],(HMENU)(RET_GAME_SETGAME_SELE+c1),hinst,0);
		c1++;
	}


	
	EnableWindow(hwind[WIND_SETGAME],0);
	return 0;
}


long win_new(void)
{
	long c1;

#define	BUTTON_Y_TEXT0 20

#define	ICON_X_DISP 20
#define	ICON_Y_DISP1 120
#define	ICON_Y_DISP2 180
#define	BUTTON_X_DISP 100
	
#define	BUTTON_Y_TEXT1 100

#define	BUTTON_Y_DISP1 110
#define	BUTTON_Y_DISP2 170

#define	BUTTON_Y_TEXT2 260
	
#define	BUTTON_Y_OKCA 650

	
#define	ICON__Y_DISP 280
#define	ICON__X_DISP1 120
#define	ICON__X_DISP2 260

	if(hwind[WIND_SETPOS] || hwind[WIND_SETGAME])
		return 0;
	
	
	hwind[WIND_SETGAME] = CreateWindow(szwindowclass[2],L"New game",
		WS_OVERLAPPED | WS_CAPTION | WS_VISIBLE,
		620,100,420,740,
		hwind[0],0,hinst,0);
	
	hwind[0x1ff] = CreateWindowA("static","___STARTUP POSITION_________________________________",
		WS_CHILD | WS_VISIBLE,
		0,10,430,20,
		hwind[WIND_SETGAME],0,hinst,0);

	hwind[0x1ff] = CreateWindowA("static","Begin from:",
		WS_CHILD | WS_VISIBLE,
		ICON_X_DISP,40,80,40,
		hwind[WIND_SETGAME],0,hinst,0);

	hwind[WIND_SETGAME+1] = CreateWindowA("button","Initial position",
		BS_RADIOBUTTON | BS_FLAT | WS_CHILD | WS_VISIBLE,
		BUTTON_X_DISP,40,180,20,
		hwind[WIND_SETGAME],(HMENU)RET_GAME_SETGAME_INITPOS,hinst,0);

	hwind[WIND_SETGAME+2] = CreateWindowA("button","Current position",
		BS_RADIOBUTTON | BS_FLAT | WS_CHILD | WS_VISIBLE,
		BUTTON_X_DISP,60,180,20,
		hwind[WIND_SETGAME],(HMENU)RET_GAME_SETGAME_CURRPOS,hinst,0);

	SendMessage(hwind[WIND_SETGAME+1],BM_SETCHECK,8,0);
	SendMessage(hwind[WIND_SETGAME+2],BM_SETCHECK,0,0);
	
	hwind[0x1ff] = CreateWindowA("static","___PLAYER SETUP_____________________________________",
		WS_CHILD | WS_VISIBLE,
		0,BUTTON_Y_TEXT1,430,20,
		hwind[WIND_SETGAME],0,hinst,0);
	
	hwind[WIND_SETGAME+3] = CreateWindowA("button","User",
		BS_RADIOBUTTON | BS_FLAT | WS_CHILD | WS_VISIBLE,
		BUTTON_X_DISP,BUTTON_Y_DISP1+20,80,20,
		hwind[WIND_SETGAME],(HMENU)RET_GAME_SETGAME_WU,hinst,0);
	
	zeromem(helpstra,sizeof helpstra);
	if(engine[engpl[0].id].id_name[0])
		copymem(helpstra,engine[engpl[0].id].id_name,sizeof engine[engpl[0].id].id_name);
	else
		copymem(helpstra,"Engine: <Empty>",sizeof "Engine: <Empty>");

	hwind[WIND_SETGAME+4] = CreateWindowA("button",(LPCSTR)helpstra,
		BS_RADIOBUTTON | BS_FLAT | WS_CHILD | WS_VISIBLE,
		BUTTON_X_DISP,BUTTON_Y_DISP1+40,380,20,
		hwind[WIND_SETGAME],(HMENU)RET_GAME_SETGAME_WE,hinst,0);
	
	hwind[WIND_SETGAME+5] = CreateWindow(TEXT("button"),TEXT("User"),
		BS_RADIOBUTTON | BS_FLAT | WS_CHILD | WS_VISIBLE,
		BUTTON_X_DISP,BUTTON_Y_DISP2+20,80,20,
		hwind[WIND_SETGAME],(HMENU)RET_GAME_SETGAME_BU,hinst,0);

	zeromem(helpstra,sizeof helpstra);
	if(engine[engpl[1].id].id_name[0])
		copymem(helpstra,engine[engpl[1].id].id_name,sizeof engine[engpl[1].id].id_name);
	else
		copymem(helpstra,"Engine: <Empty>",sizeof "Engine: <Empty>");

	hwind[WIND_SETGAME+6] = CreateWindowA("button",(LPCSTR)helpstra,
		BS_RADIOBUTTON | BS_FLAT | WS_CHILD | WS_VISIBLE,
		BUTTON_X_DISP,BUTTON_Y_DISP2+40,380,20,
		hwind[WIND_SETGAME],(HMENU)RET_GAME_SETGAME_BE,hinst,0);
	
	hwind[0x1ff] = CreateWindow(TEXT("static"),TEXT("___TIME CONTROL_____________________________________"),
		WS_CHILD | WS_VISIBLE,
		0,BUTTON_Y_TEXT2,430,20,
		hwind[WIND_SETGAME],0,hinst,0);
	
	SendMessage(hwind[WIND_SETGAME+3],BM_SETCHECK,1,0);
	SendMessage(hwind[WIND_SETGAME+4],BM_SETCHECK,0,0);
	SendMessage(hwind[WIND_SETGAME+5],BM_SETCHECK,1,0);
	SendMessage(hwind[WIND_SETGAME+6],BM_SETCHECK,0,0);
	
	hwind[0x1ff] = CreateWindow(TEXT("static"),TEXT("Time (h:mm:ss)"),
		WS_CHILD | WS_VISIBLE,
		ICON_X_DISP,ICON__Y_DISP+60,70,40,
		hwind[WIND_SETGAME],0,hinst,0);
	
	hwind[WIND_SETGAME+7] = CreateWindowA("edit","0",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP1-10,ICON__Y_DISP+60,20,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[WIND_SETGAME+8] = CreateWindowA("edit","30",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP1+20,ICON__Y_DISP+60,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[WIND_SETGAME+9] = CreateWindowA("edit","00",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP1+60,ICON__Y_DISP+60,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[WIND_SETGAME+0xa] = CreateWindowA("edit","0",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP2-10,ICON__Y_DISP+60,20,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[WIND_SETGAME+0xb] = CreateWindowA("edit","30",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP2+20,ICON__Y_DISP+60,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[WIND_SETGAME+0xc] = CreateWindowA("edit","00",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP2+60,ICON__Y_DISP+60,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[0x1ff] = CreateWindow(TEXT("static"),TEXT("Bonus (mm:ss)"),
		WS_CHILD | WS_VISIBLE,
		ICON_X_DISP,ICON__Y_DISP+100,60,40,
		hwind[WIND_SETGAME],0,hinst,0);
	
	hwind[WIND_SETGAME+0xd] = CreateWindowA("edit","00",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP1-10,ICON__Y_DISP+100,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[WIND_SETGAME+0xe] = CreateWindowA("edit","00",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP1+30,ICON__Y_DISP+100,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);

	hwind[WIND_SETGAME+0xf] = CreateWindowA("edit","00",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP2-10,ICON__Y_DISP+100,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[WIND_SETGAME+0x10] = CreateWindowA("edit","00",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		ICON__X_DISP2+30,ICON__Y_DISP+100,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[0x1ff] = CreateWindowA("static","Moves",
		WS_CHILD | WS_VISIBLE,
		ICON_X_DISP,ICON__Y_DISP+140,60,40,
		hwind[WIND_SETGAME],0,hinst,0);
	
	hwind[WIND_SETGAME+0x11] = CreateWindowA("edit","40",
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		(ICON__X_DISP1+ICON__X_DISP2)/2,ICON__Y_DISP+140,40,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);

	hwind[WIND_SETGAME+0x12] = CreateWindowA("button","Time / move (mm:ss)",
		BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | BS_FLAT,
		ICON_X_DISP,ICON__Y_DISP+170,160,20,
		hwind[WIND_SETGAME],(HMENU)RET_GAME_SETGAME_TIME,hinst,0);
	
	hwind[WIND_SETGAME+0x13] = CreateWindowA("edit",0,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		(ICON__X_DISP1+ICON__X_DISP2)/2,ICON__Y_DISP+170,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);
	
	hwind[WIND_SETGAME+0x14] = CreateWindowA("edit",0,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		(ICON__X_DISP1+ICON__X_DISP2)/2+40,ICON__Y_DISP+170,30,20,
		hwind[WIND_SETGAME],(HMENU)0,hinst,0);

	if(SendMessage(hwind[WIND_SETGAME+0x12],BM_GETCHECK,0,0))
	{
		c1 = 7;
		while(c1<0x12)
		{
			EnableWindow(hwind[WIND_SETGAME+c1],0);
			c1++;
		}
		EnableWindow(hwind[WIND_SETGAME+0x13],1);
		EnableWindow(hwind[WIND_SETGAME+0x14],1);
	}
	else
	{
		c1 = 7;
		while(c1<0x12)
		{
			EnableWindow(hwind[WIND_SETGAME+c1],1);
			c1++;
		}
		EnableWindow(hwind[WIND_SETGAME+0x13],0);
		EnableWindow(hwind[WIND_SETGAME+0x14],0);
	}
		
	hwind[0x1E] = CreateWindow(TEXT("button"),TEXT("&OK"),
		WS_CHILD | WS_VISIBLE,
		80,BUTTON_Y_OKCA,80,40,
		hwind[WIND_SETGAME],(HMENU)RET_GAME_SETGAME_OK,hinst,0);
	hwind[0x1F] = CreateWindow(TEXT("button"),TEXT("&Cancel"),
		WS_CHILD | WS_VISIBLE,
		240,BUTTON_Y_OKCA,80,40,
		hwind[WIND_SETGAME],(HMENU)RET_GAME_SETGAME_CA,hinst,0);
		
	setgamesq[0].content = W_K;
	setgamesq[1].content = B_K;

	setgamesq[0].setgeometry(ICON_X_DISP,ICON_Y_DISP1,60);
	setgamesq[1].setgeometry(ICON_X_DISP,ICON_Y_DISP2,60);

	setgamesq[2].content = W_K;
	setgamesq[3].content = B_K;

	setgamesq[2].setgeometry(ICON__X_DISP1,ICON__Y_DISP,60);
	setgamesq[3].setgeometry(ICON__X_DISP2,ICON__Y_DISP,60);


	EnableWindow(hwind[0],0);
	return 1;
}


long win_setpos(void)
{
	long c1 = 0;

#define	X_DIST 20
#define	Y_DIST 60
#define	Y2_DIST 80
	
	if(hwind[WIND_SETPOS] || hwind[WIND_SETGAME])
		return 0;
		
	hwind[WIND_SETPOS] = CreateWindow(szwindowclass[2],L"Setup position",
		WS_OVERLAPPED | WS_VISIBLE,
		620,100,420,500,
		hwind[0],0,hinst,0);

	hwind[WIND_SETPOS+1] = CreateWindow(TEXT("button"),TEXT("&OK"),
		WS_CHILD | WS_VISIBLE,
		80,420,80,40,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_OK,hinst,0);
	hwind[WIND_SETPOS+2] = CreateWindow(TEXT("button"),TEXT("&Cancel"),
		WS_CHILD | WS_VISIBLE,
		240,420,80,40,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_CA,hinst,0);
	
	while(c1<6)
	{
		setpossq[c1].setgeometry (X_DIST-10+c1*sq[0][0].length,0,sq[0][0].length);
		c1++;
	}
	while(c1<12)
	{
		setpossq[c1].setgeometry (X_DIST-10+(c1-6)*sq[0][0].length,60,sq[0][0].length);
		c1++;
	}
	setpossq[0].content = 1;
	setpossq[1].content = 2;
	setpossq[2].content = 4;
	setpossq[3].content = 8;
	setpossq[4].content = 0x10;
	setpossq[5].content = 0x40;
	setpossq[6].content = -1;
	setpossq[7].content = -2;
	setpossq[8].content = -4;
	setpossq[9].content = -8;
	setpossq[10].content = -0x10;
	setpossq[11].content = 0x41;
	
	
	hwind[WIND_SETPOS+3] = CreateWindow(TEXT("button"),TEXT("Input FEN..."),
		BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | BS_FLAT,
		X_DIST+260,90+Y_DIST,120,30,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_FEN,hinst,0);
	hwind[WIND_SETPOS+5] = CreateWindow(TEXT("button"),TEXT("Start position"),
		WS_CHILD | WS_VISIBLE | BS_FLAT,
		X_DIST,90+Y_DIST,120,30,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_ST,hinst,0);
	hwind[WIND_SETPOS+4] = CreateWindow(TEXT("button"),TEXT("Clear board"),
		WS_CHILD | WS_VISIBLE | BS_FLAT,
		X_DIST+130,90+Y_DIST,120,30,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_CL,hinst,0);
	
	hwind[0xff] = CreateWindow(TEXT("static"),TEXT("Number of move:"),
		WS_CHILD | WS_VISIBLE,
		X_DIST,140+Y2_DIST,250,20,
		hwind[WIND_SETPOS],0,hinst,0);
	hwind[0xff] = CreateWindow(TEXT("static"),L"Half-move since last capture or pawn:",
		WS_CHILD | WS_VISIBLE ,
		X_DIST,160+Y2_DIST,250,20,
		hwind[WIND_SETPOS],0,hinst,0);
	
	hwind[WIND_SETPOS+6] = CreateWindowA("edit",helpstra,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		X_DIST+270,140+Y2_DIST,40,20,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_G50,hinst,0);
	hwind[WIND_SETPOS+7] = CreateWindowA("edit",helpstra,
		WS_CHILD | WS_VISIBLE | WS_BORDER,
		X_DIST+270,160+Y2_DIST,40,20,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_GM,hinst,0);
	
	zeromem(helpstra,sizeof helpstra);
	dword2dec(gmoves,helpstra);
	SendMessageA(hwind[WIND_SETPOS+6],WM_SETTEXT,0,(LPARAM)helpstra);

	zeromem(helpstra,sizeof helpstra);
	dword2dec(g50move,helpstra);
	SendMessageA(hwind[WIND_SETPOS+7],WM_SETTEXT,0,(LPARAM)helpstra);

	hwind[0xff] = CreateWindow(TEXT("static"),TEXT("Castle rights:"),
		WS_CHILD | WS_VISIBLE ,
		X_DIST,200+Y2_DIST,180,20,
		hwind[WIND_SETPOS],0,hinst,0);
	hwind[WIND_SETPOS+8] = CreateWindow(TEXT("button"),TEXT("White Kingside"),
		BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | BS_FLAT,
		X_DIST,220+Y2_DIST,180,20,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_WK,hinst,0);
	hwind[WIND_SETPOS+9] = CreateWindow(TEXT("button"),TEXT("White Queenside"),
		BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | BS_FLAT,
		X_DIST,240+Y2_DIST,180,20,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_WQ,hinst,0);
	hwind[WIND_SETPOS+0xa] = CreateWindow(TEXT("button"),TEXT("Black Kingside"),
		BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | BS_FLAT,
		X_DIST,260+Y2_DIST,180,20,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_BK,hinst,0);
	hwind[WIND_SETPOS+0xb] = CreateWindow(TEXT("button"),TEXT("Black Queenside"),
		BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | BS_FLAT,
		X_DIST,280+Y2_DIST,180,20,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_BQ,hinst,0);
	
	if(castle&~FLAG_CSTL_WK)
		SendMessage(hwind[WIND_SETPOS+8],BM_SETCHECK,1,0);
	else
		SendMessage(hwind[WIND_SETPOS+8],BM_SETCHECK,0,0);
	if(castle&~FLAG_CSTL_WQ)
		SendMessage(hwind[WIND_SETPOS+9],BM_SETCHECK,1,0);
	else
		SendMessage(hwind[WIND_SETPOS+9],BM_SETCHECK,0,0);
	if(castle&~FLAG_CSTL_BK)
		SendMessage(hwind[WIND_SETPOS+0xa],BM_SETCHECK,1,0);
	else
		SendMessage(hwind[WIND_SETPOS+0xa],BM_SETCHECK,0,0);
	if(castle&~FLAG_CSTL_BQ)
		SendMessage(hwind[WIND_SETPOS+0xb],BM_SETCHECK,1,0);
	else
		SendMessage(hwind[WIND_SETPOS+0xb],BM_SETCHECK,0,0);
	
	hwind[WIND_SETPOS+0xc] = CreateWindow(TEXT("button"),TEXT("En passant rights"),
		BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | BS_FLAT,
		180+X_DIST,200+Y2_DIST,180,20,
		hwind[WIND_SETPOS],(HMENU)0x649,hinst,0);
	hwind[0xff] = CreateWindow(TEXT("static"),TEXT("File of the pawn:"),
		WS_CHILD | WS_VISIBLE,
		180+X_DIST,220+Y2_DIST,180,20,
		hwind[WIND_SETPOS],0,hinst,0);
	hwind[WIND_SETPOS+0xd] = CreateWindow(TEXT("edit"),0,
		ES_LOWERCASE | WS_CHILD | WS_VISIBLE | WS_BORDER,
		340,220+Y2_DIST,30,20,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_EP,hinst,0);
	
	if(enpass!=-1)
	{
		zeromem(helpstra,sizeof helpstra);
		helpstra[0] = 0x61+enpass;
		SendMessage(hwind[WIND_SETPOS+0xc],BM_SETCHECK,1,0);
		SendMessageA(hwind[WIND_SETPOS+0xd],WM_SETTEXT,0,(LPARAM)helpstra);
	}


	hwind[WIND_SETPOS+0xe] = CreateWindow(TEXT("button"),TEXT("White to move"),
		BS_RADIOBUTTON | WS_CHILD | WS_VISIBLE | BS_FLAT,
		180+X_DIST,260+Y2_DIST,180,20,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_W2M,hinst,0);
	hwind[WIND_SETPOS+0xf] = CreateWindow(TEXT("button"),TEXT("Black to move"),
		BS_RADIOBUTTON | WS_CHILD | WS_VISIBLE | BS_FLAT,
		180+X_DIST,280+Y2_DIST,180,20,
		hwind[WIND_SETPOS],(HMENU)RET_GAME_SETPOS_B2M,hinst,0);
	
	if(turn==1)
	{
		SendMessage(hwind[WIND_SETPOS+0xe],BM_SETCHECK,1,0);
		SendMessage(hwind[WIND_SETPOS+0xf],BM_SETCHECK,0,0);
	}
	else
	{
		SendMessage(hwind[WIND_SETPOS+0xe],BM_SETCHECK,0,0);
		SendMessage(hwind[WIND_SETPOS+0xf],BM_SETCHECK,1,0);
	}
	gamest_flag = GAMESTATE_SETPOS;
	return 1;
}


long win_state(long p1)
{
	long c1=0;
	
	prosq[0].setgeometry(30,10,60);
	prosq[1].setgeometry(90,10,60);
	prosq[2].setgeometry(30,70,60);
	prosq[3].setgeometry(90,70,60);
	
	prosq[0].content = 0;
	prosq[1].content = 0;
	prosq[2].content = 0;
	prosq[3].content = 0;
	
	zeromem(helpstr,0x80);
	if(!p1)
	{
		copymem(helpstr,L"Draw:",sizeof(L"Draw:"));
		prosq[1].content = B_K;
		prosq[3].content = W_K;
		copymem(statestr,"Stalemate",sizeof("Stalemate"));
	}
	else if(p1 == 2)
	{
		copymem(helpstr,L"White wins:",sizeof(L"White wins:"));
		prosq[0].content = B_K;
		prosq[3].content = W_K;
		copymem(statestr,"Checkmate",sizeof("Checkmate"));
	}
	else if(p1 == 1)
	{
		copymem(helpstr,L"Black wins:",sizeof(L"Black wins:"));
		prosq[1].content = B_K;
		prosq[2].content = W_K;
		copymem(statestr,"Checkmate",sizeof("Checkmate"));
	}
	else if(p1 == 50)
	{
		copymem(helpstr,L"Draw:",sizeof(L"Draw:"));
		prosq[1].content = B_K;
		prosq[3].content = W_K;
		copymem(statestr,"Fifty move rule",sizeof("Fifty move rule"));
	}
	else if(p1 == 0x10)
	{
		copymem(helpstr,L"Draw:",sizeof(L"Draw:"));
		prosq[1].content = B_K;
		prosq[3].content = W_K;
		copymem(statestr,"Insufisient material",sizeof("Insufisient material"));
	}
	else if(p1 == 3)
	{
		copymem(helpstr,L"Draw:",sizeof(L"Draw:"));
		prosq[1].content = B_K;
		prosq[3].content = W_K;
		copymem(statestr,"Threefold repetition",sizeof("Threefold repetition"));
	}

	hwind[WIND_STATE] = CreateWindow(szwindowclass[1],(LPCWSTR)helpstr,
		WS_OVERLAPPED | WS_BORDER | WS_VISIBLE,
		sq[3][4].left-sq[0][0].length/2,sq[3][4].top-25,sq[0][0].length*3,sq[0][0].length*3,
		hwind[0],0,hinst,0);
	
	SetTimer(hwind[0],WIND_STATE,2222,0);
	
	return 1;
}


long win_capture(void)
{
	long c1=0,c2=0;
	
	hwind[WIND_CAPTURE] = CreateWindow(szwindowclass[1],L"Delta pieces",
		WS_OVERLAPPED | WS_SIZEBOX | WS_VISIBLE,
		620,100,260,180,
		hwind[0],0,hinst,0);
	
	while(c2 < 8)
	{
		while(c1 < 8)
		{
			cpsq[8*c2+c1].setgeometry (60*c1+5,60*c2+5,60);
			c1++;
		}
		c1=0;
		c2++;
	}
	
	ShowWindow(hwind[WIND_CAPTURE],SW_SHOWNA);
	UpdateWindow(hwind[WIND_CAPTURE]);
	return 0;
}


long win_prom(long p1)
{
	long c1=0;
	
	hwind[WIND_PROM] = CreateWindow(szwindowclass[1],0,
		WS_OVERLAPPED | WS_VISIBLE,
		sq[mspos.dx][mspos.dy].left,sq[mspos.dx][mspos.dy].top,sq[0][0].length * 4,sq[0][0].length+30,
		hwind[0],0,hinst,0);
	while(c1<4)
	{
		prosq[c1].setgeometry (sq[0][0].length * c1, 0, sq[0][0].length);
		c1++;
	}
	if(p1>0)
	{
		prosq[0].content = W_Q;
		prosq[1].content = W_R;
		prosq[2].content = W_B;
		prosq[3].content = W_N;
	}
	else
	{
		prosq[0].content = B_Q;
		prosq[1].content = B_R;
		prosq[2].content = B_B;
		prosq[3].content = B_N;
	}

	//EnableWindow(hwind[0],0);

	return 1;
}


long win_fen(void)
{
	long c1=0;
	
	hwind[WIND_FEN] = CreateWindow(szwindowclass[1],L"FEN",
		WS_OVERLAPPED | WS_SIZEBOX,
		40,650,640,65,
		hwind[0],0,hinst,0);

	pos2fen();
	
	hwind[WIND_FEN+1] = CreateWindow(TEXT("edit"),0,
		ES_READONLY | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER,
		10,3,600,20,
		hwind[WIND_FEN],0,hinst,0);
	
	SendMessageA(hwind[WIND_FEN+1],WM_SETTEXT,(WPARAM)0,(LPARAM)fenout);
	
	ShowWindow(hwind[WIND_FEN],SW_SHOWNA);
	UpdateWindow(hwind[WIND_FEN]);
	return 1;
}


long win_engineinfo(long p1)
{
	char2tchar(helpstr,engine[p1].id_name,2*sizeof engine[p1].id_name);

	hwind[WIND_ENGINFO+2*p1] = CreateWindow(szwindowclass[2],(LPCWSTR)helpstr,
		WS_OVERLAPPED | WS_SIZEBOX,
		40,720,960,240,
		hwind[0],0,hinst,0);

	hwind[WIND_ENGINFO+2*p1+1] = CreateWindowA("edit",0,
		ES_READONLY | ES_MULTILINE | ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER,
		0,0,940,200,
		hwind[WIND_ENGINFO+2*p1],0,hinst,0);
	
	zeromem(engdata,sizeof engdata);
	zeromem(&engf,sizeof engf);
	
	zeromem(&engine[p1].info_cpuload,sizeof engine[p1].info_cpuload);
	zeromem(&engine[p1].info_currmove,sizeof engine[p1].info_currmove);
	zeromem(&engine[p1].info_currmovenumber,sizeof engine[p1].info_currmovenumber);
	zeromem(&engine[p1].info_depth,sizeof engine[p1].info_depth);
	zeromem(&engine[p1].info_hashfull,sizeof engine[p1].info_hashfull);
	zeromem(&engine[p1].info_nodes,sizeof engine[p1].info_nodes);
	zeromem(&engine[p1].info_nps,sizeof engine[p1].info_nps);
	zeromem(&engine[p1].info_pv,sizeof engine[p1].info_pv);
	zeromem(&engine[p1].info_score,sizeof engine[p1].info_score);
	zeromem(&engine[p1].info_seldepth,sizeof engine[p1].info_seldepth);
	zeromem(&engine[p1].info_string,sizeof engine[p1].info_string);
	zeromem(&engine[p1].info_tbhits,sizeof engine[p1].info_tbhits);
	zeromem(&engine[p1].info_time,sizeof engine[p1].info_time);


	SendMessageA(hwind[WIND_ENGINFO+2*p1+1],WM_SETTEXT,sizeof engdata,(LPARAM)engdata);

	ShowWindow(hwind[WIND_ENGINFO+2*p1],SW_SHOWNA);
	UpdateWindow(hwind[WIND_ENGINFO+2*p1]);
	return 1;
}


long win_loadengine(void)
{
	long c1=0;

#define Y_DIST1 100
		
	if(hwind[WIND_SETPOS] || hwind[WIND_SETGAME] || 
		hwind[WIND_LOADENG] || hwind[WIND_STOPGO])
		return 0;
	
	hwind[WIND_LOADENG] = CreateWindow(szwindowclass[2],L"Load engine",
		WS_OVERLAPPED | WS_VISIBLE,
		620,100,420,560,
		hwind[0],0,hinst,0);

	while(c1<4)
	{
		hwind[0x1ff] = CreateWindow(L"static",L"Name:",
			WS_CHILD | WS_VISIBLE,
			X_DIST,c1*Y_DIST1+20,70,20,
			hwind[WIND_LOADENG],0,hinst,0);
		
		zeromem(helpstr,sizeof helpstr);
		zeromem(helpstra,sizeof helpstra);
		copymem(helpstra,engine[c1].id_name,sizeof engine[c1].id_name);
		char2tchar(helpstr,helpstra,sizeof helpstra);

		hwind[WIND_LOADENG+5*c1+4] = CreateWindow(L"static",helpstr,
			WS_CHILD | WS_VISIBLE,
			X_DIST+80,c1*Y_DIST1+20,300,20,
			hwind[WIND_LOADENG],0,hinst,0);

		hwind[0x1ff] = CreateWindow(L"static",L"Path:",
			WS_CHILD | WS_VISIBLE,
			X_DIST,c1*Y_DIST1+50,70,20,
			hwind[WIND_LOADENG],0,hinst,0);

		hwind[WIND_LOADENG+5*c1+1] = CreateWindow(L"edit",(LPCWSTR)enginepath[c1],
			ES_AUTOHSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER,
			X_DIST+80,c1*Y_DIST1+50,300,20,
			hwind[WIND_LOADENG],(HMENU)(RET_ENGINE_LOADENG_PATH+c1),hinst,0);
		
		hwind[WIND_LOADENG+5*c1+3] = CreateWindow(L"button",L"Parameters",
			WS_CHILD | WS_VISIBLE,
			X_DIST+80,c1*Y_DIST1+80,100,20,
			hwind[WIND_LOADENG],(HMENU)(RET_ENGINE_LOADENG_ENGPAR+c1),hinst,0);

		hwind[WIND_LOADENG+5*c1+2] = CreateWindow(L"button",L"Restart",
			WS_CHILD | WS_VISIBLE,
			X_DIST+180,c1*Y_DIST1+80,100,20,
			hwind[WIND_LOADENG],(HMENU)(RET_ENGINE_LOADENG_RESTART+c1),hinst,0);

		hwind[WIND_LOADENG+5*c1+5] = CreateWindow(L"button",L"Unload",
			WS_CHILD | WS_VISIBLE,
			X_DIST+280,c1*Y_DIST1+80,100,20,
			hwind[WIND_LOADENG],(HMENU)(RET_ENGINE_LOADENG_UN+c1),hinst,0);

		
		if(!engine[c1].id_name[0])
			EnableWindow(hwind[WIND_LOADENG+c1*5+2],0);
		if(!engine[c1].id_name[0])
			EnableWindow(hwind[WIND_LOADENG+c1*5+3],0);
		if(!engine[c1].id_name[0])
			EnableWindow(hwind[WIND_LOADENG+c1*5+5],0);

		if(calc_flag[c1])
			SendMessage(hwind[WIND_LOADENG+5*c1+2],BM_SETCHECK,1,0);
		else
			SendMessage(hwind[WIND_LOADENG+5*c1+2],BM_SETCHECK,0,0);

		c1++;
	}
	
	hwind[WIND_LOADENG+0x1e] = CreateWindow(TEXT("button"),TEXT("Return"),
		WS_CHILD | WS_VISIBLE,
		100,480,80,40,
		hwind[WIND_LOADENG],(HMENU)RET_ENGINE_LOADENG_RET,hinst,0);
		
	hwind[WIND_LOADENG+0x1f] = CreateWindow(TEXT("button"),TEXT("Unload all"),
		WS_CHILD | WS_VISIBLE,
		240,480,80,40,
		hwind[WIND_LOADENG],(HMENU)RET_ENGINE_LOADENG_UNA,hinst,0);
		
	EnableWindow(hwind[0],0);

	ShowWindow(hwind[WIND_LOADENG],SW_SHOWNA);
	UpdateWindow(hwind[WIND_LOADENG]);

	return 0;
}


long win_gostop(void)
{
	long c1=0;
	
	if(hwind[WIND_SETPOS] || hwind[WIND_SETGAME] || 
		hwind[WIND_LOADENG] || hwind[WIND_STOPGO])
		return 0;

	hwind[WIND_STOPGO] = CreateWindow(szwindowclass[2],L"Run engine",
		WS_OVERLAPPED | WS_VISIBLE,
		620,100,400,240,
		hwind[0],0,hinst,0);

	while(c1<4)
	{
		
		zeromem(helpstra, sizeof helpstra);
		if(engine[c1].id_name[0])
		{
			copymem(helpstra, engine[c1].id_name, sizeof engine[c1].id_name);
		}
		else
		{
			copymem(helpstra, "<No engine loaded>", sizeof "<No engine loaded>");
		}
		hwind[WIND_STOPGO+1+c1] = CreateWindowA("button",(LPCSTR)helpstra,
			BS_AUTOCHECKBOX | WS_CHILD | WS_VISIBLE | BS_FLAT,
			X_DIST,c1*30+20,400,20,
			hwind[WIND_STOPGO],(HMENU)(RET_ENGINE_LOADENG_ACT+c1),hinst,0);
		if(!calc_flag[c1])
			SendMessage(hwind[WIND_STOPGO+1+c1],BM_SETCHECK,0,0);
		else
			SendMessage(hwind[WIND_STOPGO+1+c1],BM_SETCHECK,1,0);

		c1++;
	}
	

	hwind[WIND_STOPGO+5] = CreateWindow(TEXT("button"),TEXT("Return"),
		WS_CHILD | WS_VISIBLE,
		160,160,80,40,
	hwind[WIND_STOPGO],(HMENU)RET_ANALYSE_GOSTOP_RET,hinst,0);
		
	return 0;
}


long win_analoptions(void)
{






	return 0;
}


long win_timecontrol(void)
{

	setgamesq[1].setgeometry(10,20,60);
	setgamesq[0].setgeometry(10,120,60);
	
	setgamesq[0].content = W_K;
	setgamesq[1].content = B_K;
	
	hwind[WIND_TIMEC] = CreateWindow(szwindowclass[2],L"Time control",
		WS_OVERLAPPED,
		620,300,280,260,
		hwind[0],0,hinst,0);
	
	if(engpl[1].flag)
		copymem(helpstra,engine[engpl[1].id].id_name,sizeof engine[engpl[1].id].id_name);
	else
		copymem(helpstra,"User",sizeof "User");

	hwind[0x1ff] = CreateWindowA("static",(LPCSTR)helpstra,
		WS_CHILD | WS_VISIBLE,
		80,30,200,30,
		hwind[WIND_TIMEC],0,hinst,0);
	hwind[WIND_TIMEC+2] = CreateWindowA("static",(LPCSTR)timec.btime,
		WS_CHILD | WS_VISIBLE,
		80,60,100,30,
		hwind[WIND_TIMEC],0,hinst,0);
	
	if(engpl[0].flag)
		copymem(helpstra,engine[engpl[0].id].id_name,sizeof engine[engpl[0].id].id_name);
	else
		copymem(helpstra,"User",sizeof "User");

	hwind[0x1ff] = CreateWindowA("static",(LPCSTR)helpstra,
		WS_CHILD | WS_VISIBLE,
		80,130,200,30,
		hwind[WIND_TIMEC],0,hinst,0);
	hwind[WIND_TIMEC+1] = CreateWindowA("static",(LPCSTR)timec.wtime,
		WS_CHILD | WS_VISIBLE,
		80,160,100,30,
		hwind[WIND_TIMEC],0,hinst,0);

	ShowWindow(hwind[WIND_TIMEC],SW_SHOWNA);
	SetTimer(hwind[0],0x1b,100,0);
	return 0;
}


long win_enginepar(long p1)
{
	long c1=0;
	long r1=0,r2=0,r0=0;
	
	if(!engine[p1].option_name[c1][0])
		return -1;
	if(hwind[WIND_ENGPARAM])
		return 0;

	zeromem(helpstra,sizeof helpstra);
	zeromem(helpstr,sizeof helpstr);
	dword2dec(p1+1,helpstra);
	helpstra[findnull(helpstra)] = ':';
	helpstra[findnull(helpstra)] = ' ';
	copymem(helpstra+findnull(helpstra),engine[p1].id_name,sizeof engine[p1].id_name);
	
	char2tchar(helpstr,helpstra,0x100);
	
	hwind[WIND_ENGPARAM] = CreateWindow(szwindowclass[2],(LPCWSTR)helpstr,
		WS_OVERLAPPED | WS_VISIBLE | WS_VSCROLL,
		620,100,490,MAX_HEIGHT,
		hwind[0],0,hinst,0);

	while(c1<0x40)
	{
		if(cmpmem("spin",engine[p1].option_type[c1],4))
		{
			hwind[0x1ff] = CreateWindowA("static",engine[p1].option_name[c1],
			WS_CHILD | WS_VISIBLE,
			X_DIST,30*c1+30,200,25,
			hwind[WIND_ENGPARAM],0,hinst,0);

			hwind[WIND_ENGPARAM+c1+1] = CreateWindowA("edit",engine[p1].option_default[c1],
			WS_CHILD | WS_VISIBLE,
			X_DIST+200,30*c1+30,100,25,
			hwind[WIND_ENGPARAM],0,hinst,0);
			
			zeromem(helpstra,sizeof helpstra);
			helpstra[0] = '[';
			copymem(helpstra+1,engine[p1].option_min[c1],sizeof(engine[p1].option_min[c1]));
			helpstra[findnull(helpstra)] = ',';
			copymem(helpstra+findnull(helpstra),engine[p1].option_max[c1],
				sizeof(engine[p1].option_max[c1]));
			helpstra[findnull(helpstra)] = ']';

			hwind[0x1ff] = CreateWindowA("static",helpstra,
			WS_CHILD | WS_VISIBLE,
			X_DIST+360,30*c1+30,100,25,
			hwind[WIND_ENGPARAM],0,hinst,0);

			hwind[WIND_ENGPARAM+c1+1+0x80] = CreateWindow(UPDOWN_CLASS,0,
				WS_CHILD | WS_VISIBLE | 
				UDS_SETBUDDYINT | UDS_HORZ,
				X_DIST+300,30*c1+30,40,25,
				hwind[WIND_ENGPARAM],0,hinst,0);

			SendMessage(hwind[WIND_ENGPARAM+c1+1+0x80],UDM_SETBUDDY,
				(WPARAM)hwind[WIND_ENGPARAM+c1+1],0);

			r1 = char2dword(engine[p1].option_min[c1]);
			r2 = char2dword(engine[p1].option_max[c1]);
			
			SendMessage(hwind[WIND_ENGPARAM+c1+1+0x80],UDM_SETRANGE32,
				(WPARAM)r1,(LPARAM)r2);
		}
		else if(cmpmem("button",engine[p1].option_type[c1],6))
		{
			hwind[0x1ff] = CreateWindowA("button",engine[p1].option_name[c1],
			WS_CHILD | WS_VISIBLE | BS_FLAT,
			X_DIST,30*c1+30,200,25,
			hwind[WIND_ENGPARAM],(HMENU)(RET_ENGINE_PARAMETERS+c1),hinst,0);
		}
		else if(cmpmem("check",engine[p1].option_type[c1],5))
		{
			hwind[WIND_ENGPARAM+c1+1] = CreateWindowA("button",engine[p1].option_name[c1],
			WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX | BS_RIGHTBUTTON | BS_FLAT,
			X_DIST,30*c1+30,200,25,
			hwind[WIND_ENGPARAM],0,hinst,0);
			
			if(cmpmem("true",engine[p1].option_default[c1],4))
				SendMessage(hwind[WIND_ENGPARAM+c1+1],BM_SETCHECK,1,0);
		}
		else if(cmpmem("string",engine[p1].option_type[c1],6))
		{
			hwind[0x1ff] = CreateWindowA("static",engine[p1].option_name[c1],
			WS_CHILD | WS_VISIBLE,
			X_DIST,30*c1+30,200,25,
			hwind[WIND_ENGPARAM],0,hinst,0);
			
			hwind[WIND_ENGPARAM+c1+1] = CreateWindowA("edit",engine[p1].option_default[c1],
			WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL,
			X_DIST+200,30*c1+30,240,25,
			hwind[WIND_ENGPARAM],0,hinst,0);
		}
		else if(cmpmem("combo",engine[p1].option_type[c1],5))
		{
			__asm int 3

		}
		else
			break;
		c1++;
	}
	nep = c1+6;
	if (nep < MIN_NEP) 
		nep = MIN_NEP;
	
	sci.cbSize = sizeof sci;
	sci.nMin = 0;
	sci.nMax = 20;
	sci.nPos = 0;
	sci.fMask = SIF_ALL;

	SetScrollInfo(hwind[WIND_ENGPARAM],SB_VERT,&sci,1);

	hwind[WIND_ENGPARAM+0x7c] = CreateWindow(TEXT("button"),TEXT("Load settings"),
		WS_CHILD | WS_VISIBLE,
		60,30*c1+60,120,40,
		hwind[WIND_ENGPARAM],(HMENU)RET_ENGINE_ENGPARAM_LS,hinst,0);
	
	hwind[WIND_ENGPARAM+0x7d] = CreateWindow(TEXT("button"),TEXT("Save settings"),
		WS_CHILD | WS_VISIBLE,
		60,30*c1+120,120,40,
		hwind[WIND_ENGPARAM],(HMENU)RET_ENGINE_ENGPARAM_SS,hinst,0);
	
	hwind[WIND_ENGPARAM+0x7e] = CreateWindow(TEXT("button"),TEXT("Send to engine"),
		WS_CHILD | WS_VISIBLE,
		280,30*c1+60,120,40,
		hwind[WIND_ENGPARAM],(HMENU)RET_ENGINE_ENGPARAM_SE,hinst,0);
	
	hwind[WIND_ENGPARAM+0x7f] = CreateWindow(TEXT("button"),TEXT("Return"),
		WS_CHILD | WS_VISIBLE,
		280,30*c1+120,120,40,
		hwind[WIND_ENGPARAM],(HMENU)RET_ENGINE_ENGPARAM_RET,hinst,0);
	
	EnableWindow(hwind[WIND_LOADENG],0);
	return 0;
}


void initializeboard(long p1, long p2, long p3)
{
	long c1=0,c2=0,i1,i2;
	i1 = p1;
	i2 = p2;
	
	while (c1<8)
	{
		while (c2<8)
		{
			sq[c1][c2].setgeometry(i1,i2,p3);

			if((c1+c2)&1)
				sq[c1][c2].color = 1;
			else
				sq[c1][c2].color = 0;
			i2+=p3;
			c2++;
		}

		i2 = p2;
		c2 = 0;
		i1+=p3;
		c1++;
	}

}


void flipboard(void)
{
	long c1=0,c2=0;

	if(stacksq.content)
		return;
	
	c1 = 0;
	while (c1<8)
	{
		while (c2<8)
		{
			stosq[c1][c2].content = sq[c1][c2].content;

			c2++;
		}
		c2 = 0;
		c1++;
	}

	c1 = 0;
	while (c1<8)
	{
		while (c2<8)
		{
			sq[7-c1][7-c2].content = stosq[c1][c2].content;

			c2++;
		}
		c2 = 0;
		c1++;
	}

}


void paintwnd(HWND hwnd)
{
	long c1=0;
	HDC hdcmain;
	PAINTSTRUCT ps;


	
	hdcmain = BeginPaint(hwnd,&ps);

	while(c1<0x20)
	{
		hdc[c1] = CreateCompatibleDC(hdcmain);
		
		c1++;
	}
	c1 = 0;
	if(hwnd == hwind[0])
	{
		SelectObject(hdcmain,GetStockObject(SYSTEM_FIXED_FONT));
		paintboard(hdcmain);
		paintpiece(hdcmain);
		paintstack(hdcmain);
		//if(inittable[OPTION_VIEWPLMOVE])
			//paintplmove(hdcmain);
	}
	else if(hwnd == hwind[WIND_SETGAME])
	{
		while(c1 < 4)
		{
			switch(setgamesq[c1].content)
			{
			case W_K:
				SelectObject(hdc[_KING],handle[_KING]);
				BitBlt(hdcmain,
					setgamesq[c1].centx-30,
					setgamesq[c1].centy-30,
					60,60,hdc[_KING],0,0,SRCPAINT);
				SelectObject(hdc[WKING],handle[WKING]);
				BitBlt(hdcmain,
					setgamesq[c1].centx-30,
					setgamesq[c1].centy-30,
					60,60,hdc[WKING],0,0,SRCAND);
				break;
			case B_K:
				SelectObject(hdc[_KING],handle[_KING]);
				BitBlt(hdcmain,
					setgamesq[c1].centx-30,
					setgamesq[c1].centy-30,
					60,60,hdc[_KING],0,0,SRCPAINT);
				SelectObject(hdc[BKING],handle[BKING]);
				BitBlt(hdcmain,
					setgamesq[c1].centx-30,
					setgamesq[c1].centy-30,
					60,60,hdc[BKING],0,0,SRCAND);
				break;
			}
			c1++;
		}
	}
	else if(hwnd == hwind[WIND_TIMEC])
	{
		while(c1 < 2)
		{
			switch(setgamesq[c1].content)
			{
			case W_K:
				SelectObject(hdc[_KING],handle[_KING]);
				BitBlt(hdcmain,
					setgamesq[c1].centx-30,
					setgamesq[c1].centy-30,
					60,60,hdc[_KING],0,0,SRCPAINT);
				SelectObject(hdc[WKING],handle[WKING]);
				BitBlt(hdcmain,
					setgamesq[c1].centx-30,
					setgamesq[c1].centy-30,
					60,60,hdc[WKING],0,0,SRCAND);
				break;
			case B_K:
				SelectObject(hdc[_KING],handle[_KING]);
				BitBlt(hdcmain,
					setgamesq[c1].centx-30,
					setgamesq[c1].centy-30,
					60,60,hdc[_KING],0,0,SRCPAINT);
				SelectObject(hdc[BKING],handle[BKING]);
				BitBlt(hdcmain,
					setgamesq[c1].centx-30,
					setgamesq[c1].centy-30,
					60,60,hdc[BKING],0,0,SRCAND);
				break;
			}
			c1++;
		}
	}
	else if(hwnd == hwind[WIND_STATE])
	{
		paintstboard(hdcmain);
		while(c1 < 4)
		{
			switch(prosq[c1].content)
			{
			case W_K:
				SelectObject(hdc[_KING],handle[_KING]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_KING],0,0,SRCPAINT);
				SelectObject(hdc[WKING],handle[WKING]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[WKING],0,0,SRCAND);
				break;
			case B_K:
				SelectObject(hdc[_KING],handle[_KING]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_KING],0,0,SRCPAINT);
				SelectObject(hdc[BKING],handle[BKING]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[BKING],0,0,SRCAND);
				break;
			}
			c1++;
		}
	}
	else if(hwnd == hwind[WIND_PROM])
	{
		while(c1 < 4)
		{
			switch(prosq[c1].content)
			{
			case W_B:
				
				SelectObject(hdc[_BISHOP],handle[_BISHOP]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_BISHOP],0,0,SRCPAINT);
				SelectObject(hdc[WBISHOP],handle[WBISHOP]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[WBISHOP],0,0,SRCAND);
				break;
			case B_B:
				
				SelectObject(hdc[_BISHOP],handle[_BISHOP]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_BISHOP],0,0,SRCPAINT);
				SelectObject(hdc[BBISHOP],handle[BBISHOP]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[BBISHOP],0,0,SRCAND);
				break;
			case W_Q:
				
				SelectObject(hdc[_QUEEN],handle[_QUEEN]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_QUEEN],0,0,SRCPAINT);
				SelectObject(hdc[WQUEEN],handle[WQUEEN]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[WQUEEN],0,0,SRCAND);
				break;
			case B_Q:
				
				SelectObject(hdc[_QUEEN],handle[_QUEEN]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_QUEEN],0,0,SRCPAINT);
				SelectObject(hdc[BQUEEN],handle[BQUEEN]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[BQUEEN],0,0,SRCAND);
				break;
			case W_N:
				
				SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_KNIGHT],0,0,SRCPAINT);
				SelectObject(hdc[WKNIGHT],handle[WKNIGHT]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[WKNIGHT],0,0,SRCAND);
				break;
			case B_N:
				
				SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_KNIGHT],0,0,SRCPAINT);
				SelectObject(hdc[BKNIGHT],handle[BKNIGHT]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[BKNIGHT],0,0,SRCAND);
				break;
			case W_R:
				
				SelectObject(hdc[_ROCK],handle[_ROCK]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_ROCK],0,0,SRCPAINT);
				SelectObject(hdc[WROCK],handle[WROCK]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[WROCK],0,0,SRCAND);
				break;
			case B_R:
				
				SelectObject(hdc[_ROCK],handle[_ROCK]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[_ROCK],0,0,SRCPAINT);
				SelectObject(hdc[BROCK],handle[BROCK]);
				BitBlt(hdcmain,
					prosq[c1].centx-30,
					prosq[c1].centy-30,
					60,60,hdc[BROCK],0,0,SRCAND);
				break;
			}
			c1++;
		}
	}
	else if(hwnd == hwind[WIND_CAPTURE])
	{
		while(c1 < 0x40)
		{
			switch (cpsq[c1].content)
			{
			case W_P:
				
				SelectObject(hdc[_PAWN],handle[_PAWN]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_PAWN],0,0,SRCPAINT);
				SelectObject(hdc[WPAWN],handle[WPAWN]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[WPAWN],0,0,SRCAND);
				break;
			case B_P:
				
				SelectObject(hdc[_PAWN],handle[_PAWN]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_PAWN],0,0,SRCPAINT);
				SelectObject(hdc[BPAWN],handle[BPAWN]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[BPAWN],0,0,SRCAND);
				break;
			case W_B:
				
				SelectObject(hdc[_BISHOP],handle[_BISHOP]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_BISHOP],0,0,SRCPAINT);
				SelectObject(hdc[WBISHOP],handle[WBISHOP]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[WBISHOP],0,0,SRCAND);
				break;
			case B_B:
				
				SelectObject(hdc[_BISHOP],handle[_BISHOP]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_BISHOP],0,0,SRCPAINT);
				SelectObject(hdc[BBISHOP],handle[BBISHOP]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[BBISHOP],0,0,SRCAND);
				break;
			case W_Q:
				
				SelectObject(hdc[_QUEEN],handle[_QUEEN]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_QUEEN],0,0,SRCPAINT);
				SelectObject(hdc[WQUEEN],handle[WQUEEN]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[WQUEEN],0,0,SRCAND);
				break;
			case B_Q:
				
				SelectObject(hdc[_QUEEN],handle[_QUEEN]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_QUEEN],0,0,SRCPAINT);
				SelectObject(hdc[BQUEEN],handle[BQUEEN]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[BQUEEN],0,0,SRCAND);
				break;
			case W_N:
				
				SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_KNIGHT],0,0,SRCPAINT);
				SelectObject(hdc[WKNIGHT],handle[WKNIGHT]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[WKNIGHT],0,0,SRCAND);
				break;
			case B_N:
				
				SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_KNIGHT],0,0,SRCPAINT);
				SelectObject(hdc[BKNIGHT],handle[BKNIGHT]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[BKNIGHT],0,0,SRCAND);
				break;
			case W_R:
				
				SelectObject(hdc[_ROCK],handle[_ROCK]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_ROCK],0,0,SRCPAINT);
				SelectObject(hdc[WROCK],handle[WROCK]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[WROCK],0,0,SRCAND);
				break;
			case B_R:
				
				SelectObject(hdc[_ROCK],handle[_ROCK]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[_ROCK],0,0,SRCPAINT);
				SelectObject(hdc[BROCK],handle[BROCK]);
				BitBlt(hdcmain,
					cpsq[c1].centx-30,
					cpsq[c1].centy-30,
					60,60,hdc[BROCK],0,0,SRCAND);
				break;
			}
			c1++;
		}
	}
	else if(hwnd == hwind[WIND_SETPOS])
	{
		while(c1 < 12)
		{
			switch (setpossq[c1].content)
			{
			case W_P:
				
				SelectObject(hdc[_PAWN],handle[_PAWN]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_PAWN],0,0,SRCPAINT);
				SelectObject(hdc[WPAWN],handle[WPAWN]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[WPAWN],0,0,SRCAND);
				break;
			case B_P:
				
				SelectObject(hdc[_PAWN],handle[_PAWN]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_PAWN],0,0,SRCPAINT);
				SelectObject(hdc[BPAWN],handle[BPAWN]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[BPAWN],0,0,SRCAND);
				break;
			case W_B:
				
				SelectObject(hdc[_BISHOP],handle[_BISHOP]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_BISHOP],0,0,SRCPAINT);
				SelectObject(hdc[WBISHOP],handle[WBISHOP]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[WBISHOP],0,0,SRCAND);
				break;
			case B_B:
				
				SelectObject(hdc[_BISHOP],handle[_BISHOP]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_BISHOP],0,0,SRCPAINT);
				SelectObject(hdc[BBISHOP],handle[BBISHOP]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[BBISHOP],0,0,SRCAND);
				break;
			case W_Q:
				
				SelectObject(hdc[_QUEEN],handle[_QUEEN]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_QUEEN],0,0,SRCPAINT);
				SelectObject(hdc[WQUEEN],handle[WQUEEN]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[WQUEEN],0,0,SRCAND);
				break;
			case B_Q:
				
				SelectObject(hdc[_QUEEN],handle[_QUEEN]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_QUEEN],0,0,SRCPAINT);
				SelectObject(hdc[BQUEEN],handle[BQUEEN]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[BQUEEN],0,0,SRCAND);
				break;
			case W_R:
				
				SelectObject(hdc[_ROCK],handle[_ROCK]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_ROCK],0,0,SRCPAINT);
				SelectObject(hdc[WROCK],handle[WROCK]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[WROCK],0,0,SRCAND);
				break;
			case B_R:
				
				SelectObject(hdc[_ROCK],handle[_ROCK]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_ROCK],0,0,SRCPAINT);
				SelectObject(hdc[BROCK],handle[BROCK]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[BROCK],0,0,SRCAND);
				break;
			case W_N:
				
				SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_KNIGHT],0,0,SRCPAINT);
				SelectObject(hdc[WKNIGHT],handle[WKNIGHT]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[WKNIGHT],0,0,SRCAND);
				break;
			case B_N:
				
				SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_KNIGHT],0,0,SRCPAINT);
				SelectObject(hdc[BKNIGHT],handle[BKNIGHT]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[BKNIGHT],0,0,SRCAND);
				break;
			case 0x40:
				
				SelectObject(hdc[_MOVIC],handle[_MOVIC]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_MOVIC],0,0,SRCPAINT);
				SelectObject(hdc[MOVIC],handle[MOVIC]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[MOVIC],0,0,SRCAND);
				break;
			case 0x41:
				
				SelectObject(hdc[_DELIC],handle[_DELIC]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[_DELIC],0,0,SRCPAINT);
				SelectObject(hdc[DELIC],handle[DELIC]);
				BitBlt(hdcmain,
					setpossq[c1].centx-30,
					setpossq[c1].centy-30,
					60,60,hdc[DELIC],0,0,SRCAND);
				break;
			}
			c1++;
		}
		c1 = 0;
		while(c1 < 12)
		{
			if(setlsq[c1].content)
			{
				SelectObject(hdc[_TIC],handle[_TIC]);
				BitBlt(hdcmain,
					setlsq[c1].left,
					setlsq[c1].top,
					30,30,hdc[_TIC],0,0,SRCPAINT);
				SelectObject(hdc[TIC],handle[TIC]);
				BitBlt(hdcmain,
					setlsq[c1].left,
					setlsq[c1].top,
					30,30,hdc[TIC],0,0,SRCAND);
			}
			c1++;
		}



	}
	c1 = 0;
	while(c1<0x20)
	{
		DeleteDC(hdc[c1]);
		c1++;
	}
	EndPaint(hwnd,&ps);
}


void paintstboard(HDC p1)
{
	HBRUSH blight;
	HBRUSH bdark;
	long length;

	long c1=0,c2=0;
	length = sq[0][0].length;
	
	blight = CreateSolidBrush(COLOR_LIGHT);
	bdark = CreateSolidBrush(COLOR_DARK);

	SelectObject(p1,blight);
	Rectangle(p1, prosq[0].left, prosq[0].top,
		prosq[0].left+61, prosq[0].top+61);
	Rectangle(p1, prosq[3].left, prosq[3].top,
		prosq[3].left+61, prosq[3].top+61);
	
	SelectObject(p1,bdark);
	Rectangle(p1, prosq[1].left, prosq[1].top,
		prosq[1].left+61, prosq[1].top+61);
	Rectangle(p1, prosq[2].left, prosq[2].top,
		prosq[2].left+61, prosq[2].top+61);
	
	SetBkMode(p1,1);
	c1 = findnull(statestr);
	TextOutA(p1,prosq[2].left,prosq[2].top+65,statestr,c1);
	
	c1 = DeleteObject(blight);
	c1 = DeleteObject(bdark);
}


void paintboard(HDC p1)
{
	HBRUSH blight;
	HBRUSH bdark;
	long length;

	long c1=0,c2=0;
	length = sq[0][0].length;

	while (c1<8)
	{
		while (c2<8)
		{
			rectn(p1,sq[c1][c2].left, sq[c1][c2].top,
				sq[c1][c2].left + length,
				sq[c1][c2].top + length);
			c2++;
		}
		c2 = 0;
		c1++;
	}
	c1=0;
	c2=0;
	blight = CreateSolidBrush(COLOR_LIGHT);
	bdark = CreateSolidBrush(COLOR_DARK);
		
	SelectObject(p1,blight);
	Rectangle(p1, sq[0][0].left-20, sq[0][0].top-20,
		sq[7][7].left+length+20,
		sq[7][7].top+length+20);
	while (c1<8)
	{
		while (c2<8)
		{		
			if (sq[c1][c2].color == 0)
			{
				SelectObject(p1,blight);
				Rectangle(p1, sq[c1][c2].left, sq[c1][c2].top,
					sq[c1][c2].left+length+1,
					sq[c1][c2].top+length+1);
			}
			else
			{
				SelectObject(p1,bdark);
				Rectangle(p1, sq[c1][c2].left, sq[c1][c2].top,
					sq[c1][c2].left+length+1,
					sq[c1][c2].top+length+1);
			}
			c2++;
		}
		c2 = 0;
		c1++;
	}
	
	SetBkMode(p1,1);
	if (boarddir == 1)
	{
		TextOutA(p1,sq[0][0].centx-3,sq[0][0].top+length*8,str_file,1);
		TextOutA(p1,sq[1][0].centx-3,sq[0][0].top+length*8,str_file+1,1);
		TextOutA(p1,sq[2][0].centx-3,sq[0][0].top+length*8,str_file+2,1);
		TextOutA(p1,sq[3][0].centx-3,sq[0][0].top+length*8,str_file+3,1);
		TextOutA(p1,sq[4][0].centx-3,sq[0][0].top+length*8,str_file+4,1);
		TextOutA(p1,sq[5][0].centx-3,sq[0][0].top+length*8,str_file+5,1);
		TextOutA(p1,sq[6][0].centx-3,sq[0][0].top+length*8,str_file+6,1);
		TextOutA(p1,sq[7][0].centx-3,sq[0][0].top+length*8,str_file+7,1);
	
		TextOutA(p1,sq[0][0].left-15,sq[0][0].centy-5,str_rank+7,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][1].centy-5,str_rank+6,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][2].centy-5,str_rank+5,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][3].centy-5,str_rank+4,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][4].centy-5,str_rank+3,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][5].centy-5,str_rank+2,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][6].centy-5,str_rank+1,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][7].centy-5,str_rank,1);
	}
	else
	{
		TextOutA(p1,sq[0][0].centx-3,sq[0][0].top+length*8,str_file+7,1);
		TextOutA(p1,sq[1][0].centx-3,sq[0][0].top+length*8,str_file+6,1);
		TextOutA(p1,sq[2][0].centx-3,sq[0][0].top+length*8,str_file+5,1);
		TextOutA(p1,sq[3][0].centx-3,sq[0][0].top+length*8,str_file+4,1);
		TextOutA(p1,sq[4][0].centx-3,sq[0][0].top+length*8,str_file+3,1);
		TextOutA(p1,sq[5][0].centx-3,sq[0][0].top+length*8,str_file+2,1);
		TextOutA(p1,sq[6][0].centx-3,sq[0][0].top+length*8,str_file+1,1);
		TextOutA(p1,sq[7][0].centx-3,sq[0][0].top+length*8,str_file,1);
	
		TextOutA(p1,sq[0][0].left-15,sq[0][0].centy-5,str_rank,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][1].centy-5,str_rank+1,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][2].centy-5,str_rank+2,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][3].centy-5,str_rank+3,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][4].centy-5,str_rank+4,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][5].centy-5,str_rank+5,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][6].centy-5,str_rank+6,1);
		TextOutA(p1,sq[0][0].left-15,sq[0][7].centy-5,str_rank+7,1);
	}
	
	c1 = DeleteObject(blight);
	c1 = DeleteObject(bdark);
}


void redrawwin(void)
{
	RECT r1;

	if (stacksq.content &&
		(oldr.top-stacksq.top)*(oldr.top-stacksq.top)+(oldr.left-stacksq.left)*(oldr.left-stacksq.left) > 0x4
		)
	{
		///*
		InvalidateRect(hwind[0],&oldr,1);
		r1.top = stacksq.top;
		r1.left = stacksq.left;
		r1.right = stacksq.left+stacksq.length;
		r1.bottom = stacksq.top+stacksq.length;
		InvalidateRect(hwind[0],&r1,1);
		oldr.top = r1.top;
		oldr.left = r1.left;
		oldr.right = r1.right;
		oldr.bottom = r1.bottom;
		//*/
	}

}


void paintpiece(HDC p1)
{
	long c1=0;
	long c2=0;

	while (c1 < 8)
	{
		while (c2 < 8)
		{
			switch (sq[c1][c2].content)
			{
			case W_P:
				
				SelectObject(hdc[_PAWN],handle[_PAWN]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_PAWN],0,0,SRCPAINT);
				SelectObject(hdc[WPAWN],handle[WPAWN]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[WPAWN],0,0,SRCAND);

				break;
			case B_P:
				
				SelectObject(hdc[_PAWN],handle[_PAWN]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_PAWN],0,0,SRCPAINT);
				SelectObject(hdc[BPAWN],handle[BPAWN]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[BPAWN],0,0,SRCAND);

				break;
			case W_B:
				
				SelectObject(hdc[_BISHOP],handle[_BISHOP]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_BISHOP],0,0,SRCPAINT);
				SelectObject(hdc[WBISHOP],handle[WBISHOP]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[WBISHOP],0,0,SRCAND);

				break;
			case B_B:
				
				SelectObject(hdc[_BISHOP],handle[_BISHOP]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_BISHOP],0,0,SRCPAINT);
				SelectObject(hdc[BBISHOP],handle[BBISHOP]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[BBISHOP],0,0,SRCAND);

				break;
			case W_Q:
				
				SelectObject(hdc[_QUEEN],handle[_QUEEN]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_QUEEN],0,0,SRCPAINT);
				SelectObject(hdc[WQUEEN],handle[WQUEEN]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[WQUEEN],0,0,SRCAND);

				break;
			case B_Q:
				
				SelectObject(hdc[_QUEEN],handle[_QUEEN]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_QUEEN],0,0,SRCPAINT);
				SelectObject(hdc[BQUEEN],handle[BQUEEN]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[BQUEEN],0,0,SRCAND);

				break;
			case W_K:
				
				SelectObject(hdc[_KING],handle[_KING]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_KING],0,0,SRCPAINT);
				SelectObject(hdc[WKING],handle[WKING]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[WKING],0,0,SRCAND);

				break;
			case B_K:
				
				SelectObject(hdc[_KING],handle[_KING]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_KING],0,0,SRCPAINT);
				SelectObject(hdc[BKING],handle[BKING]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[BKING],0,0,SRCAND);

				break;
			case W_N:
				
				SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_KNIGHT],0,0,SRCPAINT);
				SelectObject(hdc[WKNIGHT],handle[WKNIGHT]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[WKNIGHT],0,0,SRCAND);

				break;
			case B_N:
				
				SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_KNIGHT],0,0,SRCPAINT);
				SelectObject(hdc[BKNIGHT],handle[BKNIGHT]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[BKNIGHT],0,0,SRCAND);

				break;
			case W_R:
				
				SelectObject(hdc[_ROCK],handle[_ROCK]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_ROCK],0,0,SRCPAINT);
				SelectObject(hdc[WROCK],handle[WROCK]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[WROCK],0,0,SRCAND);

				break;
			case B_R:
				
				SelectObject(hdc[_ROCK],handle[_ROCK]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[_ROCK],0,0,SRCPAINT);
				SelectObject(hdc[BROCK],handle[BROCK]);
				BitBlt(p1,
					sq[c1][c2].centx-30,
					sq[c1][c2].centy-30,
					60,60,hdc[BROCK],0,0,SRCAND);

				break;
			}
			c2++;
		}
		c2 = 0;
		c1++;
	}
}


void paintstack(HDC p1)
{
	
	switch (stacksq.content)
	{

	case W_P:
				
		SelectObject(hdc[_PAWN],handle[_PAWN]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_PAWN],0,0,SRCPAINT);
		SelectObject(hdc[WPAWN],handle[WPAWN]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[WPAWN],0,0,SRCAND);

		break;
	case B_P:
				
		SelectObject(hdc[_PAWN],handle[_PAWN]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_PAWN],0,0,SRCPAINT);
		SelectObject(hdc[BPAWN],handle[BPAWN]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[BPAWN],0,0,SRCAND);

		break;
	case W_B:
				
		SelectObject(hdc[_BISHOP],handle[_BISHOP]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_BISHOP],0,0,SRCPAINT);
		SelectObject(hdc[WBISHOP],handle[WBISHOP]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[WBISHOP],0,0,SRCAND);

		break;
	case B_B:
				
		SelectObject(hdc[_BISHOP],handle[_BISHOP]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_BISHOP],0,0,SRCPAINT);
		SelectObject(hdc[BBISHOP],handle[BBISHOP]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[BBISHOP],0,0,SRCAND);

		break;
	case W_Q:
				
		SelectObject(hdc[_QUEEN],handle[_QUEEN]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_QUEEN],0,0,SRCPAINT);
		SelectObject(hdc[WQUEEN],handle[WQUEEN]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[WQUEEN],0,0,SRCAND);

		break;
	case B_Q:
				
		SelectObject(hdc[_QUEEN],handle[_QUEEN]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_QUEEN],0,0,SRCPAINT);
		SelectObject(hdc[BQUEEN],handle[BQUEEN]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[BQUEEN],0,0,SRCAND);

		break;
	case W_K:
				
		SelectObject(hdc[_KING],handle[_KING]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_KING],0,0,SRCPAINT);
		SelectObject(hdc[WKING],handle[WKING]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[WKING],0,0,SRCAND);

		break;
	case B_K:
				
		SelectObject(hdc[_KING],handle[_KING]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_KING],0,0,SRCPAINT);
		SelectObject(hdc[BKING],handle[BKING]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[BKING],0,0,SRCAND);

		break;
	case W_N:
				
		SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_KNIGHT],0,0,SRCPAINT);
		SelectObject(hdc[WKNIGHT],handle[WKNIGHT]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[WKNIGHT],0,0,SRCAND);

		break;
	case B_N:
				
		SelectObject(hdc[_KNIGHT],handle[_KNIGHT]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_KNIGHT],0,0,SRCPAINT);
		SelectObject(hdc[BKNIGHT],handle[BKNIGHT]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[BKNIGHT],0,0,SRCAND);

		break;
	case W_R:
				
		SelectObject(hdc[_ROCK],handle[_ROCK]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_ROCK],0,0,SRCPAINT);
		SelectObject(hdc[WROCK],handle[WROCK]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[WROCK],0,0,SRCAND);

		break;
	case B_R:
				
		SelectObject(hdc[_ROCK],handle[_ROCK]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[_ROCK],0,0,SRCPAINT);
		SelectObject(hdc[BROCK],handle[BROCK]);
		BitBlt(p1,
			stacksq.centx-30,
			stacksq.centy-30,
			60,60,hdc[BROCK],0,0,SRCAND);

		break;
	}

}


void clearboard(void)
{
	long c1=0;
	long c2=0;

	while(c1<8)
	{
		while(c2<8)
		{
			sq[c1][c2].content = 0;
			c2++;
		}
		c2=0;
		c1++;
	}
	
}


long resetboard(void)
{
	long c1=0;
	long c2=0;

	
	while(c1<8)
	{
		while(c2<8)
		{
			sq[c1][c2].content = 0;
			c2++;
		}
		c2=0;
		c1++;
	}
	c1=0;
	if(boarddir == 1)
	{
		sq[0][0].content = B_R;
		sq[7][0].content = B_R;

		sq[0][7].content = W_R;
		sq[7][7].content = W_R;

		sq[1][0].content = B_N;
		sq[6][0].content = B_N;

		sq[1][7].content = W_N;
		sq[6][7].content = W_N;

		sq[2][0].content = B_B;
		sq[5][0].content = B_B;

		sq[2][7].content = W_B;
		sq[5][7].content = W_B;

		sq[3][0].content = B_Q;
		sq[4][0].content = B_K;

		sq[3][7].content = W_Q;
		sq[4][7].content = W_K;

		while(c1<8)
		{
			sq[c1][1].content = B_P;
			sq[c1][6].content = W_P;
			c1++;
		}
	}
	else
	{
		sq[7][7].content = B_R;
		sq[0][7].content = B_R;

		sq[7][0].content = W_R;
		sq[0][0].content = W_R;

		sq[6][7].content = B_N;
		sq[1][7].content = B_N;

		sq[1][0].content = W_N;
		sq[6][0].content = W_N;

		sq[2][7].content = B_B;
		sq[5][7].content = B_B;

		sq[2][0].content = W_B;
		sq[5][0].content = W_B;

		sq[4][7].content = B_Q;
		sq[3][7].content = B_K;

		sq[4][0].content = W_Q;
		sq[3][0].content = W_K;

		while(c1<8)
		{
			sq[c1][1].content = W_P;
			sq[c1][6].content = B_P;
			c1++;
		}
	}
	turn = 1;
	castle = 0;
	enpass = 0;

	return 0;
}


long resetgame(long par_init)
{
	long c1=0;

	if(!par_init)
	{
		resetboard();
		gamest_flag = GAMESTATE_NORMAL;
		turn = 1;
		castle = FLAG_CSTL_ALL;
		enpass = -1;
		g50move = 0;
		gmoves = 0;
	}
	zeromem(hissq[0][0],sizeof hissq);
	storepos();
	pos2fen();
	SendMessageA(hwind[WIND_FEN+1],WM_SETTEXT,(WPARAM)0,(LPARAM)fenout);
	deltamater();

	while(c1<4)
	{
		ucinewgame(c1);
		c1++;
	}


	InvalidateRect(hwind[WIND_CAPTURE],0,1);
	return 0;
}


long emptyboard(void)
{
	long c1=0;
	long c2=0;

	while(c1<8)
	{
		while(c2<8)
		{
			sq[c1][c2].content = 0;
			c2++;
		}
		c2=0;
		c1++;
	}
	if(boarddir>0)
	{
		sq[4][0].content = B_K;
		sq[4][7].content = W_K;
	}
	else
	{
		sq[3][7].content = B_K;
		sq[3][0].content = W_K;
	}

	return 0;
}


long dragpiece(void)
{
	RECT r1;

	if(mspos.sx < 0 || mspos.sy < 0 || !sq[mspos.sx][mspos.sy].content)
		return 0;
	if(gamest_flag == GAMESTATE_NORMAL)
	{
		if(sq[mspos.sx][mspos.sy].content * turn < 0)
			return 0;
		stacksq.content = sq[mspos.sx][mspos.sy].content;
	}
	if(gamest_flag == GAMESTATE_SETPOS && !setlsq[11].content)
		stacksq.content = sq[mspos.sx][mspos.sy].content;

	if(gamest_flag == GAMESTATE_SETPOS && setlsq[11].content &&
		(sq[mspos.sx][mspos.sy].content == W_K ||
		sq[mspos.sx][mspos.sy].content == B_K))
		goto l_10;

	sq[mspos.sx][mspos.sy].content = 0;

l_10:
	//if(gamest_flag == GAMESTATE_SETPOS && setlsq[11].content)
	//	gamest[0x3fff].storestate(0);

	r1.top = sq[mspos.sx][mspos.sy].top;
	r1.left = sq[mspos.sx][mspos.sy].left;
	r1.right = sq[mspos.sx][mspos.sy].left+stacksq.length;
	r1.bottom = sq[mspos.sx][mspos.sy].top+stacksq.length;
	InvalidateRect(hwind[0],&r1,1);
	r1.top = stacksq.top;
	r1.left = stacksq.left;
	r1.right = stacksq.left+stacksq.length;
	r1.bottom = stacksq.top+stacksq.length;
	InvalidateRect(hwind[0],&r1,1);

	return 0;
}


void movepiece(LPARAM lparam)
{
	long c1 = 0,c2 = 0;

	screenx = LOWORD(lparam);
	screeny = HIWORD(lparam);

	if(!stacksq.content)
	{
		mspos.sx = -1;
		mspos.sy = -1;
		while (c1<8)
		{
			while (c2<8)
			{
				if (screenx >= sq[c1][c2].left &&
					screeny >= sq[c1][c2].top &&
					screenx <= sq[c1][c2].left + sq[c1][c2].length &&
					screeny <= sq[c1][c2].top + sq[c1][c2].length)
				{
					mspos.sx = c1;
					mspos.sy = c2;
				}
				c2++;
			}
			c2 = 0;
			c1++;
		}
	}
	else
	{
		mspos.dx = -1;
		mspos.dy = -1;
		while (c1<8)
		{
			while (c2<8)
			{
				if (screenx >= sq[c1][c2].left &&
					screeny >= sq[c1][c2].top &&
					screenx <= sq[c1][c2].left + sq[c1][c2].length &&
					screeny <= sq[c1][c2].top + sq[c1][c2].length)
				{
					mspos.dx = c1;
					mspos.dy = c2;
				}
				c2++;
			}
			c2 = 0;
			c1++;
		}
	}
	stacksq.setgeometry(screenx-sq[0][0].length/2,screeny-sq[0][0].length/2,
		sq[0][0].length);
}


long droppiece(void)
{
	long r1,r2;

	if(!stacksq.content) return 0;

	switch(gamest_flag)
	{
	case GAMESTATE_NORMAL:
		r1 = isvalidmove(&sq, stacksq.content, &mspos);

		if(!r1)
		{
			sq[mspos.sx][mspos.sy].content = stacksq.content;
			stacksq.content = 0;
			redrawrect(mspos.sx,mspos.sy);
			return 0;
		}
		
		r2 = isvalidcontrol(stacksq.content, &mspos);
		
		if((r2 == 1 && turn == 1) || (r2 == 2 && turn == -1) || r2 == 3)
		{
			sq[mspos.sx][mspos.sy].content = stacksq.content;
			stacksq.content = 0;
			redrawrect(mspos.sx,mspos.sy);
			return 0;
		}
		if(r1&8)
		{
			if( r1 > 0 )
				win_prom(1);
			else
				win_prom(-1);
			
			redrawrect(mspos.dx,mspos.dy);
			return 0x80;
		}
		if(r1 == (RET_CASTLEK))
		{
			if(boarddir>0)
			{
				sq[5][7].content = W_R;
				sq[7][7].content = 0;
				redrawrect(5,7);
				redrawrect(7,7);
			}
			else
			{
				sq[2][0].content = W_R;
				sq[0][0].content = 0;
				redrawrect(2,0);
				redrawrect(0,0);
			}
		}
		else if(r1 == (RET_CASTLEQ))
		{
			if(boarddir>0)
			{
				sq[3][7].content = W_R;
				sq[0][7].content = 0;
				redrawrect(3,7);
				redrawrect(0,7);
			}
			else
			{
				sq[4][0].content = W_R;
				sq[7][0].content = 0;
				redrawrect(4,0);
				redrawrect(7,0);
			}
		}
		else if(r1 == (RET__CASTLEK))
		{
			if(boarddir>0)
			{
				sq[5][0].content = B_R;
				sq[7][0].content = 0;
				redrawrect(5,0);
				redrawrect(7,0);
			}
			else
			{
				sq[2][7].content = B_R;
				sq[0][7].content = 0;
				redrawrect(2,7);
				redrawrect(0,7);
			}
		}
		else if(r1 == (RET__CASTLEQ))
		{
			if(boarddir>0)
			{
				sq[3][0].content = B_R;
				sq[0][0].content = 0;
				redrawrect(3,0);
				redrawrect(0,0);
			}
			else
			{
				sq[4][7].content = B_R;
				sq[7][7].content = 0;
				redrawrect(4,7);
				redrawrect(7,7);
			}
		}
		if (mspos.sx == 4 && 
			mspos.sy == 7 && 
			boarddir == 1)
			castle = castle & (FLAG_CSTL_WK) & (FLAG_CSTL_WQ);
		else if (mspos.sx == 3 && 
			mspos.sy == 0 && 
			boarddir == -1)
			castle = castle & (FLAG_CSTL_WK) & (FLAG_CSTL_WQ);
		if (mspos.sx == 4 && 
			mspos.sy == 0 && 
			boarddir == 1)
			castle = castle & (FLAG_CSTL_BK) & (FLAG_CSTL_BQ);
		else if (mspos.sx == 3 && 
			mspos.sy == 7 && 
			boarddir == -1)
			castle = castle & (FLAG_CSTL_BK) & (FLAG_CSTL_BQ);
		if (((mspos.sx == 7 && mspos.sy == 7) ||
			(mspos.dx == 7 && mspos.dy == 7)) &&
			boarddir == 1)
			castle = castle & (FLAG_CSTL_WK);
		else if (((mspos.sx == 0 && mspos.sy == 0) ||
			(mspos.dx == 0 && mspos.dy == 0)) &&
			boarddir == -1)
			castle = castle & (FLAG_CSTL_WK);
		if (((mspos.sx == 0 && mspos.sy == 7) ||
			(mspos.dx == 0 && mspos.dy == 7)) &&
			boarddir == 1)
			castle = castle & (FLAG_CSTL_WQ);
		else if (((mspos.sx == 7 && mspos.sy == 0) ||
			(mspos.dx == 7 && mspos.dy == 0)) &&
			boarddir == -1)
			castle = castle & (FLAG_CSTL_WQ);
		if (((mspos.sx == 7 && mspos.sy == 0) ||
			(mspos.dx == 7 && mspos.dy == 0)) &&
			boarddir == 1)
			castle = castle & (FLAG_CSTL_BK);
		else if (((mspos.sx == 0 && mspos.sy == 7) ||
			(mspos.dx == 0 && mspos.dy == 7)) &&
			boarddir == -1)
			castle = castle & (FLAG_CSTL_BK);
		if (((mspos.sx == 0 && mspos.sy == 0) ||
			(mspos.dx == 0 && mspos.dy == 0)) &&
			boarddir == 1)
			castle = castle & (FLAG_CSTL_BQ);
		else if (((mspos.sx == 7 && mspos.sy == 7) ||
			(mspos.dx == 7 && mspos.dy == 7)) &&
			boarddir == -1)
			castle = castle & (FLAG_CSTL_BQ);
		if(r1 == (RET_ENPASSANT))
		{
			sq[mspos.dx][mspos.dy+boarddir].content = 0;
			redrawrect(mspos.dx,mspos.dy+boarddir);
		}
		if(r1 == (RET__ENPASSANT))
		{
			sq[mspos.dx][mspos.dy-boarddir].content = 0;
			redrawrect(mspos.dx,mspos.dy-boarddir);
		}
		enpass = -1;
		if(r1 == (RET_DMOVE) || r1 == (RET__DMOVE))
		{
			if(boarddir>0)
				enpass = mspos.dx;
			else
				enpass = 7 - mspos.dx;
		}
		if(turn == 1)
			gmoves++;
		g50move++;
		if(stacksq.content == 1 || stacksq.content == -1 ||
			sq[mspos.dx][mspos.dy].content)
			g50move = 0;

		turn *= -1;
		
		if(mspos.dx>=0 && mspos.dy>=0)
			sq[mspos.dx][mspos.dy].content = stacksq.content;
		
		stacksq.content = 0;
		storepos();

		if(check4legal())
			win_state(r2);
		else if(check4draws())
		{
			__asm MOV DWORD PTR[r1],EAX
			win_state(r1);
		}
		break;
	case GAMESTATE_SETPOS:
		if(mspos.dx>=0 && mspos.dy>=0 &&
			mspos.dx<=7 && mspos.dy<=7)
			sq[mspos.dx][mspos.dy].content = stacksq.content;
		
		stacksq.content = 0;
		break;
	case GAMESTATE_SETPOS+GAMESTATE_SETPOS_HOLD:
		if(stacksq.content >= 0x40)
			stacksq.content = 0;
		if(mspos.dx>=0 && mspos.dy>=0 &&
			mspos.dx<=7 && mspos.dy<=7)
			sq[mspos.dx][mspos.dy].content = stacksq.content;
		break;
	}
	redrawrect(mspos.dx,mspos.dy);
	return 1;
}


void redrawrect(long px, long py)
{
	RECT rc;

	rc.top = sq[px][py].top-5;
	rc.left = sq[px][py].left-5;
	rc.right = sq[px][py].left+stacksq.length+5;
	rc.bottom = sq[px][py].top+stacksq.length+5;
	InvalidateRect(hwind[0],&rc,1);
	rc.top = stacksq.top-5;
	rc.left = stacksq.left-5;
	rc.right = stacksq.left+stacksq.length+5;
	rc.bottom = stacksq.top+stacksq.length+5;
	InvalidateRect(hwind[0],&rc,1);

}


void completemove(LPARAM p1)
{
	long r1;
	RECT rc;

	r1 = getposition(p1,&prosq[0]);

	switch(r1)
	{
	case 0:
		sq[mspos.dx][mspos.dy].content = W_Q;
		break;
	case 1:
		sq[mspos.dx][mspos.dy].content = W_R;
		break;
	case 2:
		sq[mspos.dx][mspos.dy].content = W_B;
		break;
	case 3:
		sq[mspos.dx][mspos.dy].content = W_N;
		break;
	default:
		return;
	}
	if(turn != 1)
		sq[mspos.dx][mspos.dy].content = -sq[mspos.dx][mspos.dy].content;

	DestroyWindow(hwind[WIND_PROM]);
	hwind[WIND_PROM] = 0;

	r1 = isvalidcontrol(sq[mspos.dx][mspos.dy].content, &mspos);
	
	turn *= -1;
	
	stacksq.content = 0;

	if(check4legal())
		win_state(r1);

	rc.top = sq[mspos.dx][mspos.dy].top;
	rc.left = sq[mspos.dx][mspos.dy].left;
	rc.right = sq[mspos.dx][mspos.dy].left+stacksq.length;
	rc.bottom = sq[mspos.dx][mspos.dy].top+stacksq.length;
	InvalidateRect(hwind[0],&rc,1);
	rc.top = stacksq.top;
	rc.left = stacksq.left;
	rc.right = stacksq.left+stacksq.length;
	rc.bottom = stacksq.top+stacksq.length;
	InvalidateRect(hwind[0],&rc,1);
}


long getposition(LPARAM p1,SQUARE* psq)
{
	long c2=0;

	long px = p1 & 0xffff;
	long py = p1 & 0xffff0000;
	
	py /= 0x10000;

	while (c2<0x10)
	{
		if (px >= psq[c2].left &&
			px <= psq[c2].left + psq[c2].length &&
			py >= psq[c2].top &&
			py <= psq[c2].top + psq[c2].length)
		{
			return c2;
		}
		c2++;
	}
	return 0x80;
}


long check4legal(void)
{
	long r1,r2;
	VECTOR virtualpos = {0};
	
	while(virtualpos.sx<8)
	{
		while(virtualpos.sy<8)
		{
			if(sq[virtualpos.sx][virtualpos.sy].content * turn > 0)
			{
				virtualpos.dx = 0;
				virtualpos.dy = 0;
					
				while(virtualpos.dx<8)
				{
					while(virtualpos.dy<8)
					{
						r1 = isvalidmove(&sq, sq[virtualpos.sx][virtualpos.sy].content, &virtualpos);

						if(r1)
						{
							r2 = isvalidcontrol(sq[virtualpos.sx][virtualpos.sy].content, &virtualpos);
							
							if(!(	(r2 == 1 && turn == 1) || 
									(r2 == 2 && turn == -1) || 
									r2 == 3		)
									)
								return 0;

						}
						virtualpos.dy++;
					}
					virtualpos.dy = 0;
					virtualpos.dx++;
				}


			}

			virtualpos.sy++;
		}
		virtualpos.sy = 0;
		virtualpos.sx++;
	}
	return 0x80;
}


long check4draws(void)
{
	long c1=0,c2=0;
	long c3=0;
	long r1 = (-turn)/0x80000000;

	while(c1<8)
	{
		while(c2<8)
		{
			switch(sq[c1][c2].content)
			{
			case W_N:
			case B_N:
			case W_B:
			case B_B:
				c3++;
				break;
			case W_K:
			case B_K:
			case 0:
				break;
			default:
				goto check4draws_01;
			}
			c2++;
		}
		c2=0;
		c1++;
	}
	if(c3<=1)
		return 0x10;
check4draws_01:
	if(g50move >= 100)
		return 50;
check4draws_02:
	c1 = gmoves-1;
	if(c1<3)
		return 0;
	c3 = 0;
	while(c1>=0 && hissq[c1][r1][HIS_G50MOVE]>=0)
	{
		c2 = cmpmem(hissq[gmoves][r1],hissq[c1][r1],0x40);
		c3 += c2;
		if(c3 >= 2)
			return 3;
		c1--;
	}


	return 0;
}


long setpiece(LPARAM p1)
{
	long r1;

	r1 = getposition(p1,&setpossq[0]);

	if(r1 == 5)
	{
		gamest_flag = GAMESTATE_SETPOS;
		stacksq.content = 0;
	}
	else
	{
		stacksq.content = setpossq[r1].content;
		gamest_flag = GAMESTATE_SETPOS+GAMESTATE_SETPOS_HOLD;
	}

	return 0;
}


long isvalidmove(LPVOID par_source, long par_piece, VECTOR * vc)
{
	long r1 = 0;
	long c1,c2;
	SQUARE _sq[8][8];
	
	if(vc->sx == vc->dx && vc->sy == vc->dy)
		return 0;

	copymem(_sq,par_source,sizeof _sq);

	switch(par_piece)
	{
	case W_P:
		if (vc->sy == 1 &&
			vc->dy == 0 &&
			boarddir == 1)
			r1 = RET_PROM;
		else if (vc->sy == 6 &&
			vc->dy == 7 &&
			boarddir == -1)
			r1 = RET_PROM;
		if (_sq[vc->dx][vc->dy].content<0 &&
			(vc->sx == vc->dx - 1 || vc->sx == vc->dx + 1) &&
			vc->sy == vc->dy + boarddir)
		{
			r1 |= RET_CAPTURE;
			return r1;
		}
		else if(!_sq[vc->dx][vc->dy].content &&
				vc->sx == vc->dx &&
				vc->sy == vc->dy + boarddir)
		{
			r1 |= RET_MOVE;
			return r1;
		}
		else if(!_sq[vc->dx][vc->dy].content &&
				vc->sx == vc->dx &&
				vc->sy == 6 &&
				vc->dy == 4 &&
				boarddir == 1)
			return RET_DMOVE;
		else if(!_sq[vc->dx][vc->dy].content &&
				vc->sx == vc->dx &&
				vc->sy == 1 &&
				vc->dy == 3 &&
				boarddir == -1)
			return RET_DMOVE;
		else if(!_sq[vc->dx][vc->dy].content &&
			_sq[vc->dx][vc->dy+1].content == B_P &&
			enpass == (vc->dx) &&
			vc->sy == 3 &&
			vc->dy == 2 &&
			boarddir == 1)
			return RET_ENPASSANT;
		else if(!_sq[vc->dx][vc->dy].content &&
			_sq[vc->dx][vc->dy-1].content == B_P &&
			enpass == (vc->dx) &&
			vc->sy == 4 &&
			vc->dy == 5 &&
			boarddir == -1)
			return RET_ENPASSANT;
		return 0;
	case B_P:
		if (vc->sy == 6 &&
			vc->dy == 7 &&
			boarddir == 1)
			r1 = RET__PROM;
		else if (vc->sy == 1 &&
			vc->dy == 0 &&
			boarddir == -1)
			r1 = RET__PROM;
		if (_sq[vc->dx][vc->dy].content>0 &&
			(vc->sx == vc->dx - 1 || vc->sx == vc->dx + 1) &&
			vc->sy == vc->dy - boarddir)
		{
			r1 |= RET__CAPTURE;
			return r1;
		}
		else if(!_sq[vc->dx][vc->dy].content &&
				vc->sx == vc->dx &&
				vc->sy == vc->dy - boarddir)
		{
			r1 |= RET__MOVE;
			return r1;
		}
		else if(!_sq[vc->dx][vc->dy].content &&
				vc->sx == vc->dx &&
				vc->sy == 1 &&
				vc->dy == 3 &&
				boarddir == 1)
			return RET__DMOVE;
		else if(!_sq[vc->dx][vc->dy].content &&
				vc->sx == vc->dx &&
				vc->sy == 6 &&
				vc->dy == 4 &&
				boarddir == -1)
			return RET__DMOVE;
		else if(!_sq[vc->dx][vc->dy].content &&
			_sq[vc->dx][vc->dy-1].content == W_P &&
			enpass == (vc->dx) &&
			vc->sy == 4 &&
			vc->dy == 5 &&
			boarddir == 1)
			return RET__ENPASSANT;
		else if(!_sq[vc->dx][vc->dy].content &&
			_sq[vc->dx][vc->dy+1].content == W_P &&
			enpass == (vc->dx) &&
			vc->sy == 3 &&
			vc->dy == 2 &&
			boarddir == -1)
			return RET__ENPASSANT;
		return 0;
	case W_K:
		c1 = -1;
		c2 = -1;
		while(c1<2)
		{
			while(c2<2)
			{
				if (vc->sx == vc->dx + c1 &&
					vc->sy == vc->dy + c2)
				{
					if(!_sq[vc->dx][vc->dy].content)
						return RET_MOVE;
					else if(_sq[vc->dx][vc->dy].content < 0)
						return RET_CAPTURE;
					else
						return 0;
				}
				c2++;
			}
			c2 = -1;
			c1++;
		}
		if (vc->sy == 7 && vc->dy == 7 && vc->sx == 4 && vc->dx == 6 &&
			castle & ~FLAG_CSTL_WK &&
			_sq[7][7].content == W_R &&
			!_sq[5][7].content &&
			!_sq[6][7].content &&
			boarddir == 1)
			return RET_CASTLEK;
		else if (vc->sy == 7 && vc->dy == 7 && vc->sx == 4 && vc->dx == 2 &&
			castle & ~FLAG_CSTL_WQ &&
			_sq[0][7].content == W_R &&
			!_sq[3][7].content &&
			!_sq[2][7].content &&
			!_sq[1][7].content &&
			boarddir == 1)
			return RET_CASTLEQ;
		else if (vc->sy == 0 && vc->dy == 0 && vc->sx == 3 && vc->dx == 1 &&
			castle & ~FLAG_CSTL_WK &&
			_sq[0][0].content == W_R &&
			!_sq[2][0].content &&
			!_sq[1][0].content &&
			boarddir == -1)
			return RET_CASTLEK;
		else if (vc->sy == 0 && vc->dy == 0 && vc->sx == 3 && vc->dx == 5 &&
			castle & ~FLAG_CSTL_WQ &&
			_sq[7][0].content == W_R &&
			!_sq[4][0].content &&
			!_sq[5][0].content &&
			!_sq[6][0].content &&
			boarddir == -1)
			return RET_CASTLEQ;
		break;
	case B_K:
		c1 = -1;
		c2 = -1;
		while(c1<2)
		{
			while(c2<2)
			{
				if (vc->sx == vc->dx + c1 &&
					vc->sy == vc->dy + c2)
				{
					if(!_sq[vc->dx][vc->dy].content)
						return RET__MOVE;
					else if(_sq[vc->dx][vc->dy].content > 0)
						return RET__CAPTURE;
					else
						return 0;
				}
				c2++;
			}
			c2 = -1;
			c1++;
		}
		if (vc->sy == 0 && vc->dy == 0 && vc->sx == 4 && vc->dx == 6 &&
			castle & ~FLAG_CSTL_BK &&
			_sq[7][0].content == B_R &&
			!_sq[5][0].content &&
			!_sq[6][0].content &&
			boarddir == 1)
			return RET__CASTLEK;
		else if (vc->sy == 0 && vc->dy == 0 && vc->sx == 4 && vc->dx == 2 &&
			castle & ~FLAG_CSTL_BQ &&
			_sq[0][0].content == B_R &&
			!_sq[3][0].content &&
			!_sq[2][0].content &&
			!_sq[1][0].content &&
			boarddir == 1)
			return RET__CASTLEQ;
		else if (vc->sy == 7 && vc->dy == 7 && vc->sx == 3 && vc->dx == 1 &&
			castle & ~FLAG_CSTL_BK &&
			_sq[0][7].content == B_R &&
			!_sq[2][7].content &&
			!_sq[1][7].content &&
			boarddir == -1)
			return RET__CASTLEK;
		else if (vc->sy == 7 && vc->dy == 7 && vc->sx == 3 && vc->dx == 5 &&
			castle & ~FLAG_CSTL_BQ &&
			_sq[7][7].content == B_R &&
			!_sq[4][7].content &&
			!_sq[5][7].content &&
			!_sq[6][7].content &&
			boarddir == -1)
			return RET__CASTLEQ;
		break;
	case W_N:
		c1 = -2;
		c2 = -2;
		while(c1<3)
		{
			while(c2<3)
			{
				if (c1 && c2 && c1!=c2 && c1!=-c2 && 
					vc->sx == vc->dx + c1 &&
					vc->sy == vc->dy + c2)
				{
					if(!_sq[vc->dx][vc->dy].content)
						return RET_MOVE;
					else if(_sq[vc->dx][vc->dy].content < 0)
						return RET_CAPTURE;
					else
						return 0;
				}
				c2++;
			}
			c2 = -2;
			c1++;
		}
		break;
	case B_N:
		c1 = -2;
		c2 = -2;
		while(c1<3)
		{
			while(c2<3)
			{
				if (c1 && c2 && c1!=c2 && c1!=-c2 && 
					vc->sx == vc->dx + c1 &&
					vc->sy == vc->dy + c2)
				{
					if(!_sq[vc->dx][vc->dy].content)
						return RET__MOVE;
					else if(_sq[vc->dx][vc->dy].content > 0)
						return RET__CAPTURE;
					else
						return 0;
				}
				c2++;
			}
			c2 = -2;
			c1++;
		}
		break;
	case W_B:
		c2 = 1;
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		break;
	case B_B:
		c2 = 1;
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		break;
	case W_R:
		c2 = 1;
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		break;
	case B_R:
		c2 = 1;
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		break;
	case W_Q:
		c2 = 1;
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET_MOVE;
				else if(_sq[vc->dx][vc->dy].content < 0)
					return RET_CAPTURE;
				return 0;
			}
			c1++;
		}
		break;
	case B_Q:
		c2 = 1;
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx-c1 && vc->sy == vc->dy)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx-c2][vc->dy].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx && vc->sy == vc->dy-c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx][vc->dy-c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx+c1 && vc->sy == vc->dy)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx+c2][vc->dy].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		c1 = 1;
		while(c1<8)
		{
			if(vc->sx == vc->dx && vc->sy == vc->dy+c1)
			{
				while(c2<c1)
				{
					if(_sq[vc->dx][vc->dy+c2].content)
						return 0;

					c2++;
				}
				if(!_sq[vc->dx][vc->dy].content)
					return RET__MOVE;
				else if(_sq[vc->dx][vc->dy].content > 0)
					return RET__CAPTURE;
				return 0;
			}
			c1++;
		}
		break;





	default:
		return 0;
	}
	return r1;
}


long isvalidcontrol(long p1, VECTOR * vc)
{
	long r1=0;
	long c1=0,c2=0;
	long wkx,bkx,wky,bky;
	SQUARE tsq[8][8];

	
	while(c1<8)
	{
		while(c2<8)
		{
			tsq[c1][c2].content = sq[c1][c2].content;
			c2++;
		}
		c2 = 0;
		c1++;
	}
	c1 = 0;
	
	tsq[vc->dx][vc->dy].content = p1;
	tsq[vc->sx][vc->sy].content = 0;

	while(c1<8)
	{
		while(c2<8)
		{
			if(tsq[c1][c2].content == W_K)
			{
				wkx = c1;
				wky = c2;
			}
			else if(tsq[c1][c2].content == B_K)
			{
				bkx = c1;
				bky = c2;
			}
			c2++;
		}
		c2 = 0;
		c1++;
	}
	c1 = 0;

	if((wkx - bkx <= 1 && wkx - bkx >= -1) &&
		(wky - bky <= 1 && wky - bky >= -1))
		return 3;

//**********************************  WHITE IS CHECKED  ****************************************

//	B_P

	if(tsq[wkx-1][wky-1].content == B_P && 
		wkx-1>=0 && wky-1>=0)
		r1 = r1 | 1;
	if(tsq[wkx+1][wky-1].content == B_P && 
		wkx+1<=7 && wky-1>=0)
		r1 = r1 | 1;

//	B_N
	c1 = -2;
	c2 = -2;
	while(c1<3)
	{
		while(c2<3)
		{
			if(c1 && c2 && c1!=c2 && c1!=-c2)
			{
				if(wkx+c1>=0 && wkx+c1<=7 &&
					wky+c2>=0 && wky+c2<=7)
				{

					if(tsq[wkx+c1][wky+c2].content == B_N)
						r1 = r1 | 1;
				}
			}
			c2++;
		}
		c2 = -2;
		c1++;
	}

//	B_B & B_Q
	c1 = 1;
	while(c1<8)
	{
		if(wkx-c1>=0 && wky-c1>=0)
		{
			if(tsq[wkx-c1][wky-c1].content == B_B ||
				tsq[wkx-c1][wky-c1].content == B_Q)
			{
				r1 = r1 | 1;
				break;
			}
			else if(tsq[wkx-c1][wky-c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(wkx+c1<=7 && wky-c1>=0)
		{
			if(tsq[wkx+c1][wky-c1].content == B_B ||
				tsq[wkx+c1][wky-c1].content == B_Q)
			{
				r1 = r1 | 1;
				break;
			}
			else if(tsq[wkx+c1][wky-c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(wkx-c1>=0 && wky+c1<=7)
		{
			if(tsq[wkx-c1][wky+c1].content == B_B ||
				tsq[wkx-c1][wky+c1].content == B_Q)
			{
				r1 = r1 | 1;
				break;
			}
			else if(tsq[wkx-c1][wky+c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(wkx+c1<=7 && wky+c1<=7)
		{
			if(tsq[wkx+c1][wky+c1].content == B_B ||
				tsq[wkx+c1][wky+c1].content == B_Q)
			{
				r1 = r1 | 1;
				break;
			}
			else if(tsq[wkx+c1][wky+c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
		
//	B_R & B_Q
	c1 = 1;
	while(c1<8)
	{
		if(wkx-c1>=0)
		{
			if(tsq[wkx-c1][wky].content == B_R ||
				tsq[wkx-c1][wky].content == B_Q)
			{
				r1 = r1 | 1;
				break;
			}
			else if(tsq[wkx-c1][wky].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(wky-c1>=0)
		{
			if(tsq[wkx][wky-c1].content == B_R ||
				tsq[wkx][wky-c1].content == B_Q)
			{
				r1 = r1 | 1;
				break;
			}
			else if(tsq[wkx][wky-c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(wkx+c1<=7)
		{
			if(tsq[wkx+c1][wky].content == B_R ||
				tsq[wkx+c1][wky].content == B_Q)
			{
				r1 = r1 | 1;
				break;
			}
			else if(tsq[wkx+c1][wky].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(wky+c1<=7)
		{
			if(tsq[wkx][wky+c1].content == B_R ||
				tsq[wkx][wky+c1].content == B_Q)
			{
				r1 = r1 | 1;
				break;
			}
			else if(tsq[wkx][wky+c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}

//**********************************  BLACK IS CHECKED  ****************************************

//	W_P
	if(tsq[bkx-1][bky+1].content == W_P && 
		bkx-1>=0 && bky+1<=7)
		r1 = r1 | 2;
	if(tsq[bkx+1][bky+1].content == W_P && 
		bkx+1<=7 && bky+1<=7)
		r1 = r1 | 2;

//	W_N
	c1 = -2;
	c2 = -2;
	while(c1<3)
	{
		while(c2<3)
		{
			if(c1 && c2 && c1!=c2 && c1!=-c2)
			{
				if(bkx+c1>=0 && bkx+c1<=7 &&
					bky+c2>=0 && bky+c2<=7)
				{
					if(tsq[bkx+c1][bky+c2].content == W_N)
						r1 = r1 | 2;
				}
			}
			c2++;
		}
		c2 = -2;
		c1++;
	}
		
//	W_B & W_Q
	c1 = 1;
	while(c1<8)
	{
		if(bkx-c1>=0 && bky-c1>=0)
		{
			if(tsq[bkx-c1][bky-c1].content == W_B ||
				tsq[bkx-c1][bky-c1].content == W_Q)
			{
				r1 = r1 | 2;
				break;
			}
			else if(tsq[bkx-c1][bky-c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(bkx+c1<=7 && bky-c1>=0)
		{
			if(tsq[bkx+c1][bky-c1].content == W_B ||
				tsq[bkx+c1][bky-c1].content == W_Q)
			{
				r1 = r1 | 2;
				break;
			}
			else if(tsq[bkx+c1][bky-c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(bkx-c1>=0 && bky+c1<=7)
		{
			if(tsq[bkx-c1][bky+c1].content == W_B ||
				tsq[bkx-c1][bky+c1].content == W_Q)
			{
				r1 = r1 | 2;
				break;
			}
			else if(tsq[bkx-c1][bky+c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(bkx+c1<=7 && bky+c1<=7)
		{
			if(tsq[bkx+c1][bky+c1].content == W_B ||
				tsq[bkx+c1][bky+c1].content == W_Q)
			{
				r1 = r1 | 2;
				break;
			}
			else if(tsq[bkx+c1][bky+c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}

//	W_R & W_Q
	c1 = 1;
	while(c1<8)
	{
		if(bkx-c1>=0)
		{
			if(tsq[bkx-c1][bky].content == W_R ||
				tsq[bkx-c1][bky].content == W_Q)
			{
				r1 = r1 | 2;
				break;
			}
			else if(tsq[bkx-c1][bky].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(bky-c1>=0)
		{
			if(tsq[bkx][bky-c1].content == W_R ||
				tsq[bkx][bky-c1].content == W_Q)
			{
				r1 = r1 | 2;
				break;
			}
			else if(tsq[bkx][bky-c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(bkx+c1<=7)
		{
			if(tsq[bkx+c1][bky].content == W_R ||
				tsq[bkx+c1][bky].content == W_Q)
			{
				r1 = r1 | 2;
				break;
			}
			else if(tsq[bkx+c1][bky].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}
	c1 = 1;
	while(c1<8)
	{
		if(bky+c1<=7)
		{
			if(tsq[bkx][bky+c1].content == W_R ||
				tsq[bkx][bky+c1].content == W_Q)
			{
				r1 = r1 | 2;
				break;
			}
			else if(tsq[bkx][bky+c1].content == 0)
				__asm nop
			else
				break;
		}
		c1++;
	}

	return r1;
}


long pos2fen(void)
{
	long c1=0,c2=0;
	long strcnt=0,nullcnt=0;
	long r1;

	while(c1<8)
	{
		while(c2<8)
		{
			if(boarddir == 1)
				r1 = sq[c2][c1].content;
			else
				r1 = sq[7-c2][7-c1].content;
			if(!r1)
			{
				nullcnt++;
			}
			else
			{
				if(nullcnt)
				{
					fenout[strcnt] = (char)(0x30 + nullcnt);
					strcnt++;
				}
				switch(r1)
				{
				case 1:
					fenout[strcnt] = 'P';
					strcnt++;
					nullcnt = 0;
					break;
				case 2:
					fenout[strcnt] = 'N';
					strcnt++;
					nullcnt = 0;
					break;
				case 4:
					fenout[strcnt] = 'B';
					strcnt++;
					nullcnt = 0;
					break;
				case 8:
					fenout[strcnt] = 'R';
					strcnt++;
					nullcnt = 0;
					break;
				case 0x10:
					fenout[strcnt] = 'Q';
					strcnt++;
					nullcnt = 0;
					break;
				case 0x20:
					fenout[strcnt] = 'K';
					strcnt++;
					nullcnt = 0;
					break;
				case -1:
					fenout[strcnt] = 'p';
					strcnt++;
					nullcnt = 0;
					break;
				case -2:
					fenout[strcnt] = 'n';
					strcnt++;
					nullcnt = 0;
					break;
				case -4:
					fenout[strcnt] = 'b';
					strcnt++;
					nullcnt = 0;
					break;
				case -8:
					fenout[strcnt] = 'r';
					strcnt++;
					nullcnt = 0;
					break;
				case -0x10:
					fenout[strcnt] = 'q';
					strcnt++;
					nullcnt = 0;
					break;
				case -0x20:
					fenout[strcnt] = 'k';
					strcnt++;
					nullcnt = 0;
					break;
				default:
					__asm int 3
					return 0;
				}
			}
			c2++;
		}
		if(nullcnt)
		{
			fenout[strcnt] = (char)(0x30 + nullcnt);
			strcnt++;
		}
		fenout[strcnt] = '/';
		strcnt++;
		nullcnt = 0;
		c2 = 0;
		c1++;
	}
	fenout[strcnt-1] = ' ';
	if(turn == 1)
		fenout[strcnt] = 'w';
	else
		fenout[strcnt] = 'b';
	strcnt++;
	fenout[strcnt] = ' ';
	strcnt++;
	if(castle&~FLAG_CSTL_WK)
	{
		fenout[strcnt] = 'K';
		strcnt++;
	}
	if(castle&~FLAG_CSTL_WQ)
	{
		fenout[strcnt] = 'Q';
		strcnt++;
	}
	if(castle&~FLAG_CSTL_BK)
	{
		fenout[strcnt] = 'k';
		strcnt++;
	}
	if(castle&~FLAG_CSTL_BQ)
	{
		fenout[strcnt] = 'q';
		strcnt++;
	}
	if(!(castle&
		(~FLAG_CSTL_WK | ~FLAG_CSTL_WQ | ~FLAG_CSTL_BK | ~FLAG_CSTL_BQ)
		))
	{
		fenout[strcnt] = '-';
		strcnt++;
	}
	fenout[strcnt] = ' ';
	strcnt++;
	if(enpass == -1)
		fenout[strcnt] = '-';
	else
	{
		fenout[strcnt] = (char)(enpass+0x61);
		strcnt++;
		if(turn == -1)
			fenout[strcnt] = '3';
		else
			fenout[strcnt] = '6';
	}
	strcnt++;
	fenout[strcnt] = ' ';
	strcnt++;
	dword2dec(g50move,&fenout[strcnt]);
	if(g50move>=10)
		strcnt++;
	if(g50move>=100)
		strcnt++;
	strcnt++;
	fenout[strcnt] = ' ';
	strcnt++;
	dword2dec(gmoves,&fenout[strcnt]);
	if(gmoves>=10)
		strcnt++;
	if(gmoves>=100)
		strcnt++;
	strcnt++;
	while(strcnt<0x80)
	{
		fenout[strcnt] = 0;
		strcnt++;
	}
	return 0;
}


long fen2pos(void)
{
	long c1=0,c2=0,c3=0;
	
	zeromem(helpstra,sizeof helpstra);
	SendMessageA(hwind[WIND_FEN+1],WM_GETTEXT,0x80,(LPARAM)helpstra);

	while(c1<8)
	{
		while(c2<8)
		{
			switch(helpstra[c3])
			{
			case 'P':
				sq[c2][c1].content = W_P;
				break;
			case 'p':
				sq[c2][c1].content = B_P;
				break;
			case 'N':
				sq[c2][c1].content = W_N;
				break;
			case 'n':
				sq[c2][c1].content = B_N;
				break;
			case 'B':
				sq[c2][c1].content = W_B;
				break;
			case 'b':
				sq[c2][c1].content = B_B;
				break;
			case 'R':
				sq[c2][c1].content = W_R;
				break;
			case 'r':
				sq[c2][c1].content = B_R;
				break;
			case 'Q':
				sq[c2][c1].content = W_Q;
				break;
			case 'q':
				sq[c2][c1].content = B_Q;
				break;
			case 'K':
				sq[c2][c1].content = W_K;
				break;
			case 'k':
				sq[c2][c1].content = B_K;
				break;
			case '/':
				c2--;
				break;
			case ' ':
				c2=8;
				c1=8;
				break;
			default:
				c2 += helpstra[c3] - 0x31;
			}
			c2++;
			c3++;
		}
		c1++;
		c2=0;
	}
	c3++;
	switch(helpstra[c3])
	{
	case 'w':
		turn = 1;
		break;
	case 'b':
		turn = -1;
		break;
	default:
		__asm int 3;
		break;
	}

	c3+=2;
	castle=0;
	if(helpstra[c3] != '-')
	{
		while(helpstra[c3] != ' ')
		{
			switch(helpstra[c3])
			{
			case 'K':
				castle |= ~FLAG_CSTL_WK;
				break;
			case 'Q':
				castle |= ~FLAG_CSTL_WQ;
				break;
			case 'k':
				castle |= ~FLAG_CSTL_BK;
				break;
			case 'q':
				castle |= ~FLAG_CSTL_BQ;
				break;
			}
			c3++;
		}
	}
	else
		c3++;
	c3++;
	enpass=-1;
	if(helpstra[c3] != '-')
	{
		enpass = helpstra[c3] - 0x61;
		c3++;
	}
	c3++;


	return 0;
}


long storepos(void)
{
	long c1=0,c2=0;
	long r1= (-turn)/0x80000000;

	zeromem(hissq[gmoves][r1],0x50);
	while(c1<8)
	{
		while(c2<8)
		{
			if(boarddir == 1)
				hissq[gmoves][r1][c1*8+c2] = 
				(char)sq[c2][c1].content;
			else
				hissq[gmoves][r1][c1*8+c2] = 
				(char)sq[7-c2][7-c1].content;

			switch(sq[7-c2][7-c1].content)
			{
			case W_P:
				hissq[gmoves][r1][HIS_W_P] ++;
				break;
			case W_N:
				hissq[gmoves][r1][HIS_W_N] ++;
				break;
			case W_B:
				hissq[gmoves][r1][HIS_W_B] ++;
				break;
			case W_R:
				hissq[gmoves][r1][HIS_W_R] ++;
				break;
			case W_Q:
				hissq[gmoves][r1][HIS_W_Q] ++;
				break;
			case B_P:
				hissq[gmoves][r1][HIS_B_P] ++;
				break;
			case B_N:
				hissq[gmoves][r1][HIS_B_N] ++;
				break;
			case B_B:
				hissq[gmoves][r1][HIS_B_B] ++;
				break;
			case B_R:
				hissq[gmoves][r1][HIS_B_R] ++;
				break;
			case B_Q:
				hissq[gmoves][r1][HIS_B_Q] ++;
				break;




			}

			c2++;
		}
		c2=0;
		c1++;
	}
	
	hissq[gmoves][r1][HIS_TURN] = (char)turn;
	hissq[gmoves][r1][HIS_CASTLE] = (char)castle;
	hissq[gmoves][r1][HIS_ENPASSANT] = (char)enpass;
	hissq[gmoves][r1][HIS_G50MOVE] = (char)g50move;
	hissq[gmoves][r1][HIS_GMOVES] = (char)gmoves;
	
	return 0;
}


long loadpos(long p1, long p2)
{
	long c1=0,c2=0;
	long r1= (-p2)/0x80000000;

	if(!(long)hissq[p1][r1][HIS_TURN])
		return 0;

	while(c1<8)
	{
		while(c2<8)
		{
			if(boarddir == 1)
				sq[c2][c1].content = 
				(long)hissq[p1][r1][c1*8+c2];
			else
				sq[7-c2][7-c1].content = 
				(long)hissq[p1][r1][c1*8+c2];
			c2++;
		}
		c2=0;
		c1++;
	}
	
	turn = (long)hissq[p1][r1][HIS_TURN];
	castle = (long)hissq[p1][r1][HIS_CASTLE];
	enpass = (long)hissq[p1][r1][HIS_ENPASSANT];
	g50move = (long)hissq[p1][r1][HIS_G50MOVE];
	gmoves = (long)hissq[p1][r1][HIS_GMOVES];
	
	return 1;
}


long deltamater(void)
{
	long r1 = (-turn)/0x80000000;
	long c1=0;
	long c2;
	
	while(c1<0x40)
	{
		cpsq[c1].content = 0;
		c1++;
	}
	
	c1 = (long)hissq[gmoves][r1][HIS_W_P] - (long)hissq[gmoves][r1][HIS_B_P];
	if(c1>0)
	{
		while(c1)
		{
			cpsq[c1-1].content = W_P;
			c1--;
		}
	}
	else if(c1<0)
	{
		c1 = -c1;
		while(c1)
		{
			cpsq[c1-1].content = B_P;
			c1--;
		}
	}
	c2=0;
	c1 = (long)hissq[gmoves][r1][HIS_W_Q] - (long)hissq[gmoves][r1][HIS_B_Q];
	if(c1>0)
	{
		while(c1)
		{
			cpsq[8+c1-1].content = W_Q;
			c1--;
		}
	}
	else if(c1<0)
	{
		c1 = -c1;
		while(c1)
		{
			cpsq[8+c1-1].content = B_Q;
			c1--;
		}
	}
	c1 = (long)hissq[gmoves][r1][HIS_W_Q] - (long)hissq[gmoves][r1][HIS_B_Q];
	if(c1<0)c1=-c1;
	c2+=c1;
	c1 = (long)hissq[gmoves][r1][HIS_W_R] - (long)hissq[gmoves][r1][HIS_B_R];
	if(c1>0)
	{
		while(c1)
		{
			cpsq[c2+8+c1-1].content = W_R;
			c1--;
		}
	}
	else if(c1<0)
	{
		c1 = -c1;
		while(c1)
		{
			cpsq[c2+8+c1-1].content = B_R;
			c1--;
		}
	}
	c1 = (long)hissq[gmoves][r1][HIS_W_R] - (long)hissq[gmoves][r1][HIS_B_R];
	if(c1<0)c1=-c1;
	c2+=c1;
	c1 = (long)hissq[gmoves][r1][HIS_W_B] - (long)hissq[gmoves][r1][HIS_B_B];
	if(c1>0)
	{
		while(c1)
		{
			cpsq[c2+8+c1-1].content = W_B;
			c1--;
		}
	}
	else if(c1<0)
	{
		c1 = -c1;
		while(c1)
		{
			cpsq[c2+8+c1-1].content = B_B;
			c1--;
		}
	}
	c1 = (long)hissq[gmoves][r1][HIS_W_B] - (long)hissq[gmoves][r1][HIS_B_B];
	if(c1<0)c1=-c1;
	c2+=c1;
	c1 = (long)hissq[gmoves][r1][HIS_W_N] - (long)hissq[gmoves][r1][HIS_B_N];
	if(c1>0)
	{
		while(c1)
		{
			cpsq[c2+8+c1-1].content = W_N;
			c1--;
		}
	}
	else if(c1<0)
	{
		c1 = -c1;
		while(c1)
		{
			cpsq[c2+8+c1-1].content = B_N;
			c1--;
		}
	}





	return 0;
}


long startprocess(long p1)
{
	long c1=0;

	sattr.nLength = sizeof(SECURITY_ATTRIBUTES);
	sattr.bInheritHandle = 1;
	sattr.lpSecurityDescriptor = 0;
	
	zeromem(&si[p1],sizeof(si[p1]));
	zeromem(&pi[p1],sizeof(pi[p1]));
	si[p1].cb = sizeof(si[p1]);
	si[p1].dwFlags = STARTF_USESTDHANDLES;
	///*
	CreatePipe(&hinputr[p1],&hinputw[p1],&sattr,0x1000000);
	SetHandleInformation(hinputw[p1],HANDLE_FLAG_INHERIT,0);

	CreatePipe(&houtputr[p1],&houtputw[p1],&sattr,0x1000000);
	SetHandleInformation(houtputr[p1],HANDLE_FLAG_INHERIT,0);
	
	si[p1].hStdInput = hinputr[p1];
	si[p1].hStdOutput = houtputw[p1];
	si[p1].hStdError = houtputw[p1];

	if(!CreateProcessW((LPCWSTR)&enginepath[p1][0],(LPWSTR)&enginepath[p1][0],
		0,0,1,CREATE_NO_WINDOW,0,0,&si[p1],&pi[p1]))
	{
		return 0;
	}
	return 1;
}


long ucicmd(long p1)
{
	long c1=0;

	//if ( p1=1) __asm int 3


	hthr[p1] = CreateThread(0,0x1000,
		(LPTHREAD_START_ROUTINE)&ucicmd_,&thread_param[p1],0,0);

	zeromem(readstr,sizeof readstr);
	copymem(writestr,"uci\r\n",5);
	WriteFile(hinputw[p1],writestr,5,0,&overlp);
	
	while(!uciok_flag[p1] && c1 <= 0x500)
	{
		Sleep(1);
		c1++;
	}

	TerminateThread(hthr[p1],0);
	hthr[p1] = 0;
	return uciok_flag[p1];
}


long isreadycmd(long p1)
{
	long c1=0;
	
	hthr[p1] = CreateThread(0,0x1000,
		(LPTHREAD_START_ROUTINE)&isreadycmd_,&thread_param[p1],0,0);

	zeromem(readstr,sizeof readstr);
	copymem(writestr,"isready\r\n",9);
	WriteFile(hinputw[p1],writestr,9,0,&overlp);
	
	while(!readyok_flag[p1] && c1 <= 0x500)
	{
		Sleep(1);
		c1++;
	}

	TerminateThread(hthr[p1],0);
	hthr[p1] = 0;
	return readyok_flag[p1];
}


long ucicmd_(LPVOID p1)
{
	long ub = 0;
	long lb = 0;
	BOOL r1;
	long c1;
	long d1=0, d2=0;
	long e1;

	readn = 0;

	__asm
	{
		mov eax,[p1]
		mov eax,[eax]
		mov c1,eax
	}
	while(1)
	{
		readn = 0;
		e1 = 0;
		do{
		zeromem(&overlp,sizeof overlp);
		r1 = ReadFile(houtputr[c1],&readstr[e1],sizeof(readstr),&readn,&overlp);
		e1 += (long)readn;
		}
		while(readstr[e1-1] != 0xa);

		while(readstr[ub])
		{
			if(readstr[ub]==0x20 || readstr[ub]==0xd)	//find end
			{
				if(cmpmem(&readstr[lb],"id ",3))
				{
					lb = ub+1;
					if(cmpmem(&readstr[lb],"name ",5))
					{
						lb += 5;
						ub = lb;
						while(readstr[ub] != 0xd)
						{
							ub++;
						}
						copymem(engine[c1].id_name,&readstr[lb],ub-lb);
						ub++;
					}
					else if(cmpmem(&readstr[lb],"author ",7))
					{
						lb += 7;
						ub = lb;
						while(readstr[ub] != 0xd)
						{
							ub++;
						}
						copymem(engine[c1].id_author,&readstr[lb],ub-lb);
						ub++;
					}
				}
				else if(cmpmem(&readstr[lb],"info ",5))
				{
					lb = ub+1;

					if(cmpmem(&readstr[lb],"string ",7))
					{
						lb += 7;
						ub = lb;
						while(readstr[ub] != 0xd)
						{
							ub++;
						}
						copymem(engine[c1].info_string,&readstr[lb],ub-lb);
						ub++;
					}
				}
				else if(cmpmem(&readstr[lb],"option ",7))
				{
					lb = ub+1;
					if(cmpmem(&readstr[lb],"name ",5))
					{
						lb += 5;
						ub = lb;
						while(readstr[ub] != 0x20)
						{
							ub++;
						}
						copymem(&engine[c1].option_name[d1][0],&readstr[lb],ub-lb);
						ub++;
						lb = ub;
namespace_00:			if(cmpmem(&readstr[lb],"type ",5))
						{
							lb += 5;
							ub = lb;
							while(!(readstr[ub] == 0x20 || readstr[ub] == 0xd))
							{
								ub++;
							}
							copymem(&engine[c1].option_type[d1][0],&readstr[lb],ub-lb);
							ub++;
							lb = ub;
							if(cmpmem(&engine[c1].option_type[d1][0],"sp",2))
							{
								// case spin:
								while(1)
								{
									if(cmpmem(&readstr[lb],"default ",8))	
									{
										lb += 8;
										ub = lb;
										while(!(readstr[ub] == 0x20 || readstr[ub] == 0xd))
										{
											ub++;
										}
										copymem(&engine[c1].option_default[d1][0],&readstr[lb],ub-lb);
										ub++;
										lb = ub;
										if(readstr[lb] == 0xa)
										{
											d1++;
											break;
										}
									}
									else if(cmpmem(&readstr[lb],"min ",4))
									{
										lb += 4;
										ub = lb;
										while(!(readstr[ub] == 0x20 || readstr[ub] == 0xd))
										{
											ub++;
										}
										copymem(&engine[c1].option_min[d1][0],
											&readstr[lb],ub-lb);
										ub++;
										lb = ub;
										if(readstr[lb] == 0xa)
										{
											d1++;
											break;
										}
									}
									else if(cmpmem(&readstr[lb],"max ",4))
									{
										lb += 4;
										ub = lb;
										while(!(readstr[ub] == 0x20 || readstr[ub] == 0xd))
										{
											ub++;
										}
										copymem(&engine[c1].option_max[d1][0],
											&readstr[lb],ub-lb);
										ub++;
										lb = ub;
										if(readstr[lb] == 0xa)
										{
											d1++;
											break;
										}
									}
								}
							}
							else if(cmpmem(&engine[c1].option_type[d1][0],"co",2))
							{
								// case combo:
								while(1)
								{
									if(cmpmem(&readstr[lb],"default ",8))	
									{
										lb += 8;
										ub = lb;
										while(!(readstr[ub] == 0x20 || readstr[ub] == 0xd))
										{
											ub++;
										}
										copymem(&engine[c1].option_default[d1][0],
											&readstr[lb],ub-lb);
										ub++;
										lb = ub;
										if(readstr[lb] == 0xa)
										{
											d1++;
											break;
										}
									}
									else if(cmpmem(&readstr[lb],"var ",4))
									{
										lb += 4;
										ub = lb;
										while(!(readstr[ub] == 0x20 || readstr[ub] == 0xd))
										{
											ub++;
										}
										copymem(&engine[c1].option_var[d1][d2][0],
											&readstr[lb],ub-lb);
										ub++;
										d2++;
										lb = ub;
										if(readstr[lb] == 0xa)
										{
											d1++;
											d2 = 0;
											break;
										}
									}
								}
							}
							else if(cmpmem(&engine[c1].option_type[d1][0],"st",2))
							{
								// case string:
								while(1)
								{
									if(cmpmem(&readstr[lb],"default ",8))	
									{
										lb += 8;
										ub = lb;
										while(!(readstr[ub] == 0x20 || readstr[ub] == 0xd))
										{
											ub++;
										}
										copymem(&engine[c1].option_default[d1][0],
											&readstr[lb],ub-lb);
										ub++;
										lb = ub;
										if(readstr[lb] == 0xa)
										{
											d1++;
											break;
										}
									}
								}
							}
							else if(cmpmem(&engine[c1].option_type[d1][0],"ch",2))
							{
								// case check:
								while(1)
								{
									if(cmpmem(&readstr[lb],"default ",8))	
									{
										lb += 8;
										ub = lb;
										while(!(readstr[ub] == 0x20 || readstr[ub] == 0xd))
										{
											ub++;
										}
										copymem(&engine[c1].option_default[d1][0],
											&readstr[lb],ub-lb);
										ub++;
										lb = ub;
										if(readstr[lb] == 0xa)
										{
											d1++;
											break;
										}
									}
								}
							}
							else if(cmpmem(&engine[c1].option_type[d1][0],"bu",2))
							{
								// case button:
								/*
								while(!(readstr[ub] == 0xd))
								{
									ub++;
								}
								ub++;
								//*/
								lb = ub;
								d1++;
							}
							else
							{
								__asm int 3
								while(!(readstr[ub] == 0x20))
								{
									ub++;
								}
								ub++;
								lb = ub;
							}
						}
						else
						{
							while(readstr[ub] != 0x20)
							{
								ub++;
							}
							while(engine[c1].option_name[d1][d2])
							{
								d2++;
							}
							engine[c1].option_name[d1][d2] = ' ';
							d2++;
							copymem(&engine[c1].option_name[d1][d2],
							&readstr[lb],ub-lb);
							ub++;
							lb = ub;
							goto namespace_00;
						}
					}
					else
					{
						__asm int 3
					}
					d2 = 0;
				}
				else if(cmpmem(&readstr[lb],"uciok\r\n",7))
				{
					uciok_flag[c1] = 1;
					__asm nop
					break;
				}
				else if(cmpmem(&readstr[lb],"\r\n",2))
				{
					ub++;
				}
				ub++;
				lb = ub;
			}
			else
				ub++;
		}
		ub = 0;
		lb = 0;

	}
	return 0;
}


long isreadycmd_(LPVOID p1)
{
	BOOL r1;
	long c1;
	long e1=0;
	long lb=0;
	long ub=0;
	
	__asm
	{
		mov eax,[p1]
		mov eax,[eax]
		mov c1,eax
	}

	while(1)
	{
		readn = 0;
		e1 = 0;
		do{
		r1 = ReadFile(houtputr[c1],&readstr[e1],sizeof(readstr),&readn,&overlp);
		e1 += (long)readn;
		}
		while(readstr[e1-1] != 0xa);

		while(readstr[lb])
		{
			if(cmpmem(readstr+lb,"readyok\r\n",9))
				readyok_flag[c1] = 1;

			if(readstr[ub]==0xd)	//find end
			{
				lb = ub + 2;
				ub++;

			}
			ub++;
		}
		lb = 0;
		ub = 0;
	}
	return 0;
}


long settimec(void)
{
	long c1,c2;
	zeromem(&timec, sizeof timec);
	
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+7],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c1 = char2dword(helpstra);
	c1 *= 3600;
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+8],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = c1 + 60*c2;
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+9],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = c1 + c2;
	c1 *= 1000;
	dword2dec(c1,timec.wtime);
	
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+0xa],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c1 = char2dword(helpstra);
	c1 *= 3600;
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+0xb],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = c1 + 60*c2;
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+0xc],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = c1 + c2;
	c1 *= 1000;
	zeromem(helpstra, sizeof helpstra);
	dword2dec(c1,timec.btime);
	
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+0xd],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = 60*c2;
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+0xe],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = c1 + c2;
	c1 *= 1000;
	dword2dec(c1,timec.winc);
	
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+0xf],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = 60*c2;
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+0x10],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = c1 + c2;
	c1 *= 1000;
	dword2dec(c1,timec.binc);
	
	SendMessageA(hwind[WIND_SETGAME+0x11],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)timec.moves);
	
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+0x13],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = 60*c2;
	zeromem(helpstra, sizeof helpstra);
	SendMessageA(hwind[WIND_SETGAME+0x14],WM_GETTEXT,
		(WPARAM)0x10,(LPARAM)helpstra);
	c2 = char2dword(helpstra);
	c1 = c1 + c2;
	c1 *= 1000;
	dword2dec(c1,timec.movetime);

	return 0;
}


long sendparam2engine(long p1)
{
	long c1 = 0;

	while(engine[p1].option_name[c1][0])
	{
		if(engine[p1].option_type[c1][0] != 'b')
		{
			zeromem(&overlp,sizeof overlp);
			zeromem(helpstra,sizeof helpstra);
			zeromem(writestr,sizeof writestr);
			copymem(writestr,"setoption name ",sizeof "setoption name ");
			copymem(writestr+findnull(writestr),engine[p1].option_name[c1],
				sizeof engine[p1].option_name[c1]);
			copymem(writestr+findnull(writestr)," value ",sizeof " value ");
			if(engine[p1].option_type[c1][0] == 's')
			{
				//spin, string
				SendMessageA(hwind[WIND_ENGPARAM+c1+1],WM_GETTEXT,0x200,(LPARAM)helpstra);
				copymem(writestr+findnull(writestr),helpstra,findnull(helpstra));
				writestr[findnull(writestr)] = '\r';
				writestr[findnull(writestr)] = '\n';
			}
			else if(engine[p1].option_type[c1][1] == 'h')
			{
				//check
				if(SendMessage(hwind[WIND_ENGPARAM+c1+1],BM_GETCHECK,0,0))
					copymem(writestr+findnull(writestr),"true\r\n",6);
				else
					copymem(writestr+findnull(writestr),"false\r\n",7);

			}
			WriteFile(hinputw[p1],writestr,findnull(writestr),0,&overlp);
		}
		c1++;
	}
	


	return 0;
}


long calc(long p1)
{
	if(!uciok_flag[p1])
		return 0;
	if(!readyok_flag[p1])
		return 0;

	if(calc_flag[p1])
	{
		stopcalc(p1);
	}

	zeromem(&overlp,sizeof overlp);
	zeromem(helpstra,sizeof helpstra);
	copymem(helpstra,"position fen ",sizeof "position fen ");
	copymem(helpstra+findnull(helpstra),fenout,sizeof fenout);
	copymem(helpstra+findnull(helpstra),"\r\n",2);
	zeromem(writestr,sizeof writestr);
	copymem(writestr,helpstra,findnull(helpstra));
	WriteFile(hinputw[p1],writestr,findnull(writestr),0,&overlp);
	Sleep(100);

	if(!calc_flag[p1])
		return 2;
	if(!hthr[p1])
		hthr[p1] = CreateThread(0,0x1000,(LPTHREAD_START_ROUTINE)&engineoutput,&thread_param[p1],0,0);
	Sleep(100);

	zeromem(&overlp,sizeof overlp);
	zeromem(readstr,sizeof readstr);
	zeromem(writestr,sizeof writestr);



	copymem(writestr,"go infinite\r\n",sizeof "go infinite\r\n");




	WriteFile(hinputw[p1],writestr,findnull(writestr),0,&overlp);
	
	return 1;
}


long calcp(long p1)
{
	long c1=0;

	if(!uciok_flag[p1])
		return 0;
	if(!readyok_flag[p1])
		return 0;

	while(c1<4)
	{
		stopcalc(c1);
		c1++;
	}

	zeromem(&overlp,sizeof overlp);
	zeromem(helpstra,sizeof helpstra);
	copymem(helpstra,"position fen ",sizeof "position fen ");
	copymem(helpstra+findnull(helpstra),fenout,sizeof fenout);
	copymem(helpstra+findnull(helpstra),"\r\n",2);
	zeromem(writestr,sizeof writestr);
	copymem(writestr,helpstra,findnull(helpstra));
	WriteFile(hinputw[p1],writestr,findnull(writestr),0,&overlp);
	Sleep(100);

	if(!hthr[p1])
		hthr[p1] = CreateThread(0,0x1000,(LPTHREAD_START_ROUTINE)&engineoutput,&thread_param[p1],0,0);
	Sleep(100);

	zeromem(&overlp,sizeof overlp);
	zeromem(readstr,sizeof readstr);
	zeromem(writestr,sizeof writestr);

	if(SendMessageA(hwind[WIND_SETGAME+0x12],BM_GETCHECK,0,0))
	{
		copymem(writestr,"go movetime ",sizeof "go movetime ");
		copymem(writestr+findnull(writestr),timec.movetime,sizeof timec.movetime);
		copymem(writestr+findnull(writestr),"\r\n",2);
	}
	else
	{
		copymem(writestr,"go wtime ",sizeof "go wtime ");
		copymem(writestr+findnull(writestr),timec.wtime,sizeof timec.wtime);
		copymem(writestr+findnull(writestr)," btime ",sizeof " btime ");
		copymem(writestr+findnull(writestr),timec.btime,sizeof timec.btime);
		copymem(writestr+findnull(writestr)," winc ",sizeof " winc ");
		copymem(writestr+findnull(writestr),timec.winc,sizeof timec.winc);
		copymem(writestr+findnull(writestr)," binc ",sizeof " binc ");
		copymem(writestr+findnull(writestr),timec.binc,sizeof timec.binc);
		copymem(writestr+findnull(writestr)," moves ",sizeof " moves ");
		copymem(writestr+findnull(writestr),timec.moves,sizeof timec.moves);
		copymem(writestr+findnull(writestr),"\r\n",2);
	}

	WriteFile(hinputw[p1],writestr,findnull(writestr),0,&overlp);
	
	return 1;
}


long stopcalc(long p1)
{
	if(!uciok_flag[p1])
		return 0;
	if(!readyok_flag[p1])
		return 0;
	
	zeromem(&overlp,sizeof overlp);
	zeromem(readstr,sizeof readstr);
	zeromem(writestr,sizeof writestr);
	copymem(writestr,"stop\r\n",sizeof "stop\r\n");
	WriteFile(hinputw[p1],writestr,findnull(writestr),0,&overlp);
	
	return 1;
}


long ucinewgame(long p1)
{
	if(!uciok_flag[p1])
		return 0;
	if(!readyok_flag[p1])
		return 0;
	
	zeromem(&overlp,sizeof overlp);
	zeromem(readstr,sizeof readstr);
	zeromem(writestr,sizeof writestr);
	copymem(writestr,"stop\r\n",sizeof "stop\r\n");
	WriteFile(hinputw[p1],writestr,findnull(writestr),0,&overlp);
	Sleep(100);
	zeromem(writestr,sizeof writestr);
	copymem(writestr,"ucinewgame\r\n",sizeof "ucinewgame\r\n");
	WriteFile(hinputw[p1],writestr,findnull(writestr),0,&overlp);
	Sleep(100);
	copymem(helpstra,"position fen ",sizeof "position fen ");
	copymem(helpstra+findnull(helpstra),fenout,sizeof fenout);
	copymem(helpstra+findnull(helpstra),"\r\n",2);
	zeromem(writestr,sizeof writestr);
	copymem(writestr,helpstra,findnull(helpstra));
	WriteFile(hinputw[p1],writestr,findnull(writestr),0,&overlp);
	Sleep(100);
	
	return 1;
}


long translatemove(char* pv, char* pout)
{
	long c1=0,c2=0;
	long d1=0,d2=0;
	char r1;
	VECTOR v1,v2;

	copymem(&vsq[0][0],&sq[0][0],sizeof sq);

	while(pv[c1] >= 'a' && pv[c1] <= 'h')
	{
		//source
		v1.sx = pv[c1] - 0x61;
		c1++;
		v1.sy = 8-(pv[c1] - 0x30);
		c1++;
		//dest
		v1.dx = pv[c1] - 0x61;
		c1++;
		v1.dy = 8-(pv[c1] - 0x30);
		c1++;

		if(vsq[v1.sx][v1.sy].content == 1 ||
			vsq[v1.sx][v1.sy].content == -1)
		{
			if(vsq[v1.dx][v1.dy].content)
			{
				pout[c2] = pv[c1-4];
				c2++;
			}
			else if(!vsq[v1.dx][v1.dy].content &&
				(v1.sx != v1.dx))
			{
				pout[c2] = pv[c1-4];
				c2++;
				if(v1.sy > v1.dy)
					vsq[v1.dx][3].content = 0;
				else
					vsq[v1.dx][4].content = 0;
			}
			if(pv[c1] != ' ' && pv[c1])
			{
				pout[c2] = pv[c1] + 0x20;
				c2++;
				c1++;
				switch(pv[c1])
				{
				case 'q':
					vsq[v1.sx][v1.sy].content = W_Q;
					break;
				case 'r':
					vsq[v1.sx][v1.sy].content = W_R;
					break;
				case 'b':
					vsq[v1.sx][v1.sy].content = W_B;
					break;
				case 'n':
					vsq[v1.sx][v1.sy].content = W_N;
					break;
				}
				if(pv[c1-1] == '1')
					vsq[v1.sx][v1.sy].content = -vsq[v1.sx][v1.sy].content;
			}
		}
		else
		{
			switch(vsq[v1.sx][v1.sy].content)
			{
			case W_N:
			case B_N:
				pout[c2] = 'N';
				break;
			case W_B:
			case B_B:
				pout[c2] = 'B';
				break;
			case W_R:
			case B_R:
				pout[c2] = 'R';
				break;
			case W_Q:
			case B_Q:
				pout[c2] = 'Q';
				break;
			case W_K:
			case B_K:
				if(pv[c1-4] == 'e' && pv[c1-2] == 'g')
				{
					pout[c2] = 'O';
					c2++;
					pout[c2] = '-';
					c2++;
					pout[c2] = 'O';
					c2++;
					if(pv[c1-1] == '8')
						vsq[v1.sx+1][v1.sy].content = B_R;
					else
						vsq[v1.sx+1][v1.sy].content = W_R;
					vsq[v1.sx+3][v1.sy].content = 0;
					goto _end;
				}
				else if(pv[c1-4] == 'e' && pv[c1-2] == 'c')
				{
					pout[c2] = 'O';
					c2++;
					pout[c2] = '-';
					c2++;
					pout[c2] = 'O';
					c2++;
					pout[c2] = '-';
					c2++;
					pout[c2] = 'O';
					c2++;
					if(pv[c1-1] == '8')
						vsq[v1.sx-1][v1.sy].content = B_R;
					else
						vsq[v1.sx-1][v1.sy].content = W_R;
					vsq[v1.sx-4][v1.sy].content = 0;
					goto _end;
				}
				else
					pout[c2] = 'K';
				break;
			}
			c2++;
			//if source is needed
			d1=0;
			d2=0;
			while(d1<8)
			{
				while(d2<8)
				{
					if((vsq[d1][d2].content == vsq[v1.sx][v1.sy].content) &&
						(d1 != v1.sx || d2 != v1.sy))
					{
						v2.sx = d1;
						v2.sy = d2;
						v2.dx = v1.dx;
						v2.dy = v1.dy;
						if(isvalidmove(&vsq,vsq[d1][d2].content,&v2))
						{
							pout[c2] = pv[c1-4];
							c2++;
							pout[c2] = pv[c1-3];
							c2++;
							goto _exit;
						}
					}
					d2++;
				}
				d2=0;
				d1++;
			}
_exit:
			if(vsq[v1.dx][v1.dy].content)
			{
				pout[c2] = 'x';
				c2++;
			}

		}
		pout[c2] = pv[c1-2];
		c2++;
		pout[c2] = pv[c1-1];
		c2++;
_end:
		pout[c2] = ' ';
		c2++;
		c1++;

		vsq[v1.dx][v1.dy].content = vsq[v1.sx][v1.sy].content;
		vsq[v1.sx][v1.sy].content = 0;


	}


	return 0;
}


long domove(long p1, long p2, long fl)
{
	VECTOR v1;
	long r1, r2;
	if(engpl[0].pause && engpl[1].pause)
		return -1;
	
	if(engine[p1].bestmove[0] < 0x61 ||
		engine[p1].bestmove[0] > 0x68)
		return 0x80;

	v1.sx = engine[p1].bestmove[0]-0x61;
	v1.sy = 8-(engine[p1].bestmove[1]-0x30);
	v1.dx = engine[p1].bestmove[2]-0x61;
	v1.dy = 8-(engine[p1].bestmove[3]-0x30);
	if(boarddir != 1)
	{
		v1.sx = 7 - v1.sx;
		v1.dx = 7 - v1.dx;
		v1.sy = 7 - v1.sy;
		v1.dy = 7 - v1.dy;
	}
	r2 = sq[v1.dx][v1.dy].content;

	r1 = isvalidmove(&sq,sq[v1.sx][v1.sy].content,&v1);

	sq[v1.dx][v1.dy].content = sq[v1.sx][v1.sy].content;
	sq[v1.sx][v1.sy].content = 0;
	if(r1&8)
	{
		switch(engine[p1].bestmove[4])
		{
		case 'q':
			sq[v1.dx][v1.dy].content = B_Q;
			break;
		case 'r':
			sq[v1.dx][v1.dy].content = B_R;
			break;
		case 'b':
			sq[v1.dx][v1.dy].content = B_B;
			break;
		case 'n':
			sq[v1.dx][v1.dy].content = B_N;
			break;
		default:
			__asm int 3
		}
		if(engine[p1].bestmove[3] == '8')
			sq[v1.dx][v1.dy].content = -sq[v1.dx][v1.dy].content;
		redrawrect(v1.dx,v1.dy);
		sq[v1.sx][v1.sy].content = 0;
		redrawrect(v1.sx,v1.sy);
		goto domove_01;
	}
	if(r1 == (RET_CASTLEK))
	{
		if(boarddir>0)
		{
			sq[5][7].content = W_R;
			sq[7][7].content = 0;
			redrawrect(5,7);
			redrawrect(7,7);
		}
		else
		{
			sq[2][0].content = W_R;
			sq[0][0].content = 0;
			redrawrect(2,0);
			redrawrect(0,0);
		}
	}
	else if(r1 == (RET_CASTLEQ))
	{
		if(boarddir>0)
		{
			sq[3][7].content = W_R;
			sq[0][7].content = 0;
			redrawrect(3,7);
			redrawrect(0,7);
		}
		else
		{
			sq[4][0].content = W_R;
			sq[7][0].content = 0;
			redrawrect(4,0);
			redrawrect(7,0);
		}
	}
	else if(r1 == (RET__CASTLEK))
	{
		if(boarddir>0)
		{
			sq[5][0].content = B_R;
			sq[7][0].content = 0;
			redrawrect(5,0);
			redrawrect(7,0);
		}
		else
		{
			sq[2][7].content = B_R;
			sq[0][7].content = 0;
			redrawrect(2,7);
			redrawrect(0,7);
		}
	}
	else if(r1 == (RET__CASTLEQ))
	{
		if(boarddir>0)
		{
			sq[3][0].content = B_R;
			sq[0][0].content = 0;
			redrawrect(3,0);
			redrawrect(0,0);
		}
		else
		{
			sq[4][7].content = B_R;
			sq[7][7].content = 0;
			redrawrect(4,7);
			redrawrect(7,7);
		}
	}
domove_01:
	if (v1.sx == 4 && 
		v1.sy == 7 && 
		boarddir == 1)
		castle = castle & (FLAG_CSTL_WK) & (FLAG_CSTL_WQ);
	else if (v1.sx == 3 && 
		v1.sy == 0 && 
		boarddir == -1)
		castle = castle & (FLAG_CSTL_WK) & (FLAG_CSTL_WQ);
	if (v1.sx == 4 && 
		v1.sy == 0 && 
		boarddir == 1)
		castle = castle & (FLAG_CSTL_BK) & (FLAG_CSTL_BQ);
	else if (v1.sx == 3 && 
		v1.sy == 7 && 
		boarddir == -1)
		castle = castle & (FLAG_CSTL_BK) & (FLAG_CSTL_BQ);
	if (((v1.sx == 7 && v1.sy == 7) ||
		(v1.dx == 7 && v1.dy == 7)) &&
		boarddir == 1)
		castle = castle & (FLAG_CSTL_WK);
	else if (((v1.sx == 0 && v1.sy == 0) ||
		(v1.dx == 0 && v1.dy == 0)) &&
		boarddir == -1)
		castle = castle & (FLAG_CSTL_WK);
	if (((v1.sx == 0 && v1.sy == 7) ||
		(v1.dx == 0 && v1.dy == 7)) &&
		boarddir == 1)
		castle = castle & (FLAG_CSTL_WQ);
	else if (((v1.sx == 7 && v1.sy == 0) ||
		(v1.dx == 7 && v1.dy == 0)) &&
		boarddir == -1)
		castle = castle & (FLAG_CSTL_WQ);
	if (((v1.sx == 7 && v1.sy == 0) ||
		(v1.dx == 7 && v1.dy == 0)) &&
		boarddir == 1)
		castle = castle & (FLAG_CSTL_BK);
	else if (((v1.sx == 0 && v1.sy == 7) ||
		(v1.dx == 0 && v1.dy == 7)) &&
		boarddir == -1)
		castle = castle & (FLAG_CSTL_BK);
	if (((v1.sx == 0 && v1.sy == 0) ||
		(v1.dx == 0 && v1.dy == 0)) &&
		boarddir == 1)
		castle = castle & (FLAG_CSTL_BQ);
	else if (((v1.sx == 7 && v1.sy == 7) ||
		(v1.dx == 7 && v1.dy == 7)) &&
		boarddir == -1)
		castle = castle & (FLAG_CSTL_BQ);
	if(r1 == (RET_ENPASSANT))
	{
		sq[v1.dx][v1.dy+1].content = 0;
		redrawrect(v1.dx,v1.dy+1);
	}
	if(r1 == (RET__ENPASSANT))
	{
		sq[v1.dx][v1.dy-1].content = 0;
		redrawrect(v1.dx,v1.dy-1);
	}
	enpass = -1;
	if(r1 == (RET_DMOVE) || r1 == (RET__DMOVE))
	{
		if(boarddir>0)
			enpass = v1.dx;
		else
			enpass = 7 - v1.dx;
	}
	if(turn == 1)
		gmoves++;
	g50move++;
	if(sq[v1.dx][v1.dy].content == 1 || sq[v1.dx][v1.dy].content == -1 || r2)
		g50move = 0;

	turn *= -1;
	
	storepos();
	pos2fen();
	SendMessageA(hwind[WIND_FEN+1],WM_SETTEXT,(WPARAM)0,(LPARAM)fenout);
	deltamater();
	InvalidateRect(hwind[WIND_CAPTURE],0,1);
	
	if(check4legal())
	{
		r1 = isvalidcontrol(sq[v1.dx][v1.dy].content, &v1);
		if(r1)
			SetTimer(hwind[0],r1,1,0);
		KillTimer(hwind[0],0x1b);
		fl = 0;
	}
	else if(check4draws())
	{
		__asm MOV DWORD PTR[r1],EAX
		SetTimer(hwind[0],r1,1,0);
		KillTimer(hwind[0],0x1b);
		fl = 0;
	}

	if(fl)
		calcp(p2);
	
	redrawrect(v1.sx,v1.sy);
	redrawrect(v1.dx,v1.dy);
	return 0;
}


void engineoutput(LPVOID addr)
{
	long pv_flag;
	long* _pe;
	long pe;
	long readln=0, readendln=0, readmrg, readinfo=0;
	long mpv;

	engf.multipv[0] = 0x31;

	_pe = (long*)addr;
	pe = _pe[0];
	
	while(1)
	{
		zeromem(readstr,sizeof readstr);
		readmrg=0;
		while(1)
		{
			ReadFile(houtputr[pe],readstr+readmrg,sizeof(readstr)-readmrg,&readn,&overlp);
			readmrg = findnull(readstr);
			if(readstr[readmrg-1] == 0xa) break;
			__asm nop
		}
		readln = 0;
		readendln = findcrlf(readstr+readln);
		
		//for each (command) line
		do
		{
			//reset mpv
			engf.multipv[0] = '1';
			engf.multipv[1] = 0;

			// zero pv_flag
			pv_flag = 0;

			//also zero currmove
			zeromem(engine[pe].info_currmove,sizeof engine[pe].info_currmove);

			readinfo=0;
			if(cmpmem(readstr+readln,"info ",5))
			{
				while(1)
				{
					readinfo += findspace(readstr+readln+readinfo);
					if(*(readstr+readln+readinfo) == 0xd)
						break;
					readinfo++;
					
					if(cmpmem(readstr+readln+readinfo,"depth ",sizeof("depth ")-1))
					{
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						zeromem(engf.depth,sizeof engf.depth);
						copymem(engf.depth,readstr+readln+readinfo,
							findspace(readstr+readln+readinfo));
					}
					else if(cmpmem(readstr+readln+readinfo,"seldepth ",sizeof("seldepth ")-1))
					{
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						zeromem(engf.seldepth,sizeof engf.seldepth);
						copymem(engf.seldepth,readstr+readln+readinfo,
							findspace(readstr+readln+readinfo));
					}
					else if(cmpmem(readstr+readln+readinfo,"time ",sizeof("time ")-1))
					{
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						zeromem(engf.time,sizeof engf.time);
						copymem(engf.time,readstr+readln+readinfo,
							findspace(readstr+readln+readinfo));
					}
					else if(cmpmem(readstr+readln+readinfo,"nodes ",sizeof("nodes ")-1))
					{
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						zeromem(engf.nodes,sizeof engf.nodes);
						copymem(engf.nodes,readstr+readln+readinfo,
							findspace(readstr+readln+readinfo));
					}
					else if(cmpmem(readstr+readln+readinfo,"nps ",sizeof("nps ")-1))
					{
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						zeromem(engf.nps,sizeof engf.nps);
						copymem(engf.nps,readstr+readln+readinfo,
							findspace(readstr+readln+readinfo));
					}
					else if(cmpmem(readstr+readln+readinfo,"score ",sizeof("score ")-1))
					{
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						zeromem(engf.score,sizeof engf.score);
						if(cmpmem(readstr+readln+readinfo,"cp ",sizeof("cp ")-1))
						{
							readinfo += findspace(readstr+readln+readinfo);
							readinfo++;
							copymem(engf.score,readstr+readln+readinfo,
								findspace(readstr+readln+readinfo));
						}
						else
						{
							readinfo += findspace(readstr+readln+readinfo);
							readinfo++;
							copymem(engf.score+2,readstr+readln+readinfo,
								findspace(readstr+readln+readinfo));
							engf.score[0] = '#';
							engf.score[1] = ' ';
						}
					}
					else if(cmpmem(readstr+readln+readinfo,"multipv ",sizeof("multipv ")-1))
					{
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						zeromem(engf.multipv,sizeof engf.multipv);
						copymem(engf.multipv,readstr+readln+readinfo,
							findspace(readstr+readln+readinfo));
					}
					else if(cmpmem(readstr+readln+readinfo,"pv ",sizeof("pv ")-1))
					{
						pv_flag = 1;
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						zeromem(engf.pv,sizeof engf.pv);
						copymem(engf.pv,readstr+readln+readinfo,
							findcrlf(readstr+readln+readinfo));
					}
					else if(cmpmem(readstr+readln+readinfo,"currmove ",sizeof("currmove ")-1))
					{
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						copymem(engine[pe].info_currmove,readstr+readln+readinfo,
							findspace(readstr+readln+readinfo));
					}
					else if(cmpmem(readstr+readln+readinfo,"hashfull ",sizeof("hashfull ")-1))
					{
						readinfo += findspace(readstr+readln+readinfo);
						readinfo++;
						copymem(engine[pe].info_hashfull,readstr+readln+readinfo,
							findspace(readstr+readln+readinfo));
					}
				
				}
				mpv = char2dword(engf.multipv)-1;
				if(pv_flag)
				{
					copymem(engine[pe].info_depth[mpv],engf.depth,sizeof(engf.depth));
					copymem(engine[pe].info_seldepth[mpv],engf.seldepth,sizeof(engf.seldepth));
					copymem(engine[pe].info_score[mpv],engf.score,sizeof(engf.score));
					copymem(engine[pe].info_nodes[mpv],engf.nodes,sizeof(engf.nodes));
					copymem(engine[pe].info_time[mpv],engf.time,sizeof(engf.time));
					copymem(engine[pe].info_nps[mpv],engf.nps,sizeof(engf.nps));
					copymem(engine[pe].info_pv[mpv],engf.pv,sizeof(engf.pv));
					dataout(pe);
				}
				else
				{
					copymem(engine[pe].info_depth[mpv],engf.depth,sizeof(engf.depth));
					copymem(engine[pe].info_nodes[mpv],engf.nodes,sizeof(engf.nodes));
					copymem(engine[pe].info_time[mpv],engf.time,sizeof(engf.time));
					copymem(engine[pe].info_nps[mpv],engf.nps,sizeof(engf.nps));
					//hashfull
					//currmove
					dataoutx(pe);
				}

			}
			else if(cmpmem(readstr+readln,"bestmove ",9))
			{
				readinfo += findspace(readstr+readln+readinfo);
				readinfo++;
				copymem(engine[pe].bestmove,readstr+readln+readinfo,findspace(readstr+readln+readinfo));
				if(engpl[0].flag && pe == engpl[0].id)
					domove(engpl[0].id,engpl[1].id,engpl[1].flag);
				else if(engpl[1].flag && pe == engpl[1].id)
					domove(engpl[1].id,engpl[0].id,engpl[0].flag);

			}
			readln = readendln+2;
			readendln = readln + findcrlf(readstr+readln);
		}while(readln < readmrg);

	}

}


long dataout(long pe)
{
	long mpv=0;
	long d1;
	
	zeromem(engdata,sizeof engdata);
	copymem(engdata,"line\tdepth\tscore\tpv\r\n",sizeof "line\tdepth\tscore\tpv\r\n");

	while(mpv<0x1f)
	{
		if(!engine[pe].info_depth[mpv][0])
			break;
		
		zeromem(helpstra,sizeof helpstra);
		d1 = findnull(engdata);
		dword2dec(mpv+1,helpstra);
		helpstra[findnull(helpstra)] = ':';
		helpstra[findnull(helpstra)] = '\t';
		copymem(engdata+d1,helpstra,findnull(helpstra));

		d1 = findnull(engdata);

		copymem(engdata+d1,engine[pe].info_depth[mpv],
			sizeof(engine[pe].info_depth[mpv]));
		d1 = findnull(engdata);

		engdata[d1] = '/';
		if(engine[pe].info_seldepth[mpv][0])
			copymem(engdata+d1+1,engine[pe].info_seldepth[mpv],
				sizeof(engine[pe].info_seldepth[mpv]));
		else
			copymem(engdata+d1+1,engine[pe].info_depth[mpv],
				sizeof(engine[pe].info_seldepth[mpv]));
		d1 = findnull(engdata);

		engdata[d1] = '\t';
		
		copymem(engdata+d1+1,engine[pe].info_score[mpv],
			sizeof(engine[pe].info_score[mpv]));
		d1 = findnull(engdata);

		engdata[d1] = '\t';
		translatemove(engine[pe].info_pv[mpv],engdata+d1+1);
		d1 = findnull(engdata);
				
		engdata[d1] = '\r';
		engdata[d1+1] = '\n';


		mpv++;
	}

	SendMessageA(hwind[WIND_ENGINFO+2*pe+1],WM_SETTEXT,0,(LPARAM)engdata);
	
	return 0;
}








long dataoutx(long pe)
{
	long mpv=0;
	long d1;

	zeromem(engdata,sizeof engdata);
	d1 = findnull(engdata);
	copymem(engdata+d1,engine[pe].id_name,
			sizeof(engine[pe].id_name));
	d1 = findnull(engdata);
	copymem(engdata+d1,"   depth: ",
			sizeof "   depth: ");
	d1 = findnull(engdata);
	copymem(engdata+d1,engine[pe].info_depth[0],
			sizeof(engine[pe].info_depth));
	d1 = findnull(engdata);
	copymem(engdata+d1,"   nodes: ",
			sizeof "   nodes: ");
	d1 = findnull(engdata);
	copymem(engdata+d1,engine[pe].info_nodes[0],
			sizeof(engine[pe].info_nodes));
	d1 = findnull(engdata);
	copymem(engdata+d1,"   time: ",
			sizeof "   time: ");
	d1 = findnull(engdata);
	copymem(engdata+d1,engine[pe].info_time[0],
		sizeof(engine[pe].info_time));
	d1 = findnull(engdata);
	copymem(engdata+d1,"   nps: ",
			sizeof "   nps: ");
	d1 = findnull(engdata);
	copymem(engdata+d1,engine[pe].info_nps[0],
			sizeof(engine[pe].info_nps[0]));
	d1 = findnull(engdata);
	copymem(engdata+d1,"   hashfull: ",
			sizeof "   hashfull: ");
	d1 = findnull(engdata);
	copymem(engdata+d1,engine[pe].info_hashfull,
		sizeof(engine[pe].info_hashfull));
	d1 = findnull(engdata);
	copymem(engdata+d1,"   Searching: ",
			sizeof "   Searching: ");
	d1 = findnull(engdata);
	copymem(engdata+d1,engine[pe].info_currmove,
			sizeof(engine[pe].info_currmove));

	if(calc_flag)
		SendMessageA(hwind[WIND_ENGINFO+2*pe],WM_SETTEXT,0,(LPARAM)engdata);

	return 0;
}














































