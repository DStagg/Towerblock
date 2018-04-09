#include "TitleScene.h"

TitleScene::TitleScene(sf::RenderWindow* rw)
{
	_Window = rw;
};

TitleScene::~TitleScene()
{

};

void TitleScene::Begin()
{
	_Font.loadFromFile("Resources\\Roboto-Regular.ttf");
};

void TitleScene::End()
{

};

void TitleScene::Pause()
{

};

void TitleScene::Resume()
{

};

void TitleScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			GetManager()->Quit();
		else if (Event.type == sf::Event::KeyPressed)
		{
			if (Event.key.code == sf::Keyboard::Key::Escape)
				GetManager()->Quit();
			else if (Event.key.code == sf::Keyboard::Key::Return)
				GetManager()->PushScene(new MainScene(_Window));
			else if (Event.key.code == sf::Keyboard::E)
				GetManager()->PushScene(new EditorScene(_Window));
		}
	}
};

void TitleScene::DrawScreen()
{
	sf::Text winMsg;
	winMsg.setString("Title Screen");
	winMsg.setFont(_Font);
	winMsg.setFillColor(sf::Color::White);
	winMsg.setPosition((_Window->getSize().x - winMsg.getGlobalBounds().width) / 2.f, (_Window->getSize().y - winMsg.getGlobalBounds().height) / 2.f);
	_Window->draw(winMsg);

	winMsg.setString("Press Enter to begin, or Esc to quit.");
	winMsg.setPosition((_Window->getSize().x - winMsg.getGlobalBounds().width) / 2.f, ((_Window->getSize().y - winMsg.getGlobalBounds().height) / 2.f) + 100.f);
	_Window->draw(winMsg);
};