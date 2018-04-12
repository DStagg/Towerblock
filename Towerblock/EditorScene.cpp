#include "EditorScene.h"

EditorScene::EditorScene(sf::RenderWindow* rw) : SFMLScene(rw)
{
	
};
EditorScene::~EditorScene()
{

};

void EditorScene::Begin()
{
	_CameraView = _Window->getDefaultView();

	_ImgMan.SetDirectory("Resources");
	_ImgMan.LoadTextureFromFile("Tilesheet", "Tilesheet.png");

	sf::Image img = _ImgMan.GetTexturePntr("Tilesheet")->copyToImage();
	_CompositeBuilder = CompositeBuilder(img, PairInt(32, 32));

	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");

	_Level.Load("Level.sav");

	Console::C()->Init(_Font, 16, 20);

	_MouseInput.Init(_Window);

	RefreshTiles();
};
void EditorScene::End()
{
	Console::C()->DumpLog("EditorLog.txt");
};
void EditorScene::Pause()
{

};
void EditorScene::Resume()
{

};
void EditorScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if (Event.type == sf::Event::MouseMoved)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle))
				_CameraView.move((float)_CameraPanX - Event.mouseMove.x, (float)_CameraPanY - Event.mouseMove.y);

			_CameraPanX = Event.mouseMove.x;
			_CameraPanY = Event.mouseMove.y;
		}
		else if (Event.type == sf::Event::MouseButtonPressed)
		{
			PairInt mpos = _MouseInput.GetWorldPos();
			int mx = mpos._A;
			int my = mpos._B;

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				mx = mx - (mx % 16);
				my = my - (my % 16);
			}

			if (Event.mouseButton.button == sf::Mouse::Button::Left)
			{
				if (_Mode == EditMode::PlayerStartMode)
					_Level.SetPlayerStart(mx, my);
				else if (_Mode == EditMode::TileSpriteMode)
				{
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))		//	Select Tile
					{
						int maxx = (_ImgMan.GetTexturePntr("Tilesheet")->getSize().x / 32) - 1;
						int maxy = (_ImgMan.GetTexturePntr("Tilesheet")->getSize().y / 32) - 1;
						_TileX = Min(maxx, Max(0, (mx - (mx % 32)) / 32));
						_TileY = Min(maxy, Max(0, (my - (my % 32)) / 32));
					}
					else														//	Paint Tile
					{
						int col = _Level.CalcCol((float)mx);
						int row = _Level.CalcRow((float)my);

						_Level.GetGrid().SetCell(col, row, Tile(_TileX, _TileY, _Level.GetGrid().GetCell(col, row)._Solid));

						RefreshTiles();
					}
				}
				else if (_Mode == EditMode::TileSolidMode)
				{
					int col = _Level.CalcCol((float)mx);
					int row = _Level.CalcCol((float)my);

					_Level.GetGrid().SetCell(col, row, Tile(_Level.GetGrid().GetCell(col, row)._SpriteX, _Level.GetGrid().GetCell(col, row)._SpriteY, !_Level.GetGrid().GetCell(col, row)._Solid));
				}
				else if (_Mode == EditMode::AddEnemyMode)
				{
					bool collided = false;
					for (int i = 0; i < _Level.CountEnemies(); i++)
					{
						if (collided) break;
						if (_Level.GetEnemy(i).GetMask().Collide(CircleMask(Circle(mx, my, 16)))._Collided)
						{
							collided = true;
							break;
						}
					}

					if (!collided)
					{
						Enemy newE;
						newE._Position.Set(mx, my);
						newE._Velocity = Vec(0, 0);
						_Level.AddEnemy(newE);
					}
				}
				else if (_Mode == EditMode::EnemyMoveMode)
				{
					for (int i = 0; i < _Level.CountEnemies(); i++)
					{
						if (_Level.GetEnemy(i).GetMask().Collide(CircleMask(Circle(mx, my, 16)))._Collided)
						{
							_EnemyDrag = i;
							break;
						}
					}
				}
				else if (_Mode == EditMode::AddPickupMode)
				{
					bool collided = false;
					for (int i = 0; i < _Level.CountPickups(); i++)
					{
						if (collided) break;
						if (_Level.GetPickup(i).GetMask().Collide(CircleMask(Circle(mx, my, 8)))._Collided)
						{
							collided = true;
							break;
						}
					}

					if (!collided)
					{
						Pickup newP;
						newP._Position.Set(mx, my);
						_Level.AddPickup(newP);
					}
				}
			}
			else if (Event.mouseButton.button == sf::Mouse::Right)
			{
				if (_Mode == EditMode::AddEnemyMode)
				{
					for (int i = 0; i < _Level.CountEnemies(); i++)
					{
						if (_Level.GetEnemy(i).GetMask()._Mask.Contains(mx, my))
						{
							_Level.DelEnemy(i);
							break;
						}
					}
				}
				else if (_Mode == EditMode::AddPickupMode)
				{
					for (int i = 0; i < _Level.CountPickups(); i++)
					{
						if (_Level.GetPickup(i).GetMask()._Mask.Contains(mx, my))
						{
							_Level.DelPickup(i);
							break;
						}
					}
				}
				else if (_Mode == EditMode::EnemyMoveMode)
				{
					for (int i = 0; i < _Level.CountEnemies(); i++)
					{
						if (_Level.GetEnemy(i).GetMask()._Mask.Contains(mx, my))
						{
							_Level.GetEnemyPntr(i)->_Velocity = Vec(0, 0);
							_Level.GetEnemyPntr(i)->_Facing = 0.f;
							break;
						}
					}
				}
			}
		}
		else if (Event.type == sf::Event::MouseButtonReleased)
		{
			PairInt mpos = _MouseInput.GetWorldPos();
			int mx = mpos._A;
			int my = mpos._B;

			if ((_Mode == EditMode::EnemyMoveMode) && (_EnemyDrag != -1) && (Event.mouseButton.button == sf::Mouse::Button::Left))
			{
				Vec dir = (Vec((float)mx, (float)my) - Vec(_Level.GetEnemy(_EnemyDrag)._Position)).UnitVec() * 100.f;
				_Level.GetEnemyPntr(_EnemyDrag)->_Velocity = dir;
				
				_EnemyDrag = -1;

			}
		}
		else if (Event.type == sf::Event::KeyPressed)
			switch (Event.key.code)
			{
			case sf::Keyboard::Escape:
				GetManager()->Quit();
				break;
			case sf::Keyboard::F1:
				_ShowLog = !_ShowLog;
				break;
			case sf::Keyboard::S:
				_Level.Save("Level.sav");
				break;
			case sf::Keyboard::L:
				_Level.Load("Level.sav");
				RefreshTiles();
				break;
			case sf::Keyboard::Num1:
				_Mode = EditMode::PlayerStartMode;
				break;
			case sf::Keyboard::Num2:
				_Mode = EditMode::GridSizeMode;
				break;
			case sf::Keyboard::Num3:
				_Mode = EditMode::TileSpriteMode;
				break;
			case sf::Keyboard::Num4:
				_Mode = EditMode::TileSolidMode;
				break;
			case sf::Keyboard::Num5:
				_Mode = EditMode::AddEnemyMode;
				break;
			case sf::Keyboard::Num6:
				_Mode = EditMode::EnemyMoveMode;
				break;
			case sf::Keyboard::Num7:
				_Mode = EditMode::AddPickupMode;
				break;
			case sf::Keyboard::Return:
				_CameraView = _Window->getDefaultView();
				break;
			case sf::Keyboard::Left:
				if (_Mode == EditMode::GridSizeMode)
				{
					_Level.GetGrid().Resize(Max(3, _Level.GetGrid().GetWidth() - 1), _Level.GetGrid().GetHeight());
					RefreshTiles();
				}
				break;
			case sf::Keyboard::Right:
				if (_Mode == EditMode::GridSizeMode)
				{
					_Level.GetGrid().Resize(Min(100, _Level.GetGrid().GetWidth() + 1), _Level.GetGrid().GetHeight());
					RefreshTiles();
				}
				break;
			case sf::Keyboard::Up:
				if (_Mode == EditMode::GridSizeMode)
				{
					_Level.GetGrid().Resize(_Level.GetGrid().GetWidth(), Max(3, _Level.GetGrid().GetHeight() - 1));
					RefreshTiles();
				}
				break;
			case sf::Keyboard::Down:
				if (_Mode == EditMode::GridSizeMode)
				{
					_Level.GetGrid().Resize(_Level.GetGrid().GetWidth(), Min(100, _Level.GetGrid().GetHeight() + 1));
					RefreshTiles();
				}
				break;
			default:
				break;
			}
	}
};
void EditorScene::DrawScreen()
{
	_Window->setView(_CameraView);

	_Window->draw(_CompositeTex.BuildSprite());

	//	Draw the collision map
	if (_Mode == EditMode::TileSolidMode)
	{
		//	HACK: optimise by only drawing on-screen area
		for (int x = 0; x < _Level.GetGrid().GetWidth(); x++)
			for (int y = 0; y < _Level.GetGrid().GetHeight(); y++)
			{
				if (_Level.GetGrid().GetCell(x, y)._Solid)
				{
					sf::RectangleShape rect;
					rect.setPosition((float)x * 32.f, (float)y * 32.f);
					rect.setSize(sf::Vector2f(32.f, 32.f));
					rect.setFillColor(sf::Color(255, 0, 0, 155));
					rect.setOutlineColor(sf::Color::Blue);
					rect.setOutlineThickness(1.f);
					_Window->draw(rect);
				}
			}
	}

	//	Draw the starting position of the player
	sf::CircleShape playerCirc;
	playerCirc.setFillColor(sf::Color::Transparent);
	playerCirc.setOutlineColor(sf::Color::Blue);
	playerCirc.setOutlineThickness(1.f);
	playerCirc.setRadius(16.f);
	playerCirc.setOrigin(16.f, 16.f);
	playerCirc.setPosition((float)_Level.GetPlayerStart()._A, (float)_Level.GetPlayerStart()._B);
	_Window->draw(playerCirc);
	////////////////////////////////////////////

	//	Draw the enemies
	for (int i = 0; i < _Level.CountEnemies(); i++)
	{
		sf::CircleShape circ;
		circ.setRadius(16.f);
		circ.setOrigin(16.f, 16.f);
		circ.setFillColor(sf::Color::Transparent);
		circ.setOutlineColor(sf::Color::Red);
		circ.setOutlineThickness(1.f);
		circ.setPosition((float)_Level.GetEnemy(i)._Position.GetX(), (float)_Level.GetEnemy(i)._Position.GetY());
		_Window->draw(circ);

		if (_Mode == EditMode::EnemyMoveMode)
		{
			if (_Level.GetEnemy(i)._Velocity == Vec(0, 0))
				continue;

			sf::RectangleShape linedir;
			linedir.setSize(sf::Vector2f(50.f, 1.f));
			linedir.setPosition((float)_Level.GetEnemy(i)._Position.GetX(), (float)_Level.GetEnemy(i)._Position.GetY());
			linedir.setFillColor(sf::Color::Red);
			linedir.setRotation(CalcSFMLAngle(_Level.GetEnemy(i)._Velocity._X, _Level.GetEnemy(i)._Velocity._Y));

			_Window->draw(linedir);
		}
	}
	////////////////////

	//	Draw the pickups
	for (int i = 0; i < _Level.CountPickups(); i++)
	{
		sf::CircleShape circ;
		circ.setRadius(8.f);
		circ.setOrigin(8.f, 8.f);
		circ.setFillColor(sf::Color::Transparent);
		circ.setOutlineColor(sf::Color::Yellow);
		circ.setOutlineThickness(1.f);
		circ.setPosition((float)_Level.GetPickup(i)._Position.GetX(), (float)_Level.GetPickup(i)._Position.GetY());
		_Window->draw(circ);
	}
	////////////////////

	if ((_Mode == EditMode::EnemyMoveMode) && (_EnemyDrag != -1))
	{
		sf::RectangleShape linedir;
		linedir.setSize(sf::Vector2f(CalcDistance(
			_Level.GetEnemy(_EnemyDrag)._Position.GetX(),
			_Level.GetEnemy(_EnemyDrag)._Position.GetY(),
			_MouseInput.GetWorldPos()._A,
			_MouseInput.GetWorldPos()._B)
			, 1.f));
		linedir.setPosition((float)_Level.GetEnemy(_EnemyDrag)._Position.GetX(), (float)_Level.GetEnemy(_EnemyDrag)._Position.GetY());
		linedir.setFillColor(sf::Color::White);
		linedir.setRotation(CalcSFMLAngle(_Level.GetEnemy(_EnemyDrag)._Position.GetX(), _Level.GetEnemy(_EnemyDrag)._Position.GetY(), (int)(sf::Mouse::getPosition(*_Window).x + _CameraView.getCenter().x - (_CameraView.getSize().x / 2.f)), (int)(sf::Mouse::getPosition(*_Window).y + _CameraView.getCenter().y - (_CameraView.getSize().y / 2.f))));

		_Window->draw(linedir);
	}

	//	GUI
	_Window->setView(_Window->getDefaultView());

	sf::RectangleShape backBar;
	backBar.setFillColor(sf::Color(155, 155, 155));
	backBar.setSize(sf::Vector2f((float)_Window->getSize().x, 100.f));
	backBar.setPosition(0.f, _Window->getSize().y - 100.f);
	_Window->draw(backBar);

	sf::Text modeText;
	if (_Mode == EditMode::PlayerStartMode) modeText.setString("Player Start Pos:");
	else if (_Mode == EditMode::GridSizeMode) modeText.setString("Grid Size:");
	else if (_Mode == EditMode::TileSpriteMode) modeText.setString("Tile Sprite:");
	else if (_Mode == EditMode::TileSolidMode) modeText.setString("Tile Solid:");
	else if (_Mode == EditMode::AddEnemyMode) modeText.setString("Add Enemy:");
	else if (_Mode == EditMode::EnemyMoveMode) modeText.setString("Enemy Movement:");
	else if (_Mode == EditMode::AddPickupMode) modeText.setString("Add Pickup:");
	modeText.setFont(_Font);
	modeText.setFillColor(sf::Color::White);
	modeText.setPosition(5.f, _Window->getSize().y - (15.f + modeText.getLocalBounds().height));
	_Window->draw(modeText);

	sf::Text rightText;
	if (_Mode == EditMode::PlayerStartMode) rightText.setString("[" + IntToString(_Level.GetPlayerStart()._A) + "," + IntToString(_Level.GetPlayerStart()._B) + "]");
	else if (_Mode == EditMode::GridSizeMode) rightText.setString("[" + IntToString(_Level.GetGrid().GetWidth()) + "," + IntToString(_Level.GetGrid().GetHeight()) + "]");
	else if (_Mode == EditMode::TileSpriteMode) rightText.setString("Hold Ctrl to show tilesheet.");
	else if (_Mode == EditMode::TileSolidMode) rightText.setString("L-Click to toggle.");
	else if (_Mode == EditMode::AddEnemyMode) rightText.setString(IntToString(_Level.CountEnemies()));
	else if (_Mode == EditMode::EnemyMoveMode) rightText.setString("");
	else if (_Mode == EditMode::AddPickupMode) rightText.setString(IntToString(_Level.CountPickups()));
	rightText.setFont(_Font);
	rightText.setFillColor(sf::Color::White);
	rightText.setPosition(_Window->getSize().x - (5.f + rightText.getLocalBounds().width), _Window->getSize().y - (15.f + modeText.getLocalBounds().height));
	_Window->draw(rightText);

	if (_Mode == EditMode::TileSpriteMode)
	{
		sf::Sprite tileSelection;
		tileSelection.setPosition((_Window->getSize().x - 32.f) / 2.f, _Window->getSize().y - 37.f);
		tileSelection.setTexture(*_ImgMan.GetTexturePntr("Tilesheet"));
		tileSelection.setTextureRect(sf::IntRect(_TileX * 32, _TileY * 32, 32, 32));
		_Window->draw(tileSelection);

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		{
			sf::Sprite tileSheet;
			tileSheet.setTexture(*_ImgMan.GetTexturePntr("Tilesheet"));
			tileSheet.setPosition(0.f, 0.f);
			_Window->draw(tileSheet);

			sf::RectangleShape tileRect;
			tileRect.setPosition((float)_TileX * 32, (float)_TileY * 32);
			tileRect.setSize(sf::Vector2f(32.f, 32.f));
			tileRect.setFillColor(sf::Color::Transparent);
			tileRect.setOutlineColor(sf::Color::Red);
			tileRect.setOutlineThickness(1.f);
			_Window->draw(tileRect);
		}
	}

	if (_ShowLog)
		Console::C()->Draw(_Window);

	_Window->setView(_CameraView);
};

void EditorScene::RefreshTiles()
{
	_CompositeBuilder.BuildCompositeTex(_Level.BuildSpriteCoordGrid(), &_CompositeTex);
};