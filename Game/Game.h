#pragma once
#include "stdafx.h"
#include "resource.h"
#include <vector>
#include <Windows.h>
using namespace std;

#include <mmsystem.h>
#pragma comment(lib, "WINMM.LIB")


//全局变量声明//
extern int x,y;
typedef enum {Right,Left,Up,Down}sta;
extern int score;
extern bool map[2][6][9],Key[2][6][9],Climb[2][6][9],monster[2][6][9];
extern bool start;
extern int level;
extern HBITMAP hbmp1,hbmp2,hbmp3,hbmp6,hbmp9,hbmp10,hbmp11,hbmp5,hbmp8;



//Control.cpp 函数声明//

class WEPEN
{
public:
	WEPEN(int x=0,int y=0,bool i=true,int t=0,sta s=Right):x(x),y(y),isLive(i),t(t),_sta(s){};
	int getX()const{return x;};
	int getY()const{return y;}
	int getT()const{return t;}
	sta getSTA()const{return _sta;}
	bool getI(){return isLive;}
	void setValue(int x,int y){
		this->x=x;
		this->y=y;
	}
	void setI(bool i){this->isLive=i;}
	void setT(int t){this->t=t;}
	~WEPEN(){};
protected:
private:
	int x,y,t;
	bool isLive;
	sta _sta;
};


class people
{
public:
	people();
	people(int x,int y):x_s(x),y_s(y){};
	int getX() const{return x_s;}
	int getY() const{return y_s;}
	sta getSTA() const{return _sta;}
	void setValue(int x,int y);
	bool control_UP();
	bool control_DOWN();
	bool control_LEFT();
	bool control_RIGHT();
	bool control_SPACE();
	~people(){}
protected:
private:
	int x_s,y_s;
	sta _sta;
};
extern vector<WEPEN> wepen;
extern people MainRole;


//WM_Paint.cpp 函数声明//
void winPaint(HDC hdc,HWND hWnd,HBITMAP hbmp1,HBITMAP hbmp11);

//Map.cpp 函数声明//
void paintMap(HDC hdc,HWND hWnd);

//monster

class _Monster
{
public:
	_Monster(int x=0,int y=0,bool i=true,int t=0,sta S=Right,int hp=0):x_s(x),y_s(y),Islive(i),t(t),STA(S),HP(hp){};
	int getX()const{return x_s;}
	int getY()const{return y_s;}
	int getT()const{return t;}
	sta getSTA()const{return STA;};
	int getHp()const{return HP;};
	bool getLive()const{return Islive;}
	void setValue(int x,int y,bool i);
	void setT(int t){this->t=t;}
	void setSTA(sta s){this->STA=s;};
	void setHp(int i){HP=i;};
	~_Monster(){};
protected:
private:
	int x_s,y_s,t;
	bool Islive;
	sta	STA;
	int HP;
};
extern _Monster Monster[10];

void CreateMonster(HWND hWnd);

void PaintMonster(HDC hdc,HWND hWnd);
