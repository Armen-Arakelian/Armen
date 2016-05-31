#include <SFML/Graphics.hpp>
#include "Quad.h"
#include "Segment.h"
#include "Chuvak.h"

using namespace sf;

const int width = 1024;
const int height = 768;
const int roadW = 3000;
const int segL = 250; //segment length
const float camD = 0.84; //camera depth

typedef enum sideStatus
{
	LEFT = -1, 
	MIDLE, 
	RIGHT
} sideStatus;

struct Line
{
	float x, y, z; //3d center of line
	float X, Y, W; //screen coord
	float  spriteX, clip, scale;
	Sprite sprite;
	sideStatus status;


	Line()
	{
		spriteX  = x = y = z = 0;
	}

	void project(int camX, int camY, int camZ)
	{
		scale = camD / (z - camZ);
		X = (1 + scale*(x - camX)) * width / 2;
		Y = (1 - scale*(y - camY)) * height / 2;
		W = scale * roadW  * width / 2;
	}

	void drawSprite(RenderWindow &app, int lineNum)
	{
		Sprite s = sprite;
		int w = s.getTextureRect().width;
		int h = s.getTextureRect().height;

		float destX = X + scale * spriteX * width / 2;
		float destY = Y + 4;
		float destW = w * W / 266;
		float destH = h * W / 266;

		destX += destW * spriteX; //offsetX
		destY += destH * (-1);    //offsetY

		float clipH = destY + destH - clip;
		if (clipH < 0) clipH = 0;

		if (clipH >= destH) return;
		/*if (scale > 0.001 && scale < 0.002 && status == lineNum)
		{
			printf("%f", scale);
			exit(1);
		}*/
		s.setTextureRect(IntRect(0, 0, w, h - h*clipH / destH));
		s.setScale(destW / w, destH / h);
		s.setPosition(destX, destY);
		app.draw(s);
	}
};


int main()
{
	srand(time(NULL));
	RenderWindow app(VideoMode(width, height), "Run game!");
	app.setFramerateLimit(60);


	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		app.display();
	}

	return 0;
}
