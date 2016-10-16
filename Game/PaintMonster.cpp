#include "StdAfx.h"
#include "Game.h"
#include <Windows.h>
#include <cmath>
#include <time.h>

void CreateMonster(HWND hWnd){
		int i=0;
		srand((unsigned)time(NULL));
		for (int j=0;j<6;++j)
			for (int k=0;k<9;++k)
				if (monster[level][j][k]==1)
				{
					int t=rand()%60;
					Monster[i].setValue(k*35+25+t,j*40+65,true);
					Monster[i].setSTA(rand()%2?Right:Left);
					Monster[i].setHp(level+1);
					Monster[i++].setT(t);
				}
				if (level==0){SetTimer(hWnd,1,500,NULL);
				}else SetTimer(hWnd,1,200,NULL);
}

void PaintMonster(HDC hdc,HWND hWnd)
{
	//根据怪物的位移t改变方向
	for (int i=0;i<10;++i)
	{
		if (Monster[i].getT()>=70)
		{	
			Monster[i].setSTA(Left);
		}else if(Monster[i].getT()<=0){
			Monster[i].setSTA(Right);
		}
	}
	for (int i=0;i<10;++i)
	{
		//绘制存活的怪物
		if (Monster[i].getLive()==true)
		{
			HDC hdcMem;
			hdcMem = CreateCompatibleDC(hdc);
			SelectObject(hdcMem, hbmp10);
			//BitBlt(hdc,Monster[i].getX(),Monster[i].getY(), 25, 20, hdcMem,0, 0, SRCCOPY);
			TransparentBlt(hdc,Monster[i].getX(),Monster[i].getY(), 25, 20,hdcMem,0,0, 25, 20,RGB(255,255,255));
			DeleteDC(hdcMem);
		}
		//判断怪物是否被杀死
		for (unsigned int j=0;j<wepen.size();++j)
		{
			if ((abs(wepen[j].getX()-Monster[i].getX())<=5)&&(abs(wepen[j].getY()-Monster[i].getY())<=20))
			{
				Monster[i].setHp(Monster[i].getHp()-1);
				if(Monster[i].getHp()==0){
					Monster[i].setValue(0,0,false);
					wepen[j].setI(false);
				}
				//杀死怪物的同时清除掉武器
				vector<WEPEN>::iterator k = wepen.begin()+j;
				wepen.erase(k);
				PlaySound(_T("./wav/monster_die.wav"),NULL,SND_FILENAME|SND_ASYNC);
				if (wepen.size()==0)
				{
					KillTimer(hWnd,3);
				}
			}
		}
		//判断主人公是否碰到怪物
		if ((abs(MainRole.getX()-Monster[i].getX())<=15)&&(abs(MainRole.getY()-Monster[i].getY())<=5))
		{
			KillTimer(hWnd,1);
			KillTimer(hWnd,3);
			PlaySound(_T("./wav/lose.wav"),NULL,SND_FILENAME|SND_ASYNC);
			if(MessageBox(hWnd,_T("Lose!!"),TEXT("Winner"),MB_OK)==IDOK)
			{
				for (int i=1;i<6;++i)
					for(int j=0;j<9;++j)
						Key[level][i][j]=map[level][i][j];
				wepen.clear();
				MainRole.setValue(25,300);
				score=0;
				CreateMonster(hWnd);
			}
		}
	}
}