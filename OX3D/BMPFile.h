#pragma once
#include <gl\glut.h>
class BMPFile
{
	public:
		BMPFile(void);
		GLint Width;
		GLint Height;		
		GLint Length;
		GLubyte* Data;
		int Load(char *path);
		void Draw(float x,float y,float z);
		~BMPFile(void);
		
};

