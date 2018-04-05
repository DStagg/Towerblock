#ifndef WIN_SCENE_H
#define WIN_SCENE_H

#include <SFML\Graphics.hpp>
#include "Framework\Scene.h"

class WinScene : public Scene
{
public:

	WinScene(sf::RenderWindow* rw);
	~WinScene();

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