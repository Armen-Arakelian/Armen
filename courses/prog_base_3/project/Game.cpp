#include "Game.h"

Game::Game(int _width, int _height)
{
	width = _width;
	height = _height;
}


Game::~Game()
{
}

const int roadW = 3000;
const int segL = 250; //segment length
const float camD = 0.84; //camera depth

typedef enum sideStatus
{
	LEFT = -1,
	MIDLE,
	RIGHT
} sideStatus;

typedef enum objectType
{
	OBSTACLE,
	COIN,
	OTHER
} objectType;

static sideStatus getSide(int position);

struct Line
{
	float x, y, z; //3d center of line
	float X, Y, W; //screen coord
	float  spriteX, clip, scale;
	Sprite sprite;
	sideStatus status;
	objectType type;


	Line()
	{
		spriteX = x = y = z = 0;
	}

	void project(int camX, int camY, int camZ, int width, int height)
	{
		scale = camD / (z - camZ);
		X = (1 + scale*(x - camX)) * width / 2;
		Y = (1 - scale*(y - camY)) * height / 2;
		W = scale * roadW  * width / 2;
	}

	void drawSprite(RenderWindow &app, int lineNum, int * isCoinTook, int * isCrashed, int width)
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

		if (destY > -600 && destY < 0 && type == OBSTACLE && status == lineNum)
			*isCrashed = 1;
		if (destY > 480 && destY < 700 && type == COIN && status == lineNum)
		{
			*isCoinTook = 1;
			sprite.setColor(Color(0, 0, 0, 0));
		}

		s.setTextureRect(IntRect(0, 0, w, h - h*clipH / destH));
		s.setScale(destW / w, destH / h);
		s.setPosition(destX, destY);
		app.draw(s);
	}
};


int Game::run(RenderWindow &app)
{
	srand(time(NULL));
	app.setFramerateLimit(60);

	Clock clock;

	Image im;
	Image coinImage;
	Texture coinTexture;
	Texture textures[20];
	Sprite object[20];
	Sprite coinSprite;
	for (int i = 1;i <= 11;i++)
	{
		im.loadFromFile("images/" + std::to_string(i) + ".png");
		im.createMaskFromColor(Color(255, 255, 255));
		textures[i].loadFromImage(im);
		textures[i].setSmooth(true);
		object[i].setTexture(textures[i]);
	}
	coinImage.loadFromFile("images/coin.png");
	coinImage.createMaskFromColor(Color(0, 0, 0));
	coinTexture.loadFromImage(coinImage);
	coinTexture.setSmooth(true);
	coinSprite.setTexture(coinTexture);

	Texture bg;
	bg.loadFromFile("images/bg.jpg");
	bg.setRepeated(true);
	Sprite background;
	background.setTexture(bg);
	background.setTextureRect(IntRect(0, 0, 5000, 411));
	background.setPosition(-2000, 0);

	std::vector<Line> lines;
	int coinPos;
	for (int i = 0;i<16000;i++)
	{
		Line line;
		line.z = i*segL;

		double side[3] = { -1.3, -0.5, 0.2 };
		double coinSide[3] = {-6, 0, 6 };
		int position = rand() % 3;
		line.status = getSide(position);
		int obj = rand() % 4 + 1;
		if (i % 31 == 0) { line.spriteX = 3.0; line.sprite = object[9]; line.type = OTHER; }
		if (i % 13 == 0) { line.spriteX = -3.0; line.sprite = object[8]; line.type = OTHER; }
		if (i % 27 == 0) { line.spriteX = 0.5; line.sprite = object[11]; line.type = OTHER; }
		if (i % 7 == 0) { line.spriteX = rand() % 25 + 3; line.sprite = object[10]; line.type = OTHER; }
		if (i % 6 == 0) { line.spriteX = rand() % 25 - 28; line.sprite = object[6]; line.type = OTHER; }
		if (i % 511 == 0) { line.spriteX = -4; line.sprite = object[5]; line.type = OTHER; }
		int typeFlag = 0;
		if (i>100 && i % 17 == 0)
		{
			line.spriteX = side[position];
			line.sprite = object[obj];
			line.type = OBSTACLE;
			typeFlag = 1;
		}
		if (i % 11 == 0 && !typeFlag)
		{
			coinPos = rand() % 3;
			if (coinPos != position)
			{
				line.status = getSide(coinPos);
				line.spriteX = coinSide[coinPos];
				line.sprite = coinSprite;
				line.type = COIN;
			}
		}
		if ((i % 693) == 0 || (i % 694) == 0)
			line.type = COIN;
		lines.push_back(line);
	}




	Player *player = new Player("images/chuvak.png", "images/chuvak1.png");

	Font font;
	font.loadFromFile("fonts/CyrilicOld.ttf");
	Text text("", font, 40);
	text.setColor(Color::Yellow);
	text.setStyle(Text::Bold);

	int N = lines.size();
	float playerX = 0;
	int pos = 0;
	int H = 1500;
	int lineNum = 0;
	int movingFlag = 0;
	int isCoinTook = 0;
	int isCrashed = 0;
	int score = 0;
	float currentFrame = 0;

	while (app.isOpen())
	{
		Event e;
		while (app.pollEvent(e))
		{
			if (e.type == Event::Closed)
				app.close();
		}

		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 200;

		int speed = 800;

		if (lineNum != 1 && !movingFlag && Keyboard::isKeyPressed(Keyboard::Right))
		{
			playerX += 0.65;
			lineNum++;
			movingFlag = 5;
		}
		if (lineNum != -1 && !movingFlag && Keyboard::isKeyPressed(Keyboard::Left))
		{
			playerX -= 0.65;
			lineNum--;
			movingFlag = 5;
		}
		if (movingFlag)
			movingFlag--;



		pos += speed;
		while (pos >= N*segL) pos -= N*segL;
		while (pos < 0) pos += N*segL;

		app.clear(Color(105, 205, 4));
		app.draw(background);
		int startPos = pos / segL;
		int camH = lines[startPos].y + H;

		int maxy = height;

		///////draw road////////
		for (int n = startPos; n<startPos + 300; n++)
		{
			Line &l = lines[n%N];
			l.project(playerX*roadW, camH, startPos*segL - (n >= N ? N*segL : 0), width, height);

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
			lines[n%N].drawSprite(app, lineNum, &isCoinTook, &isCrashed, width);

		currentFrame += 0.005*time;
		if (currentFrame > 1) currentFrame = 0;

		{
			player->setPlayer((double)time);
			player->drawPlayer(app);
		}
		score++;
		if (isCoinTook)
		{
			Effect * effect = new Effect();
			effect->addEffect("images/Effects_coin.png", app, 525, 540);
			isCoinTook = 0;
			score += 10;
		}

		if (isCrashed)
		{
			Effect * effect = new Effect();
			effect->addEffect("images/crashEffect.jpg", app, 250, 450);
			app.display();
			sleep(milliseconds(5000));
			break;
			//exit(0);
		}
		std::ostringstream playerScoreString;
		playerScoreString << score;
		text.setString("Score :" + playerScoreString.str());
		text.setPosition(0, 650);
		app.draw(text);
		app.display();
	}

	return score;
}

static sideStatus getSide(int position)
{
	switch (position)
	{
	case 0:
		return LEFT;
	case 1:
		return MIDLE;
	case 2:
		return RIGHT;
	default:
		break;
	}
}