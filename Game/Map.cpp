#include "StdAfx.h"
#include "Game.h"

//地图模版 1为有平台 0为无平台
bool map[2][6][9]={
	0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 ,
    0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 ,
	0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 ,

	0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 ,
	0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 0 ,
	0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 ,
};


//对应的钥匙模版 方便更新数据
bool Key[2][6][9]={
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 ,
	0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 ,
	0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 ,

	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 ,
	0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 0 ,
	0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 ,
};

bool Climb[2][6][9]={
	0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 ,
	0 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 ,

	0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 0 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 ,
	0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 ,
};

bool monster[2][6][9]={
	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 ,
	0 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 1 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 ,
	0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 , 0 ,

	0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ,
	0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 0 ,
	0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 1 , 0 , 0 , 0 ,
	0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 ,
	0 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 0 ,
};


//绘制地图平台
void paintMap(HDC hdc,HWND hWnd)
{
	//绘制窗口四周的背景方块//
	HDC hdcMem;
	hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, hbmp9);
	//BitBlt(hdc,0, 0, 400, 350, hdcMem,0, 0, SRCCOPY);
	TransparentBlt(hdc,0, 0, 400, 350,hdcMem,0,0, 400, 350,RGB(255,255,255));
	for (int i=0;i<6;++i)
	{
		for (int j=0;j<9;++j)
		{
				////绘制平台
				if (map[level][i][j]==1)
				{
					SelectObject(hdcMem, hbmp5);
					//BitBlt(hdc,j*35+25,i*40+85, 90, 5, hdcMem,0, 0, SRCCOPY);
					TransparentBlt(hdc,j*35+25,i*40+85, 90, 5,hdcMem,0,0, 90, 5,RGB(255,255,255));
				}
				//绘制平台上的钥匙
				if (Key[level][i][j]==1)
				{
					SelectObject(hdcMem, hbmp6);
					//BitBlt(hdc,j*35+75,i*40+70, 15, 15, hdcMem,0, 0, SRCCOPY);
					TransparentBlt(hdc,j*35+75,i*40+70, 15, 15,hdcMem,0,0, 15, 15,RGB(255,255,255));
				}
				//绘制楼梯
				if (Climb[level][i][j]==1)
				{
					SelectObject(hdcMem, hbmp8);
					//BitBlt(hdc,j*35+25,i*40+85, 20, 40, hdcMem,0, 0, SRCCOPY);
					TransparentBlt(hdc,j*35+25,i*40+85, 20, 40,hdcMem,0,0, 20, 40,RGB(255,255,255));
				}
				if (i==0)
				{
					//判断是否通关
					if (score==10&&j*35+55<=MainRole.getX()&&MainRole.getX()<=j*35+60&&MainRole.getY()==60)
					{
						KillTimer(hWnd,1);
						KillTimer(hWnd,3);
						wepen.clear();
						PlaySound(_T("./wav/win.wav"),NULL,SND_FILENAME|SND_ASYNC);
						if(MessageBox(hWnd,_T("You Win!!"),TEXT("Winner"),MB_OK)==IDOK)
						{
							for (int i=1;i<6;++i)
								for(int j=0;j<9;++j)
									Key[level][i][j]=map[level][i][j];
							if (level==0) level++;
							else if (level==1) level--;
							MainRole.setValue(25,300);
							score=0;
							CreateMonster(hWnd);
						}
					}
				}
				//判断是否拿到钥匙
				if (MainRole.getX()<=j*35+75&&MainRole.getX()>=j*35+65&&MainRole.getY()==i*40+60&&Key[level][i][j]==1&&MainRole.getY()!=60)
				{
					Key[level][i][j]=0;
					score++;
					if (i==0) i=0;
				}
		}
	}
	DeleteDC(hdcMem);
}