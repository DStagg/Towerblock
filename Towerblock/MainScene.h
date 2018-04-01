#ifndef MainScene_H
#define MainScene_H

#include <SFML\Graphics.hpp>
#include "Framework/Utility/Utility.h"
#include "Framework/Scene.h"

#include "Framework\Data\Grid.h"
#include "CompositeTex.h"

#include "Player.h"
#include "Enemy.h"
#include "Level.h"

class MainScene : public Scene
{
public:

	MainScene(sf::RenderWindow* rw);
	~MainScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	sf::RenderWindow* _Window;
	sf::View _CameraView;

	CompositeTex _CompositeTex;

	Player _Player;
	Enemy _Enemy;
	Level _Level;
};

void DebugDrawAABB(AABB box, sf::RenderWindow* rw);

#endif