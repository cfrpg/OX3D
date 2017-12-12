#include "StdAfx.h"
#include "BMPFile.h"


BMPFile::BMPFile(void)
{
	Width=0;
	Height=0;
	Length=0;
	
}



int BMPFile::Load(char *path)
{
	FILE *fp=fopen(path,"rb");
	if(fp==NULL)
	{
		return -1;
	}
	fseek(fp,0x0012,SEEK_SET);
	fread(&Width,sizeof(Width),1,fp);
	fread(&Height,sizeof(Height),1,fp);
	Length=Width*4;
	while(Length%4!=0)
		Length++;
	Length*=Height;

	this->Data = (GLubyte*)malloc(Length);
	if(this->Data==NULL)
		return -1;
	fseek(fp,54,SEEK_SET);
	fread(this->Data,1,Length,fp);
	fclose(fp);

	return 0;
}

void BMPFile::Draw(float x,float y,float z)
{
	glRasterPos3f(x,y,z);
	glDrawPixels(Width,Height,GL_BGR_EXT,GL_UNSIGNED_BYTE,this->Data);
	
	
}

BMPFile::~BMPFile(void)
{
}
