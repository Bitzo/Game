#include "StdAfx.h"
#include "Game.h"
#include <Windows.h>
//主人公的各项动作

//设置位置
void people::setValue(int x,int y)
{
	x_s=x;
	y_s=y;
}

bool people::control_DOWN()
{
	_sta=Down;
	int _y=y_s;
	if(y_s<100) _y=60;
	if (_y<300&&Climb[level][(_y-100)/40+1][(x_s-30)/35+1]==1&&(_y-100)/40+1<6&&(_y-100)/40+1>=0&&(x_s-30)/35+1>=0&&(x_s-30)/35+1<=9)//j*35+25 i*40+85
	{
		x=0;
		y=5;
		return true;
	}else return false;
}

bool people::control_LEFT()
{
	int _y=y_s,_x=x_s;
	if(y_s<100) _y=45;
	if (x_s<55) _x=15;
	if (x_s>25&&(y_s-20)%40==0&&(map[level][(_y-85)/40+1][(_x-55)/35+1]==1||map[level][(_y-85)/40+1][(_x-85)/35+1]==1||map[level][(_y-85)/40+1][(_x-115)/35+1]==1)||(_y==300&&x_s>25))
	{
		_sta=Left;
		x=-5;
		y=0;
		return true;
	}else return false;
}

bool people::control_RIGHT()
{
	int _y=y_s,_x=x_s;
 	if(y_s<100) _y=45;
	if (x_s<85) _x=50;
	if (x_s<350&&(y_s-20)%40==0&&(map[level][(_y-85)/40+1][(_x-50)/35+1]==1||map[level][(_y-85)/40+1][(_x-85)/35+1]==1||map[level][(_y-85)/40+1][(_x-100)/35+1]==1)||(_y==300&&_x<350))//j*35+25,i*40+85,
	{
		_sta=Right;
		x=5;
		y=0;
		return true;
	}else return false;
}
bool people::control_UP()
{
	if (y_s>60&&Climb[level][(y_s-65)/40][(x_s-15)/35]==1&&(y_s-65)/40<6&&(y_s-65)/40>=0&&(x_s-15)/35>=0&&(x_s-15)/35<=9)
	{
		_sta=Up;
		x=0;
		y=-5;
		return true;
	}else return false;
}

bool people::control_SPACE()
{
	if ((y_s-20)%40==0) {
		WEPEN _wepen(x_s,y_s,true,0,MainRole.getSTA());
		wepen.push_back(_wepen);
		PlaySound(_T("./wav/wepen.wav"),NULL,SND_FILENAME|SND_ASYNC);
		return true;
	}else return false;
}