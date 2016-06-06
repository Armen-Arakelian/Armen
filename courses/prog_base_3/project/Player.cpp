#include "Player.h"



Player::Player(String _file)
{
	file = _file;
	animation = 5;
}


Player::~Player()
{
}

void Player::setPlayer()
{
	playerTexture.loadFromFile(file);
		if (animation > 4)
		{
			playerSprite.setTexture(playerTexture);
			playerSprite.setTextureRect(IntRect(35, 164, 35, 40));
			playerSprite.setPosition(500, 600);
			animation--;
		}
		if (animation < 0)
		{
			playerSprite.setTexture(playerTexture);
			playerSprite.setTextureRect(IntRect(100, 160, 35, 165));
			playerSprite.setPosition(500, 600);
			animation++;
		}
		playerSprite.setScale(3, 3);
}

Sprite Player::getPlayer()
{
	return playerSprite;
}

void Player::drawPlayer(RenderWindow &app)
{
	app.draw(playerSprite);
}