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

#include "Rotation.h"

#include "Console.h"

#include "Bullet.h"

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

	sf::Font _Font;

	bool _DrawLog;

	Bullet _B1, _B2, _B3, _B4;
};

void DebugDrawAABB(AABB box, sf::RenderWindow* rw);

#endif