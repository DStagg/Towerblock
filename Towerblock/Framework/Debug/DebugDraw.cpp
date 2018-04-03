#include "DebugDraw.h"

void DebugDrawMask(AABBMask mask, sf::RenderWindow* rw, sf::Color col)
{
	return DebugDrawAABB(mask._Mask, rw, col);
};

void DebugDrawMask(CircleMask mask, sf::RenderWindow* rw, sf::Color col)
{
	return DebugDrawCirc(mask._Mask, rw, col);
};

void DebugDrawAABB(AABB box, sf::RenderWindow* rw, sf::Color col)
{
	sf::RectangleShape rect;
	rect.setSize(sf::Vector2f((float)box._Width, (float)box._Height));
	rect.setOutlineThickness(1.f);
	rect.setOutlineColor(col);
	rect.setFillColor(sf::Color::Transparent);
	rect.setPosition((float)box._X, (float)box._Y);
	rw->draw(rect);

};

void DebugDrawCirc(Circle circ, sf::RenderWindow* rw, sf::Color col)
{
	sf::CircleShape circle;
	circle.setRadius((float)circ._Radius);
	circle.setOutlineThickness(1.f);
	circle.setOutlineColor(col);
	circle.setFillColor(sf::Color::Transparent);
	circle.setOrigin((float)circ._Radius, (float)circ._Radius);
	circle.setPosition((float)circ._X, (float)circ._Y);
	rw->draw(circle);
};