#pragma once

#include "Quad.h"

class Segment
{
private:
	Quad *grassQ;
	Quad *rumbleQ;
	Quad *roadQ;

public:
	Segment(Quad * grass, Quad * roumble, Quad * road);
	~Segment();

public:
	void drawSegment(RenderWindow &app, Color c, Color rumble, Color road);
};

