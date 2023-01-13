

// Constants:
#define MAX_LOADSTRING 0x100

#define WPAWN 0x0
#define BPAWN 0x1
#define _PAWN 0x2
#define WKNIGHT 0x3
#define BKNIGHT 0x4
#define _KNIGHT 0x5
#define WBISHOP 0x6
#define BBISHOP 0x7
#define _BISHOP 0x8
#define WROCK 0x9
#define BROCK 0xa
#define _ROCK 0xb
#define WQUEEN 0xc
#define BQUEEN 0xd
#define _QUEEN 0xe
#define WKING 0xf
#define BKING 0x10
#define _KING 0x11
#define DELIC 0x12
#define _DELIC 0x13
#define MOVIC 0x14
#define _MOVIC 0x15
#define TIC 0x16
#define _TIC 0x17


#define W_P 1
#define W_N 2
#define W_B 4
#define W_R 8
#define W_Q 16
#define W_K 32
#define B_P -1
#define B_N -2
#define B_B -4
#define B_R -8
#define B_Q -16
#define B_K -32


#define	WIND_MAIN			0
#define	WIND_SETGAME		1
#define	WIND_SETPOS			0x20
#define	WIND_CAPTURE		0x30
#define	WIND_ENGLIST		0x31
#define WIND_TIMEC			0x38
#define	WIND_PROM			0x40
#define	WIND_FEN			0x50
#define	WIND_STATE			0x60
#define	WIND_ENGINFO		0x62
#define	WIND_LOADENG		0x70
#define WIND_STOPGO			0xA0
#define	WIND_ENGPARAM		0x100
#define	WIND_0				0x1ff

#define	RC_GAME_SETGAME		0x400
	#define	RET_GAME_SETGAME_OK		0x4010
	#define	RET_GAME_SETGAME_CA		0x4011
	#define	RET_GAME_SETGAME_WU		0x4012
	#define	RET_GAME_SETGAME_WE		0x4013
	#define	RET_GAME_SETGAME_BU		0x4014
	#define	RET_GAME_SETGAME_BE		0x4015
	#define	RET_GAME_SETGAME_TIME	0x4016
	#define	RET_GAME_SETGAME_SELE	0x4017

	#define	RET_GAME_SETGAME_INITPOS	0x401F
	#define	RET_GAME_SETGAME_CURRPOS	0x401E
#define	RC_GAME_SETPOS		0x401
	#define	RET_GAME_SETPOS_OK		0x4030
	#define	RET_GAME_SETPOS_CA		0x4031
	#define	RET_GAME_SETPOS_ST		0x4032
	#define	RET_GAME_SETPOS_CL		0x4033
	#define	RET_GAME_SETPOS_FEN		0x4034
	#define RET_GAME_SETPOS_WK		0x4035
	#define RET_GAME_SETPOS_BK		0x4036
	#define RET_GAME_SETPOS_WQ		0x4037
	#define RET_GAME_SETPOS_BQ		0x4038
	#define	RET_GAME_SETPOS_W2M		0x4039
	#define	RET_GAME_SETPOS_B2M		0x403A
	#define	RET_GAME_SETPOS_G50		0x403B
	#define	RET_GAME_SETPOS_GM		0x403C
	#define	RET_GAME_SETPOS_EP		0x403D

#define	RC_GAME_OPEN		0x402
#define	RC_GAME_SAVE		0x403
#define	RC_GAME_UNDO		0x404
#define	RC_GAME_REDO		0x405
#define	RC_GAME_EXIT		0x40f
#define	RC_VIEW_FLIP		0x410
#define	RC_VIEW_AUTOFLIP	0x411
#define	RC_VIEW_LASTMOVE	0x412
#define	RC_ENGINE_LOADENG		0x420
	#define	RET_ENGINE_LOADENG_ACT		0x4200
	#define	RET_ENGINE_LOADENG_UN		0x4204
	#define	RET_ENGINE_LOADENG_PATH		0x4208
	#define	RET_ENGINE_LOADENG_ENGPAR	0x420C
	#define	RET_ENGINE_LOADENG_RESTART	0x42F0
	#define	RET_ENGINE_LOADENG_RET		0x4210
	#define	RET_ENGINE_LOADENG_UNA		0x4211
	#define	RET_ENGINE_ENGPARAM_LS		0x4212
	#define	RET_ENGINE_ENGPARAM_SS		0x4213
	#define	RET_ENGINE_ENGPARAM_SE		0x4214
	#define	RET_ENGINE_ENGPARAM_RET		0x4215

