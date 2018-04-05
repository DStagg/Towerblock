#ifndef MainScene_H
#define MainScene_H

#include <SFML\Graphics.hpp>
#include "Framework/Utility/Utility.h"
#include "Framework/Scene.h"

#include "Framework\Data\Grid.h"
#include "Framework\Data\CompositeTex.h"

#include "Framework\IO\ImageManager.h"

#include "Player.h"
#include "Enemy.h"
#include "Level.h"

#include "Bullet.h"

#include "WinScene.h"
#include "LoseScene.h"

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

	ImageManager _ImgMan;

	sf::Font _Font;
	CompositeTex _CompositeTex;

	bool _DrawLog;

	Level _Level;
};

//	TODO: 6.4 Show enemy facing
//	TODO: 7.1 Title screen
//	TODO: 7.2 Track ammo per fire mode
//	TODO: 7.3 Ammo pickups appear on screen
//	TODO: 7.4 Ammo can be collected
//	TODO: 8.1 SFX for each fire mode
//	TODO: 8.2 SFX for player harm & death
//	TODO: 8.3 SFX for enemy harm & death
//	TODO: 8.4 SFX for pickups
//	TODO: 9.1 Enemy sprite
//	TODO: 9.2 Player sprite
//	TODO: 9.3 Terrain sprite
//	TODO: 9.4 Pickup sprite
//	TODO: 10  JUICE IT UP

#endif