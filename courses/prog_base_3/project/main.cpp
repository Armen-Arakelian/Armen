#include <SFML/Graphics.hpp>
#include "Quad.h"
#include "Segment.h"
#include "Player.h"

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
		if (destY > -700 && destY < -200 && status == lineNum)
		{
			printf("%f\n", destY);
			exit(1);
		}
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

	//Clock clock;

	Image im;
	Texture textures[50];
	Sprite object[50];
	for (int i = 1;i <= 7;i++)
	{
		im.loadFromFile("images/" + std::to_string(i) + ".png");
		im.createMaskFromColor(Color(255,255,255));
		textures[i].loadFromImage(im);
		textures[i].setSmooth(true);
		object[i].setTexture(textures[i]);
	}

	Texture Skybg;
	Texture hillsBg;
	Skybg.loadFromFile("images/hills.png");
	Skybg.setRepeated(true);
	Sprite sBackground(Skybg);
	hillsBg.loadFromFile("images/bg.png");
	hillsBg.setRepeated(true);
	Sprite hBackground(hillsBg);
	sBackground.setTextureRect(IntRect(0, 0, 5000, 411));
	sBackground.setPosition(-2000, 100);
	hBackground.setTextureRect(IntRect(0, 0, 5000, 411));
	hBackground.setPosition(-2000, 0);

	std::vector<Line> lines;

	for (int i = 0;i<1600;i++)
	{
		Line line;
		line.z = i*segL;

		double side[4] = {-1.6, -0.5, 0.5 };
		int r = rand() % 3;
		switch (r)
		{
		case 0:
			line.status = LEFT;
			break;
		case 1:
			line.status = MIDLE;
			break;
		case 2:
			line.status = RIGHT;
			break;
		default:
			break;
		}
		int obj = rand() % 6;
		//if (i < 10 && i % 20 == 0) { line.spriteX = -2.5; line.sprite = object[5]; }
		//if (i % 17 == 0) { line.spriteX = 2.0; line.sprite = object[6]; }
		//if (i>800 && i % 20 == 0) { line.spriteX = -0.7; line.sprite = object[4]; }
		if (i>100 && i % 20 == 0) { line.spriteX = side[r]; line.sprite = object[3]; }

		//if (i>750) line.y = sin(i / 30.0) * 1500;

		lines.push_back(line);
	}
	
	


	Player *player = new Player("images/chuvak1.png");
	player->setPlayer();

	int N = lines.size();
	float playerX = 0;
	int pos = 0;
	int lineNum = 0;
	int H = 1500;
	int up = 0;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		/*float time = clock.getElapsedTime().asMicroseconds(); //���� ��������� ����� � �������������
		clock.restart(); //������������� �����
		time = time / 800;*/
		int speed = 800;

		if (lineNum != 1 && Keyboard::isKeyPressed(Keyboard::Right))
		{
			playerX += 0.65;
			lineNum++;
		}
		if (lineNum != -1 && Keyboard::isKeyPressed(Keyboard::Left))
		{
			playerX -= 0.65;
			lineNum--;
		}

		if (up == 1)
		{
			up = 0;
			for (int i = 1;i < 100;i++)
				H -= 10;
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) && up!=1)
		{
			for (int i = 1;i < 100;i++)
				H += 10;
			
			up = 1;
			//lineNum--;
		}

		pos += speed;
		while (pos >= N*segL) pos -= N*segL;
		while (pos < 0) pos += N*segL;

		app.clear(Color(105, 205, 4));
		//app.draw(sBackground);
		app.draw(hBackground);
		int startPos = pos / segL;
		int camH = lines[startPos].y + H;

		int maxy = height;

		///////draw road////////
		for (int n = startPos; n<startPos + 300; n++)
		{
			Line &l = lines[n%N];
			l.project(playerX*roadW, camH, startPos*segL - (n >= N ? N*segL : 0));

			l.clip = maxy;
			if (l.Y >= maxy) continue;
			maxy = l.Y;

			Color grass = (n / 3) % 2 ? Color(16, 200, 16) : Color(0, 154, 0);
			Color rumble = (n / 3) % 2 ? Color(255, 255, 255) : Color(0, 0, 0);
			Color road = (n / 3) % 2 ? Color(107, 107, 107) : Color(105, 105, 105);

			Line p = lines[(n - 1) % N]; //previous line
			Quad * grassQ = new Quad(0, p.Y, width, 0, l.Y, width);
			Quad * rumbleQ = new Quad(p.X, p.Y, p.W*1.2, l.X, l.Y, l.W*1.2);
			Quad * roadQ = new Quad(p.X, p.Y, p.W, l.X, l.Y, l.W);
			Segment * seg = new Segment(grassQ, rumbleQ, roadQ);
			seg->drawSegment(app, grass, rumble, road);
		}

		////////draw objects////////
		for (int n = startPos + 300; n > startPos; n--)
			lines[n%N].drawSprite(app, lineNum);
			
		player->drawPlayer(app);
		//
		app.display();
	}

	return 0;
}
