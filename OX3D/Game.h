#pragma once
#include <Windows.h>
#include "BMPFile.h"
#include "CheckBoard.h"
#define Left 29
#define BlockWidth 43


class Game
{
	public:
		Game(void);
		~Game(void);
		void Update();
		void Draw();
		void UpdateControl(UINT msg,WPARAM wParam,LPARAM lParam);
		
		void Initialize(HWND _hWnd);
	private:		
		CheckBoard board;
		int MouseX;
		int MouseY;
		int LeftButton;
		int state[3][3][3];
		int isEnd;

		int currentPlayer;
		int lastLeft;
		int lastX;
		int lastY;
		HWND hWnd;
		int isClicked(int x1,int y1,int x2,int y2);
		int whoWin();
};