#define	RC_ANALYSE_OPTIONS		0x430
#define	RC_ANALYSE_GOSTOP		0x431
	#define	RET_ANALYSE_GOSTOP_RET		0x4300



	#define	RET_ENGINE_PARAMETERS	0x5000



#define	COLOR_LIGHT	0xF0F0E0
#define	COLOR_DARK	0xE0C080
#define	COLOR_WHITE	0xFFFFFF
#define	COLOR_BLACK	0

#define MAX_HEIGHT 600
#define MIN_NEP 19 //	600 / 30 = 20


#define GAMESTATE_NORMAL 0
#define GAMESTATE_SETPOS 0x10
	#define	GAMESTATE_SETPOS_HOLD 1


#define	RET_MOVE		1
#define	RET_CAPTURE		2
#define	RET_DMOVE		4
#define	RET_ENPASSANT	5
#define	RET_PROM		8
#define	RET_CASTLEK		0x10
#define	RET_CASTLEQ		0x11
#define	RET__MOVE		1 | 0x80000000
#define	RET__CAPTURE	2 | 0x80000000
#define	RET__DMOVE		4 | 0x80000000
#define	RET__ENPASSANT	5 | 0x80000000
#define	RET__PROM		8 | 0x80000000
#define	RET__CASTLEK	0x10 | 0x80000000
#define	RET__CASTLEQ	0x11 | 0x80000000


#define	FLAG_CSTL_WK	~1
#define	FLAG_CSTL_WQ	~2
#define	FLAG_CSTL_BK	~0x10
#define	FLAG_CSTL_BQ	~0x20
#define	FLAG_CSTL_ALL	~FLAG_CSTL_WK | ~FLAG_CSTL_WQ | ~FLAG_CSTL_BK | ~FLAG_CSTL_BQ


#define	HIS_TURN		0x40
#define	HIS_CASTLE		0x41
#define	HIS_ENPASSANT	0x42
#define	HIS_G50MOVE		0x43
#define	HIS_GMOVES		0x44

#define HIS_W_P 0x45
#define HIS_W_N 0x46
#define HIS_W_B 0x47
#define HIS_W_R 0x48
#define HIS_W_Q 0x49
#define HIS_B_P 0x4A
#define HIS_B_N 0x4B
#define HIS_B_B 0x4C
#define HIS_B_R 0x4D
#define HIS_B_Q 0x4E




// Global Variables:
HINSTANCE hinst;								// current instance
TCHAR sztitle[0x100][MAX_LOADSTRING];					// The title bar text
TCHAR szwindowclass[4][MAX_LOADSTRING];			// the main window class name



HANDLE handle[0x20];
HDC hdc[0x20];

RECT oldr;

HWND hwind[0x200];

SCROLLINFO sci;
long autoflip;

long boarddir = 1;

char str_file[] = "abcdefgh";
char str_rank[] = "12345678";

long gamest_flag = GAMESTATE_NORMAL;

long turn;
long castle;
long enpass;
long g50move;
long gmoves;

long scrl, nep;
long adrp;

char statestr[0x20];

char hissq[0x800][2][0x50];

long screenx = -1;
long screeny = -1;

TCHAR helpstr[0x100];
char helpstra[0x200];

char fenout[0x80];

OVERLAPPED overlp;
SECURITY_ATTRIBUTES sattr;
STARTUPINFO si[4];
PROCESS_INFORMATION pi[4];
HANDLE hinputr[4];
HANDLE houtputr[4];
HANDLE hinputw[4];
HANDLE houtputw[4];
HANDLE hthr[4], hthrout;

char enginepath[4][0x110];

char readstr[0x100000];
char writestr[0x100000];

DWORD readn;

char uciok_flag[4];
char readyok_flag[4];
char calc_flag[4];
long thread_param[4] = {0,1,2,3};

char engdata[0x8000];

//classes	~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



