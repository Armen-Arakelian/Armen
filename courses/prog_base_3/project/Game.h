#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include "Quad.h"
#include "Segment.h"
#include "Player.h"
#include "Effect.h"

using namespace sf;

class Game
{
public:
	Game();
	~Game();
public :
	int run();
};

