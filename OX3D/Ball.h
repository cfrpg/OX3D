#pragma once
#define BallR 0.06
#define BLength 0.2
#define BOrginalX	0.2
#define BOrginalY	0.05
#define BOrginalZ	-2.3
class Ball
{
	public:
		Ball(void);
		Ball(float _x,float _y,float _z);
		float x;
		float y;
		float z;
		int Color;
		void Draw(int c,float rx,float ry);
		~Ball(void);
};

