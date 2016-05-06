#pragma once

typedef enum { LEFT, RIGHT, MIDDLE } line;

class Obstacle
{
public:
	Obstacle(line _l);
	~Obstacle();
private :
	double z;
	line l;
public:
	void spawnObstacle();
};

