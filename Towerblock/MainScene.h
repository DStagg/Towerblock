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

	sf::Font _Font;
	CompositeTex _CompositeTex;

	bool _DrawLog;

	Level _Level;
};

void DebugDrawMask(AABBMask mask, sf::RenderWindow* rw, sf::Color col = sf::Color::White);
void DebugDrawMask(CircleMask mask, sf::RenderWindow* rw, sf::Color col = sf::Color::White);
void DebugDrawAABB(AABB box, sf::RenderWindow* rw, sf::Color col = sf::Color::White);
void DebugDrawCirc(Circle circ, sf::RenderWindow* rw, sf::Color col = sf::Color::White);

//	TODO: 4.1 Player can fire bullets w/ cooldown
//	TODO: 4.2 Bullets collide w/ enemy
//	TODO: 4.3 Bullets harm & kill enemy
//	TODO: 4.4 Multiple enemies on screen
//	TODO: 4.5 Move new framework files to correct director and update #include paths
//	TODO: 5.1 Add alt. fire mode (shotgun)
//	TODO: 5.2 Display gun cooldown on screen
//	TODO: 5.3 Player knocked back on harm
//	TODO: 5.4 Screen flashes on harm
//	TODO: 6.1 Win Screen (kill all enemies)
//	TODO: 6.2 Lose screen (lose all health)
//	TODO: 6.3 Show player facing
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