#include "Menu.h"

using namespace std;

Menu::Menu()
{
}


Menu::~Menu()
{
}

static void printTopScore(RenderWindow & app);

void Menu::menu(RenderWindow & app, int width, int height) {
	Texture menuTexture1, menuTexture2, menuTexture3, aboutTexture, menuBackground;
	menuTexture1.loadFromFile("images/StartGame.png");
	menuTexture2.loadFromFile("images/LeaderBoard.png");
	menuTexture3.loadFromFile("images/exit.png");
	menuBackground.loadFromFile("images/bgdfv.jpg");
	Sprite menu1(menuTexture1), menu2(menuTexture2), menu3(menuTexture3), menuBg(menuBackground);
	bool isMenu = 1;
	int menuNum = 0;
	menu1.setPosition(400, 300);
	menu2.setPosition(400, 350);
	menu3.setPosition(400, 400);
	menuBg.setPosition(345, 0);

	while (isMenu)
	{
		menu1.setColor(Color::White);
		menu2.setColor(Color::White);
		menu3.setColor(Color::White);
		menuNum = 0;
		app.clear(Color(129, 181, 221));

		if (IntRect(400, 300, 300, 50).contains(Mouse::getPosition(app))) 
		{ 
			menu1.setColor(Color::Blue); 
			menuNum = 1; 
		}
		if (IntRect(400, 350, 300, 50).contains(Mouse::getPosition(app))) 
		{
			menu2.setColor(Color::Blue); 
			menuNum = 2; 
		}
		if (IntRect(400, 400, 300, 50).contains(Mouse::getPosition(app))) 
		{
			menu3.setColor(Color::Blue); 
			menuNum = 3; 
		}

		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if (menuNum == 1)
			{
				const char * filename = "score.txt";
				isMenu = false;
				Game * game = new Game(width, height);
				int score = game->run(app);
				ofstream scoreFile;
				scoreFile.open(filename);
				scoreFile << score;
				scoreFile.close();
				isMenu = true;
			}
			//if (menuNum == 2) { window.draw(about); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == 3) 
			{ 
				app.close(); isMenu = false; 
			}

		}

		app.draw(menuBg);
		app.draw(menu1);
		app.draw(menu2);
		app.draw(menu3);
		printTopScore(app);
		app.display();
	}
}

static void printTopScore(RenderWindow & app)
{
	int score;
	Font font;
	font.loadFromFile("fonts/CyrilicOld.ttf");
	Text text("", font, 40);
	text.setColor(Color::Yellow);
	text.setStyle(Text::Bold);
	const char * filename = "score.txt";
	ifstream scoreFile;
	scoreFile.open(filename);
	scoreFile >> score;
	scoreFile.close();
	std::ostringstream playerScoreString;
	playerScoreString << score;
	text.setString("Top score :" + playerScoreString.str());
	text.setPosition(0, 0);
	app.draw(text);
}