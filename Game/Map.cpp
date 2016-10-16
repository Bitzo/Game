#include "StdAfx.h"
#include "Game.h"

//��ͼģ�� 1Ϊ��ƽ̨ 0Ϊ��ƽ̨
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


//��Ӧ��Կ��ģ�� �����������
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


//���Ƶ�ͼƽ̨
void paintMap(HDC hdc,HWND hWnd)
{
	//���ƴ������ܵı�������//
	HDC hdcMem;
	hdcMem = CreateCompatibleDC(hdc);
	SelectObject(hdcMem, hbmp9);
	//BitBlt(hdc,0, 0, 400, 350, hdcMem,0, 0, SRCCOPY);
	TransparentBlt(hdc,0, 0, 400, 350,hdcMem,0,0, 400, 350,RGB(255,255,255));
	for (int i=0;i<6;++i)
	{
		for (int j=0;j<9;++j)
		{
				////����ƽ̨
				if (map[level][i][j]==1)
				{
					SelectObject(hdcMem, hbmp5);
					//BitBlt(hdc,j*35+25,i*40+85, 90, 5, hdcMem,0, 0, SRCCOPY);
					TransparentBlt(hdc,j*35+25,i*40+85, 90, 5,hdcMem,0,0, 90, 5,RGB(255,255,255));
				}
				//����ƽ̨�ϵ�Կ��
				if (Key[level][i][j]==1)
				{
					SelectObject(hdcMem, hbmp6);
					//BitBlt(hdc,j*35+75,i*40+70, 15, 15, hdcMem,0, 0, SRCCOPY);
					TransparentBlt(hdc,j*35+75,i*40+70, 15, 15,hdcMem,0,0, 15, 15,RGB(255,255,255));
				}
				//����¥��
				if (Climb[level][i][j]==1)
				{
					SelectObject(hdcMem, hbmp8);
					//BitBlt(hdc,j*35+25,i*40+85, 20, 40, hdcMem,0, 0, SRCCOPY);
					TransparentBlt(hdc,j*35+25,i*40+85, 20, 40,hdcMem,0,0, 20, 40,RGB(255,255,255));
				}
				if (i==0)
				{
					//�ж��Ƿ�ͨ��
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
				//�ж��Ƿ��õ�Կ��
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