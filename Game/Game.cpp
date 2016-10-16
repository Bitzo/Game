// Game.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Game.h"
#include <vector>
using namespace std;

#define MAX_LOADSTRING 100

// ȫ�ֱ���:
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// �˴���ģ���а����ĺ�����ǰ������:
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

 	// TODO: �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GAME, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GAME));

	// ����Ϣѭ��:
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
//  ����: MyRegisterClass()
//
//  Ŀ��: ע�ᴰ���ࡣ
//
//  ע��:
//
//    ����ϣ��
//    �˴�������ӵ� Windows 95 �еġ�RegisterClassEx��
//    ����֮ǰ�� Win32 ϵͳ����ʱ������Ҫ�˺��������÷������ô˺���ʮ����Ҫ��
//    ����Ӧ�ó���Ϳ��Ի�ù�����
//    ����ʽ��ȷ�ġ�Сͼ�ꡣ
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
//   ����: InitInstance(HINSTANCE, int)
//
//   Ŀ��: ����ʵ�����������������
//
//   ע��:
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

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
//  ����: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��: ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
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
		// �����˵�ѡ��:
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
				//����λͼ
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
				MessageBox(hWnd,_T("������ \t������ \n������ \t������ \nSPACE������"),_T("������"),NULL);
			}else MessageBox(hWnd,_T("Game is running!"),_T("Notice!"),NULL);
			break;
		case ID_RESET://erasebank
			//��Ϸ��סʱ����
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
		//���ƹ����Զ������ƶ�
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
		//���ƻ����ƶ�
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
			//���Ƶ�ͼ
			paintMap(hdc,hWnd);
			//���ƹ���
			PaintMonster(hdc,hWnd);
			//��������
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

// �����ڡ������Ϣ�������
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
