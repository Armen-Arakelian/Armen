#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Quad
{
private :
	int x1;
	int y1;
	int w1;
	int x2;
	int y2;
	int w2;
public:
	Quad(int _x1, int _y1, int _w1, int _x2, int _y2, int _w2);
	~Quad();

public :
	void drawQuad(RenderWindow &w, Color c);
};

