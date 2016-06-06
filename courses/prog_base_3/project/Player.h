#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Player
{
private :
	Texture playerTexture;
	Sprite playerSprite;
	String file;
	int animation;

public:
	Player(String _file);
	~Player();
public :
	void setPlayer();
	Sprite getPlayer();
	void drawPlayer(RenderWindow &app);
};

