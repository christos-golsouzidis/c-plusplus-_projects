// sudoku3.1.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "sudolib.cpp"
#include "sudoku3.1.h"







int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.

    hfont_fixed = CreateFont(28, 0, 0, 0, 900, 0, 0, 0, 0, 0, 0, 0, 0, 0);
    hfont_var = CreateFont(28, 0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0, 0);

    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SUDOKU31, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SUDOKU31));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SUDOKU31));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(3+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_SUDOKU31);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
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
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);


   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, 3);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
        Createallbuttons(hWnd);
        Createpuzzle();
        break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);

            if (wmId <= 0x209 && wmId >= 0x200)
            {
                PressDigitButton((int)wmId);
            }

            else if (wmId <= 0x1FF && wmId >= 0x100)
            {
                PressGridButton((int)wmId);
                if (CheckIfSolved())
                    MessageBox(hWnd,TEXT("Puzzle solved!"),TEXT("Sudoku3.1"),0x40);
            }

            switch (wmId)
            {
            case ID_FILE_NEWPUZZLE:
                Createpuzzle();
                break;
            case ID_EDIT_RESETPUZZLE:
                Resetpuzzle();
                break;
            case ID_EDIT_SOLVEPUZZLE:
                Solvepuzzle();
                break;
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


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



void PressDigitButton(int winid)
{
    stack = winid - 0x200;
}

void PressGridButton(int winid)
{
    int y = 0;
    int x = 0;
    const WCHAR* _digits[] = { L" ", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", };


    y = winid - 0x100;
    x = winid - 0x100;
    y = y / 9;
    x = x % 9;
    if (visual_puzzle[y][x].enabled == true)
        SendMessage(grid_btn[y][x], WM_SETTEXT, 0, (LPARAM)_digits[stack]);
}


bool CheckIfSolved(void)
{
    int y;
    int x;
    int inhalt;

    y = 0;
    while (y < 9)
    {
        x = 0;
        while (x < 9)
        {

            SendMessage(grid_btn[y][x], WM_GETTEXT, 2, (LPARAM)&inhalt);


            if (inhalt != (0x30 + puzzle_solved.vector[y][x]))
                return false;

            x++;
        }
        y++;
    }
    return true;
}


void Createallbuttons(HWND hWnd)
{
    int bx = 10;
    int by = 10;
    int y_margin, x_margin;
    int length = 60;
    int dy = 0;
    int dx = 0; 
    const WCHAR* digits[] = { L"Clear", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", };

    while (dy < 9)
    {
        if (dy % 3)
            y_margin = 0;
        else
            y_margin = 5;
        dx = 0;
        bx = 150;
        while (dx < 9)
        {
            if (dx % 3)
                x_margin = 0;
            else
                x_margin = 5;
            grid_btn[dy][dx] = CreateWindow(TEXT("BUTTON"), 0, WS_VISIBLE | WS_CHILD,
                bx + x_margin, by + y_margin, length, length, hWnd, (HMENU)(0x100 + 9 * dy + dx), 0, 0);
            bx += length + x_margin;
            dx++;
        }
        by += length + y_margin;
        dy++;
    }
    dy = 0;
    while (dy < 10)
    {
        digit_btn[dy] = CreateWindow(TEXT("BUTTON"), digits[dy], WS_VISIBLE | WS_CHILD,
            750, 15 + length * dy, length, length, hWnd, (HMENU)(0x200 + dy), 0, 0);
        //bx += length;
        dy++;
    }

}


void Displaypuzzle(void)
{
    int x, y;
    const WCHAR* digits[] = { L" ", L"1", L"2", L"3", L"4", L"5", L"6", L"7", L"8", L"9", };

    y = 0;
    while (y < 9)
    {
        x = 0;
        while (x < 9)
        {
            if(visual_puzzle[y][x].enabled == false)
                SendMessage(grid_btn[y][x], WM_SETFONT, (WPARAM)hfont_fixed, MAKELPARAM(true, 0));
            else
                SendMessage(grid_btn[y][x], WM_SETFONT, (WPARAM)hfont_var, MAKELPARAM(true, 0));

            SendMessage(grid_btn[y][x], WM_SETTEXT, 0, (LPARAM)digits[puzzle.vector[y][x]]);
            x++;
        }
        y++;
    }
}


void Addfeatures(void)
{
    int x, y;
    y = 0;
    while (y < 9)
    {
        x = 0;
        while (x < 9)
        {
            if (puzzle.vector[y][x] == 0)
                visual_puzzle[y][x].enabled = true;
            else
                visual_puzzle[y][x].enabled = false;

            x++;
        }
        y++;
    }
}


void Createpuzzle()
{
    g_random = time(0);
    srand(g_random);
    puzzle.Fillgrid();
    puzzle_solved = puzzle;
    puzzle.Removedigits(0x80);
    Addfeatures();
    Displaypuzzle();
}


void Resetpuzzle()
{
    srand(g_random);
    puzzle.Fillgrid();
    puzzle.Removedigits(0x80);
    Addfeatures();
    Displaypuzzle();
}


void Solvepuzzle()
{
    puzzle.Solveit(puzzle.vector[0]);
    Addfeatures();
    Displaypuzzle();
}













