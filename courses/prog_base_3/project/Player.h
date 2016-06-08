#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private :
	double frame;
	Texture texture1, texture2;
	Sprite sprite;

public:
	Player(String text1, String text2);
	~Player();
public :
	void setPlayer(float time);
	Sprite getPlayer();
	void drawPlayer(RenderWindow &app);
};

