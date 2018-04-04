#ifndef COLLISION_SCENE_H
#define COLLISION_SCENE_H

#include <SFML\Graphics.hpp>
#include "Framework/Utility/Utility.h"
#include "Framework/Scene.h"

#include "Framework\Data\Collision.h"
#include "Framework\Debug\Console.h"
#include "Framework\Debug\DebugDraw.h"

class CollisionScene : public Scene
{
public:

	CollisionScene(sf::RenderWindow* rw);
	~CollisionScene();

	void Begin();
	void End();
	void Pause();
	void Resume();
	void Update(float dt);
	void DrawScreen();

private:

	sf::RenderWindow* _Window;
	sf::View _CameraView;

	sf::Font _Font;

	bool _DrawLog;

	AABB _Box1, _Box2;
	Circle _Circ1, _Circ2;
	int _Choice = 0;
};

#endif