#include "StdAfx.h"
#include "Game.h"


Game::Game(void)
{

}

void Game::Initialize(HWND _hWnd)
{	
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				state[i][j][k]=0;
			}
		}
	}
	hWnd=_hWnd;
	currentPlayer=1;
	isEnd=0;
	
	board.Initialize();
}



void Game::UpdateControl(UINT msg,WPARAM wParam,LPARAM lParam)
{
	switch(msg)
	{
		case WM_MOUSEMOVE:
			MouseX=LOWORD(lParam);
			MouseY=HIWORD(lParam);
			break;
		case WM_LBUTTONDOWN:
			LeftButton=1;
			break;
		case WM_LBUTTONUP:
			LeftButton=0;
			break;
		
	}
}

void Game::Update()
{
	int tx=0,ty=0,tz=0,flag=0,win=0;
	if(isClicked(220,0,700,550))
	{
		if(LeftButton==1)
		{			
			board.RotationY+=(MouseX-lastX)/3;
			board.RotationX+=(MouseY-lastY)/3;	
			if(board.RotationX>MaxRotation)
				board.RotationX=MaxRotation;
			if(board.RotationX<-MaxRotation)
				board.RotationX=-MaxRotation;
			if(board.RotationY>MaxRotation)
				board.RotationY=MaxRotation;
			if(board.RotationY<-MaxRotation)
				board.RotationY=-MaxRotation;
		}
	}
	if(isClicked(Left,76-47,155,200-47))
	{
		tx=2;
		ty=(MouseX-Left)/BlockWidth;
		tz=2-(MouseY-76+47)/42;
		flag=1;
	}
	if(isClicked(33,235-47,155,360-47))
	{
		tx=1;
		ty=(MouseX-Left)/BlockWidth;
		tz=2-(MouseY-235+47)/42;
		flag=1;
	}
	if(isClicked(Left,394-47,155,519-47))
	{
		tx=0;
		ty=(MouseX-Left)/BlockWidth;
		tz=2-(MouseY-394+47)/42;
		flag=1;
	}
	if(isEnd==0&&flag==1)
	{
		if(LeftButton==1&&lastLeft==0)
		{
			if(state[tx][ty][tz]==0)
			{
			
				state[tx][ty][tz]=currentPlayer;
				currentPlayer=currentPlayer==1?2:1;
			}
		}
		else
		{
			if(state[tx][ty][tz]==0)
				board.SetTempBall(tx,ty,tz);
		}

	}
	
	if(isEnd==1)
	{
		win=whoWin();
		if(win!=0)
		{
			if(win==2)
				MessageBoxA(hWnd,"Player 1£¨Red£© win!","OX3D",MB_OK);
			else
				MessageBoxA(hWnd,"Player 2£¨Blue£© win!","OX3D",MB_OK);
			isEnd=2;
		}
	}
	if(isEnd==0)
	{
		win=whoWin();
		if(win!=0)
		{
			
			isEnd=1;
		}
	}
	
	lastLeft=LeftButton;
	lastX=MouseX;
	lastY=MouseY;
	
}

void Game::Draw()
{	
	glClearColor(0,0,0,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); //Çå³ý»º³åÇø		
	board.Draw(state);
	
}

Game::~Game(void)
{

}

int Game::isClicked(int x1,int y1,int x2,int y2)
{
	if(MouseX>=x1&&MouseX<=x2&&MouseY>=y1&&MouseY<=y2)
		return 1;
	return 0;
}
int Game::whoWin()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(state[i][j][0]==state[i][j][1]&&state[i][j][1]==state[i][j][2])
			{
				if(state[i][j][0]!=0)
				{					
					return state[i][j][0];
				}
				
			}
		}
		for(int k=0;k<3;k++)
		{
			if(state[i][0][k]==state[i][1][k]&&state[i][1][k]==state[i][2][k])
			{
				if(state[i][0][k]!=0)
				{
					
					return state[i][0][k];
				}
				
			}
		}
		if(state[i][0][0]==state[i][1][1]&&state[i][1][1]==state[i][2][2])
		{
			if(state[i][0][0]!=0)
				return state[i][0][0];
		}
		if(state[i][0][2]==state[i][1][1]&&state[i][1][1]==state[i][2][0])
		{
			if(state[i][0][2]!=0)
				return state[i][0][2];
		}
	}
	for(int j=-0;j<3;j++)
	{
		for(int k=0;k<3;k++)
		{
			if(state[0][j][k]==state[1][j][k]&&state[1][j][k]==state[2][j][k])
			{
				if(state[0][j][k]!=0)
				{
					return state[0][j][k];
				}
			}
		}
	}
	if(state[0][0][0]==state[1][1][1]&&state[1][1][1]==state[2][2][2]&&state[1][1][1]!=0)
	{
		return state[1][1][1];
	}
	if(state[0][0][2]==state[1][1][1]&&state[1][1][1]==state[2][2][0]&&state[1][1][1]!=0)
	{
		return state[1][1][1];
	}
	if(state[0][2][0]==state[1][1][1]&&state[1][1][1]==state[2][0][2]&&state[1][1][1]!=0)
	{
		return state[1][1][1];
	}
	if(state[0][2][2]==state[1][1][1]&&state[1][1][1]==state[2][0][0]&&state[1][1][1]!=0)
	{
		return state[1][1][1];
	}
	return 0;
}
