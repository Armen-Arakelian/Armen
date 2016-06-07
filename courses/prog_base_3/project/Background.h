#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Background
{
private:
	String file;
	Sprite background;
public:
	Background(String _file);
	~Background();
public :
	void setBackground();
	void drawBackground(RenderWindow &app);
};

