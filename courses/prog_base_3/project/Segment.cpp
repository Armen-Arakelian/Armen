#include "Segment.h"
#include "Quad.h"


Segment::Segment(Quad *_grass, Quad *_rumble, Quad *_road)
{
	grassQ = _grass;
	rumbleQ = _rumble;
	roadQ = _road;
}


Segment::~Segment()
{
	free(grassQ);
	free(rumbleQ);
	free(roadQ);
}

void Segment::drawSegment(RenderWindow &app, Color grass, Color rumble, Color road)
{
	grassQ->drawQuad(app, grass);
	rumbleQ->drawQuad(app, rumble);
	roadQ->drawQuad(app, road);
}
