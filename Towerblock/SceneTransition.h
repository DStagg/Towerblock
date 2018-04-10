#ifndef SCENE_TRANSITION_H
#define SCENE_TRANSITION_H

#include "Framework\Scene.h"
#include "SFML\Graphics.hpp"

#include "Framework\Debug\Console.h"

class SceneTransition : public Scene
{
public:

	SceneTransition(Scene* scene1, Scene* scene2, sf::RenderWindow* rw);

	void Begin();
	void End();
	void Pause();
	void Resume();
	virtual void Update(float dt) = 0;
	virtual void DrawScreen() = 0;

protected:

	Scene* _Scene1 = 0;
	Scene* _Scene2 = 0;
	sf::RenderWindow* _Window = 0;
};

class FadeTransition : public SceneTransition
{
public:

	FadeTransition(Scene* scene1, Scene* scene2, sf::RenderWindow* rw, float time);

	void Update(float dt);
	void DrawScreen();

private:

	float _TransitionTime;
	float _ElapsedTime = 0.f;
};

#endif