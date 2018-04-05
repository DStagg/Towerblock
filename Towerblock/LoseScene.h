#ifndef LOSE_SCENE_H
#define LOSE_SCENE_H

#include <SFML\Graphics.hpp>
#include "Framework\Scene.h"

class LoseScene : public Scene
{
public:

	LoseScene(sf::RenderWindow* rw);
	~LoseScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	sf::RenderWindow* _Window;
	sf::Font _Font;
};

#endif