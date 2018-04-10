#ifndef MainScene_H
#define MainScene_H

#include "Framework/Utility/Utility.h"
#include "Framework/SFMLScene.h"

#include "Framework\Data\Grid.h"
#include "Framework\Data\CompositeTex.h"

#include "Framework\IO\ImageManager.h"

#include "Player.h"
#include "Enemy.h"
#include "Level.h"

#include "Bullet.h"
#include "Pickup.h"

#include "WinScene.h"
#include "LoseScene.h"

#include "SceneTransitions.h"

class MainScene : public SFMLScene
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

	sf::View _CameraView;

	ImageManager _ImgMan;

	sf::Font _Font;
	CompositeTex _CompositeTex;

	bool _DrawLog;

	bool _Paused = false;

	Level _Level;
};

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