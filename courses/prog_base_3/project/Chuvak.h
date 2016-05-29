#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Chuvak
{
private :
	Texture chuvakTexture;
	Sprite chuvakSprite;
	String file;
	int animation;

public:
	Chuvak(String _file);
	~Chuvak();
public :
	void setChuvak();
	Sprite getChuvak();
	void drawChuvak(RenderWindow &app);
};

