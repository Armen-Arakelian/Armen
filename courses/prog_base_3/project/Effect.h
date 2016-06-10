#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Effect
{
public:
	Effect();
	~Effect();

public:
	void addEffect(String file, RenderWindow &app, double x, double y);
};