#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include <SFML\Graphics.hpp>
#include "Framework\Scene.h"

#include "MainScene.h"

class TitleScene : public Scene
{
public:

	TitleScene(sf::RenderWindow* rw);
	~TitleScene();

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