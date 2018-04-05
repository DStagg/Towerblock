#include "LoseScene.h"

LoseScene::LoseScene(sf::RenderWindow* rw)
{
	_Window = rw;
};

LoseScene::~LoseScene()
{

};

void LoseScene::Begin()
{
	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");
};

void LoseScene::End()
{

};

void LoseScene::Pause()
{

};

void LoseScene::Resume()
{

};

void LoseScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if (Event.type == sf::Event::KeyPressed)
			if (Event.key.code == sf::Keyboard::Key::Escape)
				GetManager()->Quit();
	}
};

void LoseScene::DrawScreen()
{
	sf::Text winMsg;
	winMsg.setString("Loser!");
	winMsg.setFont(_Font);
	winMsg.setFillColor(sf::Color::White);
	winMsg.setPosition((_Window->getSize().x - winMsg.getGlobalBounds().width) / 2.f, (_Window->getSize().y - winMsg.getGlobalBounds().height) / 2.f);
	_Window->draw(winMsg);
};