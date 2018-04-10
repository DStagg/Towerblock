#ifndef WIN_SCENE_H
#define WIN_SCENE_H

#include "Framework\SFMLScene.h"

class WinScene : public SFMLScene
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

	sf::Font _Font;
};

#endif