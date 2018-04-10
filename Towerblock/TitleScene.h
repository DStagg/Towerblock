#ifndef TITLE_SCENE_H
#define TITLE_SCENE_H

#include "Framework\SFMLScene.h"

#include "MainScene.h"
#include "EditorScene.h"

class TitleScene : public SFMLScene
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

	sf::Font _Font;
};

#endif