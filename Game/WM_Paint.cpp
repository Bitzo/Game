#include "StdAfx.h"
#include "Game.h"

void winPaint(HDC hdc,HWND hWnd,HBITMAP hbmp1,HBITMAP hbmp11)
{
	HDC hdcMem;
	hdcMem = CreateCompatibleDC(hdc);
	//根据按键选择绘制不同的角色状态图//
	SelectObject(hdcMem, hbmp1);
	TransparentBlt(hdc,MainRole.getX()+x,MainRole.getY()+y, 25, 25,hdcMem,0,0, 25, 25,RGB(255,255,255));
	MainRole.setValue(MainRole.getX()+x,MainRole.getY()+y);
	x=y=0;
		for (unsigned int i=0;i<wepen.size();++i)
		{
			if (wepen[i].getI()==true)
			{
				SelectObject(hdcMem, hbmp11);
			//	BitBlt(hdc,wepen[i].getX(),wepen[i].getY(),10,10,hdcMem,0,0,SRCCOPY);
				TransparentBlt(hdc,wepen[i].getX(),wepen[i].getY(),10,10,hdcMem,0,0, 10, 10,RGB(255,255,255));
			}else KillTimer(hWnd,3);
			//武器到达最远距离被清除
			if (wepen[i].getT()==80||wepen[i].getT()==-80){
				wepen[i].setI(false);
				vector<WEPEN>::iterator k = wepen.begin();
				wepen.erase(k);
			}
			if (wepen.size()==0)
			{
				KillTimer(hWnd,3);
			}
		}
		DeleteDC(hdcMem);
}