class SQUARE
{
public:
	char file;
	char rank;
	long length;
	long left;
	long top;
	long centx;
	long centy;
	long content;
	long color;
	void setgeometry(long,long,long);
}
sq[8][8],
vsq[8][8],
setgamesq[4],
setpossq[12],
cpsq[0x40],
stosq[8][8],
setlsq[12],
prosq[4],
stacksq;



void SQUARE::setgeometry(long p1, long p2, long p3)
{
	left = p1;
	top = p2;
	length = p3;
	centx = p1+p3/2;
	centy = p2+p3/2;
}


class VECTOR
{
public:
	long sx;
	long sy;
	long dx;
	long dy;
}
mspos;


struct TIMEC
{
	char wtime[0x10];
	char btime[0x10];
	char winc[0x10];
	char binc[0x10];
	char moves[0x10];
	char movetime[0x10];
}
timec;


struct ENGINE_PLAYER
{
	long id;
	long flag;
	long pause;
}
engpl[2];


class ENGINE_INFO
{
public:
	char id_name[0x80];
	char id_author[0x80];
	char option_name[0x40][0x40];
	char option_type[0x40][0x8];
	char option_default[0x40][0x200];
	char option_min[0x40][0x10];
	char option_max[0x40][0x10];
	char option_var[0x40][0x20][0x20];
	char info_depth[0x20][4];
	char info_seldepth[0x20][4];
	char info_score[0x20][0x20];
	char info_time[0x20][0x10];
	char info_nodes[0x20][0x10];
	char info_nps[0x20][0x8];
	char info_tbhits[0x20][8];
	char info_pv[0x20][0x400];
	char info_currmove[8];
	char info_currmovenumber[4];
	char info_hashfull[4];
	char info_cpuload[4];
	char info_string[0x800];
	char bestmove[8];
	char ponder[8];
}
engine[4];


struct ENG_INFO
{
	char depth[4];
	char seldepth[4];
	char score[0x20];
	char time[0x10];
	char nodes[0x10];
	char nps[0x8];
	char tbhits[8];
	char pv[0x400];
	char multipv[2];
}engf;


// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

long win_new(void);
long win_setpos(void);
long win_fen(void);
long win_capture(void);
long win_loadengine(void);
long win_enginepar(long);
long win_engineinfo(long);
long win_loadenginelist(long);
long win_gostop(void);
long win_analoptions(void);
long win_state(long);
long win_timecontrol(void);

void loadresources(void);
void initializeboard(long, long, long);
void paintwnd(HWND);
void paintboard(HDC);
void paintstboard(HDC);
void paintpiece(HDC);
void paintstack(HDC);
long resetboard(void);
void clearboard(void);
long emptyboard(void);
long resetgame(long);
void flipboard(void);
void redrawwin(void);
long setpiece(LPARAM);
long dragpiece(void);
void movepiece(LPARAM);
long droppiece(void);
long isvalidmove(LPVOID,long,VECTOR*);
long isvalidcontrol(long,VECTOR*);
long check4legal(void);
long check4draws(void);
long getposition(LPARAM,SQUARE*);
void redrawrect(long, long);
void completemove(LPARAM);
long pos2fen(void);
long fen2pos(void);
long storepos(void);
long loadpos(long, long);
long captmater(void);
long deltamater(void);
long startprocess(long);
long ucicmd(long);
long isreadycmd(long);
long ucicmd_(LPVOID);
long isreadycmd_(LPVOID);
long calc(long);
long calcp(long);
long stopcalc(long);
void engineoutput(LPVOID);
long dataout(long);
long dataoutx(long);
long sendparam2engine(long);
long domove(long,long,long);
long ucinewgame(long);
long settimec(void);
long translatemove(char*, char*);



void circle(HDC, long, long, long);
void rectn(HDC, long, long, long, long);
void tchar2char(LPVOID par_dest,LPVOID par_src,long par_lng);
void char2tchar(LPVOID par_dest,LPVOID par_src,long par_lng);
long findnull(char*);
long __stdcall cmpmem(LPVOID, LPVOID, long);
void __stdcall copymem(LPVOID, LPVOID, long);
void __stdcall zeromem(LPVOID, long);
