#include "Player.h"



Player::Player(String text1, String text2)
{
	texture1.loadFromFile(text1);
	texture2.loadFromFile(text2);
	frame = 0;
}


Player::~Player()
{
}

void Player::setPlayer(float time)
{
	frame += 0.003*time / 2;
	if (frame > 2)
		frame = 0;

	if (frame >= 1)
		sprite.setTexture(texture1);
	else
		sprite.setTexture(texture2);
	sprite.setPosition(500, 500);
	sprite.setScale(3, 3);
}

Sprite Player::getPlayer()
{
	return sprite;
}

void Player::drawPlayer(RenderWindow &app)
{
	app.draw(sprite);
}