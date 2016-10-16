// Game.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "Game.h"
#include <vector>
using namespace std;

#define MAX_LOADSTRING 100

// 全局变量:
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 此代码模块中包含的函数的前向声明:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: 在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

	// 主消息循环:
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



//
//  函数: MyRegisterClass()
//
//  目的: 注册窗口类。
//
//  注释:
//
//    仅当希望
//    此代码与添加到 Windows 95 中的“RegisterClassEx”
//    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
//    这样应用程序就可以获得关联的
//    “格式正确的”小图标。
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAME));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GAME);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   函数: InitInstance(HINSTANCE, int)
//
//   目的: 保存实例句柄并创建主窗口
//
//   注释:
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW^WS_THICKFRAME^WS_MAXIMIZEBOX,
	   CW_USEDEFAULT, 0, 400, 400, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  函数: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的: 处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
//
//
int x=0,y=0;
int score=0;
bool start=false;
people MainRole(25,300);
_Monster Monster[10];
vector <WEPEN> wepen;
HBITMAP hbmp1,hbmp2,hbmp3,hbmp6,hbmp9,hbmp10,hbmp11,hbmp5,hbmp8;
int level=0;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_START:
			if (!start)
			{
				CreateMonster(hWnd);
				//载入位图
				hbmp1 = (HBITMAP)LoadImage(NULL, _T("bitmap1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				hbmp2 = (HBITMAP)LoadImage(NULL, _T("bitmap2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				hbmp3 = (HBITMAP)LoadImage(NULL, _T("bitmap3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				hbmp6 = (HBITMAP)LoadImage(NULL, _T("bitmap6.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				hbmp9 = (HBITMAP)LoadImage(NULL, _T("bitmap9.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				hbmp10 = (HBITMAP)LoadImage(NULL, _T("bitmap10.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				hbmp11 = (HBITMAP)LoadImage(NULL, _T("bitmap11.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				hbmp5 = (HBITMAP)LoadImage(NULL, _T("bitmap5.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				hbmp8 = (HBITMAP)LoadImage(NULL, _T("bitmap8.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE|LR_CREATEDIBSECTION);
				start = true;
				::InvalidateRect(hWnd, NULL, 1);
				MessageBox(hWnd,_T("↑：上 \t↓：下 \n←：左 \t→：右 \nSPACE：攻击"),_T("操作："),NULL);
			}else MessageBox(hWnd,_T("Game is running!"),_T("Notice!"),NULL);
			break;
		case ID_RESET://erasebank
			//游戏卡住时重置
			for (int i=1;i<6;++i)
				for(int j=0;j<9;++j)
					Key[level][i][j]=map[level][i][j];
			KillTimer(hWnd,1);
			KillTimer(hWnd,3);
			wepen.clear();
			MainRole.setValue(25,300);
			score=0;CreateMonster(hWnd);
			::InvalidateRect(hWnd, NULL, 1);
			break;
		case ID_Pause:
			start=false;
			KillTimer(hWnd,1);
			KillTimer(hWnd,3);
			wepen.clear();
			break;
		case ID_Restart:
			start=true;
			SetTimer(hWnd,2,500,NULL);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_KEYDOWN:
		switch (wParam) 
		{
		case VK_LEFT:
			if(start==true)
			if(MainRole.control_LEFT())
			::InvalidateRect(hWnd, NULL, 1);
			break;
		case  VK_RIGHT:
			if(start==true)
			if(MainRole.control_RIGHT())
			::InvalidateRect(hWnd, NULL, 1);
			break;
		case VK_DOWN:
			if(start==true)
			if(MainRole.control_DOWN())
			::InvalidateRect(hWnd, NULL, 1);
			break;
		case VK_UP:
			if(start==true)
			if(MainRole.control_UP())
			::InvalidateRect(hWnd, NULL, 1);
			break;
		case VK_SPACE:
			if(start==true)
			if (MainRole.control_SPACE()){
				SetTimer(hWnd,3,50,NULL);
				::InvalidateRect(hWnd, NULL, 1);
			}
			break;
		}break;
	case WM_TIMER:
		//控制怪物自动来回移动
		if (wParam==1){
			for(int i=0;i<10;++i){
				if (Monster[i].getSTA()==Right)
				{
					Monster[i].setValue(Monster[i].getX()+5,Monster[i].getY(),Monster[i].getLive());
					Monster[i].setT(Monster[i].getT()+5);
				}
				if (Monster[i].getSTA()==Left)
				{
					Monster[i].setValue(Monster[i].getX()-5,Monster[i].getY(),Monster[i].getLive());
					Monster[i].setT(Monster[i].getT()-5);
				}
			}
			::InvalidateRect(hWnd, NULL, 1);
		}
		//控制火球移动
		if(wParam==3){
			for (unsigned int i=0;i<wepen.size();++i)
			{
				switch(wepen[i].getSTA())
				{
				case Left:
					wepen[i].setValue(wepen[i].getX()-5,wepen[i].getY());
					wepen[i].setT(wepen[i].getT()-5);
					break;
				default:
				case Right:
					wepen[i].setValue(wepen[i].getX()+5,wepen[i].getY());
					wepen[i].setT(wepen[i].getT()+5);
					break;
				}		
			}
			::InvalidateRect(hWnd, NULL, 1);
		}
		break;
	case WM_PAINT:
		if (start==true)
		{
			hdc = BeginPaint(hWnd,&ps);
			//绘制地图
			paintMap(hdc,hWnd);
			//绘制怪物
			PaintMonster(hdc,hWnd);
			//绘制人物
			switch(MainRole.getSTA())
			{
			case Up:winPaint(hdc,hWnd,hbmp3,hbmp11);break;
			case Left:winPaint(hdc,hWnd,hbmp2,hbmp11);break;
			case Right:winPaint(hdc,hWnd,hbmp1,hbmp11);break;
			default:winPaint(hdc,hWnd,hbmp1,hbmp11);break;
			}
			EndPaint(hWnd,&ps);
		}
		break;
	case WM_DESTROY:
		DeleteObject(hbmp1);
		DeleteObject(hbmp10);
		DeleteObject(hbmp11);
		DeleteObject(hbmp2);
		DeleteObject(hbmp3);
		DeleteObject(hbmp6);
		DeleteObject(hbmp5);
		DeleteObject(hbmp9);
		DeleteObject(hbmp8);
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// “关于”框的消息处理程序。
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
