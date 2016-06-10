#pragma once
#include <SFML/Graphics.hpp>
#include "Game.h"
#include <fstream>

using namespace sf;

class Menu
{
public:
	Menu();
	~Menu();
public :
	void menu(RenderWindow & app, int width, int height);
};

