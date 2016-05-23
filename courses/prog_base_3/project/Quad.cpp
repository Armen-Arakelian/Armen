#include "Quad.h"
#include <SFML/Graphics.hpp>

using namespace sf;

Quad::Quad(int _x1, int _y1, int _w1, int _x2, int _y2, int _w2)
{
	x1 = _x1;
	y1 = _y1;
	w1 = _w1;
	x2 = _x2;
	y2 = _y2;
	w2 = _w2;
}


Quad::~Quad()
{
}

void Quad::drawQuad(RenderWindow &w, Color c)
{
	ConvexShape shape(4);
	shape.setFillColor(c);
	shape.setPoint(0, Vector2f(x1 - w1, y1));
	shape.setPoint(1, Vector2f(x2 - w2, y2));
	shape.setPoint(2, Vector2f(x2 + w2, y2));
	shape.setPoint(3, Vector2f(x1 + w1, y1));
	w.draw(shape);
}