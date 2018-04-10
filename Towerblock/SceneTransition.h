#ifndef SCENE_TRANSITION_H
#define SCENE_TRANSITION_H

#include "Framework\Scene.h"
#include "SFML\Graphics.hpp"

#include "Framework\Debug\Console.h"

class FadeTransition : public SceneTransition
{
public:

	FadeTransition(sf::RenderWindow* rw, float time);

	void Update(float dt);
	void DrawScreen();

private:

	sf::RenderWindow* _Window = 0;
	float _TransitionTime;
	float _ElapsedTime = 0.f;
};

#endif