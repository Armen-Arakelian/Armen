#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class LeaderBord
{
public:
	LeaderBord();
	~LeaderBord();
public :
	Text getName(RenderWindow & window);
};

