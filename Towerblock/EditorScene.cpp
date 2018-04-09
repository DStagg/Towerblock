#include "EditorScene.h"

EditorScene::EditorScene(sf::RenderWindow* rw)
{
	_Window = rw;
};
EditorScene::~EditorScene()
{

};

void EditorScene::Begin()
{
	_CameraView = _Window->getDefaultView();

	_ImgMan.SetDirectory("Resources");
	_ImgMan.LoadTextureFromFile("Tilesheet", "Tilesheet.png");

	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");

	_Level.Load("Level.sav");
};
void EditorScene::End()
{

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
		else if (Event.type == sf::Event::MouseButtonPressed)
		{
			if (Event.mouseButton.button == sf::Mouse::Button::Left)
			{

			}
		}
		else if (Event.type == sf::Event::KeyPressed)
			switch (Event.key.code)
			{
			case sf::Keyboard::Escape:
				GetManager()->Quit();
				break;
			case sf::Keyboard::S:
				_Level.Save("Level.sav");
				break;
			case sf::Keyboard::L:
				_Level.Load("Level.sav");
				break;
			default:
				break;
			}
	}
};
void EditorScene::DrawScreen()
{
	_Level.Draw(_Window);
};