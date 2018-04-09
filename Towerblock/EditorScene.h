#ifndef EDITOR_SCENE_H
#define EDITOR_SCENE_H

#include <SFML\Graphics.hpp>
#include "Framework/Scene.h"

#include "Framework\Data\Grid.h"
#include "Framework\Data\CompositeTex.h"

#include "Framework\IO\ImageManager.h"

#include "Level.h"

class EditorScene : public Scene
{
public:

	enum EditMode {
		PlayerStartMode = 0,
		GridSizeMode,
		TileSpriteMode,
		TileSolidMode,
		AddEnemyMode,
		EnemyMoveMode,
		AddPickupMode
	};

	EditorScene(sf::RenderWindow* rw);
	~EditorScene();

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

	int _Mode = 0;

	Level _Level;
};

/*	Modes
Edit Player Start				Just click on the map, possibly with a snap-to-grid filter
Edit Grid Size					Use the arrow keys (Up = height--, Down = height++, Left = width--, Right = width++)
Edit Tile Sprite Coordinates	Select a tile sprite (hold shift for overlay, click to select?) and then click to paint
Edit Tile Solid					Have an overlay show which tiles are solid, click to toggle
Add/Delete Enemies				Just click - left adds, right deletes, possibly with a snap-to-grid filter.
Edit Enemy Starting Velocity	???
Add/Delete Pickups				Just click - left adds, right deletes, possibly with a snap-to-grid filter.
*/
/*	Things we need to be able to edit:
Grid Width - inc or dec, by key?
Grid Height - inc or dec, by key?
Whether any given tile is solid or not - toggle by mouseclick?
The SpriteX of any given tile
The SpriteY of any given tile
The starting point of the player
Add enemies
Delete enemies
The starting velocity of any given enemy
Move enemies - or just delete and re-add?
Add pickups
Delete pickups
Move pickups - or just delete and re-add?
*/
#endif