#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>
#include "Quad.h"
#include "Segment.h"
#include "Player.h"
#include "Effect.h"

using namespace sf;

class Game
{
private:
	int width;
	int height;
public:
	Game(int _width, int _height);
	~Game();
public :
	int run(RenderWindow &app);
};

