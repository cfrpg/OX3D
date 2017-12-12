#include "StdAfx.h"
#include "CheckBoard.h"
#define BoardTexturePath "Images\\a.bmp"
#define RedTexturePath "Images\\r2.bmp"
#define BlueTexturePath "Images\\b2.bmp"

CheckBoard::CheckBoard(void)
{
	
}

void CheckBoard::Initialize()
{
	Board=BMPFile();
	Red=BMPFile();
	Blue=BMPFile();
	Board.Load(BoardTexturePath);
	Red.Load(RedTexturePath);
	Blue.Load(BlueTexturePath);

	for(int i=1;i<3;i++)
	{
		setVert(i*8+0-8,0,i*BlockLength,-BlockLength);
		setVert(i*8+1-8,3*BlockLength,i*BlockLength,-BlockLength);
		setVert(i*8+2-8,0,i*BlockLength,-2*BlockLength);
		setVert(i*8+3-8,3*BlockLength,i*BlockLength,-2*BlockLength);
		setVert(i*8+4-8,BlockLength,i*BlockLength,0);
		setVert(i*8+5-8,BlockLength,i*BlockLength,-3*BlockLength);
		setVert(i*8+6-8,2*BlockLength,i*BlockLength,0);
		setVert(i*8+7-8,2*BlockLength,i*BlockLength,-3*BlockLength);
	}
	setVert(16,BlockLength,0,-BlockLength);
	setVert(17,BlockLength,3*BlockLength,-BlockLength);
	setVert(18,2*BlockLength,0,-BlockLength);
	setVert(19,2*BlockLength,3*BlockLength,-BlockLength);
	setVert(20,BlockLength,0,-2*BlockLength);
	setVert(21,BlockLength,3*BlockLength,-2*BlockLength);
	setVert(22,2*BlockLength,0,-2*BlockLength);
	setVert(23,2*BlockLength,3*BlockLength,-2*BlockLength);
	for(int i=0;i<24;i++)
	{
		BoardVerts[i][0]-=1.5*BlockLength;
		BoardVerts[i][1]-=1.5*BlockLength;
		BoardVerts[i][2]+=1.5*BlockLength;
	}
	enableTemp=0;

}

void CheckBoard::Draw(int state[3][3][3])
{
	float xoff=0.225,yoff=0.225,x=-1.64;
	float y[3]={-1.15,-1.15+0.84,-1.15+0.835*2};
	Board.Draw(-1.7,-1.2+0,-5);
	Board.Draw(-1.7,-1.2+0.85,-5);
	Board.Draw(-1.7,-1.2+1.7,-5);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			for(int k=0;k<3;k++)
			{
				if(state[i][j][k]==1)
				{
					Red.Draw(x+xoff*j,y[i]+yoff*k,-4.9);
				}
				if(state[i][j][k]==2)
				{
					Blue.Draw(x+xoff*j,y[i]+yoff*k,-4.9);
				}
				DrawBall(i,j,k,state[i][j][k]);				
			}
		}
	}
	if(enableTemp==1)
	{
		DrawBall(tempX,tempY,tempZ,3);
		enableTemp=0;
	}
	glDisable(GL_LIGHTING);
	glPointSize(5.0); 
	glLineWidth(3.0);
	glEnable(GL_LINE_SMOOTH);
	
	glPushMatrix();
	
	glTranslated(OrginalX,OrginalY,OrginalZ);
	glRotatef(RotationX, 1.0, 0.0, 0.0); //旋转矩阵
	glRotatef(RotationY, 0.0, 1.0, 0.0); //旋转矩阵
	glBegin(GL_LINES);
	glColor3f(0.0f, 1.0f, 1.0f);
	for(int i=0;i<8;i++)
	{
		glVertex3fv(BoardVerts[i]);
	}
	glColor3f(1.0f, 1.0f, 0.0f);
	for(int i=8;i<16;i++)
	{
		glVertex3fv(BoardVerts[i]);
	}
	glColor3f(1.0f, 0.0f, 1.0f);
	for(int i=16;i<24;i++)
	{
		glVertex3fv(BoardVerts[i]);
	}
	glEnd();
	glPopMatrix(); //将当前矩阵弹出堆栈
	glPointSize(6.0); 
	glLineWidth(1.0);
	glBegin(GL_POINTS);
	glColor3f(0.0,1.0,0.0);
	glVertex3f(RotationY/MaxRotation*0.8+0.5,-1,-5);
	glVertex3f(1.5,-RotationX/MaxRotation*0.6,-5);
	glEnd();
	glBegin(GL_LINES);
	glVertex3f(MaxRotation/MaxRotation*0.8+0.5,-1,-5);
	glVertex3f(-MaxRotation/MaxRotation*0.8+0.5,-1,-5);
	glVertex3f(1.5,MaxRotation/MaxRotation*0.6,-5);
	glVertex3f(1.5,-MaxRotation/MaxRotation*0.6,-5);
	glEnd();
	
}

void CheckBoard::setVert(int i,float x,float y,float z)
{
	BoardVerts[i][0]=x;
	BoardVerts[i][1]=y;
	BoardVerts[i][2]=z;
}

void CheckBoard::DrawBall(int x,int y,int z,int p)
{
	float vx,vy,vz,r;
	GLUquadricObj* q;
	float color[]={0.0,0.0,0.0,1.0};
	r=BlockLength/3;
	if(p==0)
		return;
	if(p==1)
	{
		color[0]=1.0;
	}
	else if(p==2)
	{
		color[2]=1.0;
	}
	else
	{
		color[1]=0.7;
		r/=1.5;
	}
	vx=(y-1)*BlockLength;
	vy=(x-1)*BlockLength;
	vz=-(z-1)*BlockLength;
	glPushMatrix();
	glTranslated(OrginalX,OrginalY,OrginalZ);
	glRotatef(RotationX, 1.0, 0.0, 0.0); //旋转矩阵
	glRotatef(RotationY, 0.0, 1.0, 0.0); //旋转矩阵
	glTranslated(vx,vy,vz);
	glMaterialfv(GL_FRONT,GL_EMISSION,color);
	q = gluNewQuadric(); //创建二次曲面对象
	gluQuadricDrawStyle(q,GLU_FILL); //多边形和三角条状元填充曲面
	gluQuadricNormals(q,GLU_SMOOTH); //为每个顶点生成光照标准
	gluSphere(q,r,50,50); //绘制球体
	gluDeleteQuadric(q); //删除二次曲面对象
	glPopMatrix();

}

void CheckBoard::DisableTempBall()
{
	enableTemp=0;
}
void CheckBoard::SetTempBall(int x,int y,int z)
{
	enableTemp=1;
	tempX=x;
	tempY=y;
	tempZ=z;
}

CheckBoard::~CheckBoard(void)
{

}
