#pragma once
#include "BMPFile.h"
#define BlockLength 0.2
#define OrginalX	0.2
#define OrginalY	0.05
#define OrginalZ	-2.3
#define MaxRotation 60
class CheckBoard
{
	public:
		CheckBoard(void);
		BMPFile Board;
		BMPFile Red;
		BMPFile Blue;
		float RotationX;
		float RotationY;//¶ÈÊý
		void Initialize();
		void Draw(int state[3][3][3]);
		void SetTempBall(int x,int y,int z);
		void DisableTempBall();
		~CheckBoard(void);
	private:		
		float BoardVerts[24][3];//¶¥µã
		void setVert(int i,float x,float y,float z);
		void DrawBall(int x,int y,int z,int p);

		int enableTemp;
		int tempX;
		int tempY;
		int tempZ;
		
};
