#include "Game.h"
#include "Menu.h"

const int width = 1024;
const int height = 768;

int main()
{
	RenderWindow app(VideoMode(width, height), "Run game!");
	Menu * menu = new Menu();
	menu->menu(app, width, height);
}
