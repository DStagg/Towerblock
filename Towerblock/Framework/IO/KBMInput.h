#ifndef KBMInput_H
#define KBMInput_H

#include "SFML\Graphics.hpp"
#include "..\Data\Pair.h"

namespace KBMInput
{
	PairInt GetMousePosWorld(sf::RenderWindow* win);
	PairInt GetMousePosScreen(sf::RenderWindow* win);
}

#endif