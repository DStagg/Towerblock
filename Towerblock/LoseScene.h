#ifndef LOSE_SCENE_H
#define LOSE_SCENE_H

#include "Framework\SFMLScene.h"

class LoseScene : public SFMLScene
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

	sf::Font _Font;
};

#endif