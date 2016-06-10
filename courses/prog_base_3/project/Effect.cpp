#include "Effect.h"
#include <SFML/Graphics.hpp>



Effect::Effect()
{
}


Effect::~Effect()
{
}

void Effect::addEffect(String file, RenderWindow &app, double x, double y)
{
	Image EffectImage;
	EffectImage.loadFromFile(file);
	EffectImage.createMaskFromColor(Color(0, 0, 0));
	Texture EffectTexture;
	EffectTexture.loadFromImage(EffectImage);
	Sprite EffectSprite;
	EffectSprite.setTexture(EffectTexture);
	EffectSprite.setPosition(x, y);
	app.draw(EffectSprite);
}