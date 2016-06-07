#include "Background.h"



Background::Background(String _file)
{
	file = _file;
}


Background::~Background()
{
}

void Background::setBackground()
{
	Texture bg;
	bg.loadFromFile(file);
	bg.setRepeated(true);
	background.setTexture(bg);
	background.setTextureRect(IntRect(0, 0, 5000, 411));
	background.setPosition(-2000, 0);
}

void Background::drawBackground(RenderWindow &app)
{
	app.draw(background);
}