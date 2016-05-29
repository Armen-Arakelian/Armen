#include "Chuvak.h"



Chuvak::Chuvak(String _file)
{
	file = _file;
	animation = 5;
}


Chuvak::~Chuvak()
{
}

void Chuvak::setChuvak()
{
	chuvakTexture.loadFromFile(file);
		if (animation > 4)
		{
			chuvakSprite.setTexture(chuvakTexture);
			chuvakSprite.setTextureRect(IntRect(35, 164, 35, 40));
			chuvakSprite.setPosition(500, 600);
			animation--;
		}
		if (animation < 0)
		{
			chuvakSprite.setTexture(chuvakTexture);
			chuvakSprite.setTextureRect(IntRect(100, 160, 35, 165));
			chuvakSprite.setPosition(500, 600);
			animation++;
		}
}

Sprite Chuvak::getChuvak()
{
	return chuvakSprite;
}

void Chuvak::drawChuvak(RenderWindow &app)
{
	app.draw(chuvakSprite);
}