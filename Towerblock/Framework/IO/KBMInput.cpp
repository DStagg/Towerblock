#include "KBMInput.h"

PairInt KBMInput::GetMousePosWorld(sf::RenderWindow* win)
{
	return PairInt((int)(sf::Mouse::getPosition(*win).x + win->getView().getCenter().x - (win->getView().getSize().x / 2.f)),
		           (int)(sf::Mouse::getPosition(*win).y + win->getView().getCenter().y - (win->getView().getSize().y / 2.f)));
};

PairInt KBMInput::GetMousePosScreen(sf::RenderWindow* win)
{
	return PairInt(sf::Mouse::getPosition(*win).x, sf::Mouse::getPosition(*win).y);
};