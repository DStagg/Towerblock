#include "MainScene.h"

MainScene::MainScene(sf::RenderWindow* rw)
{
	_Window = rw;
};
MainScene::~MainScene()
{

};

void MainScene::Begin()
{
	sf::Image img;
	img.loadFromFile("Tilesheet.png");
	std::map<int, PairInt> dic;
	dic[0] = PairInt(0, 0);
	dic[1] = PairInt(1, 0);
	dic[2] = PairInt(1, 0);
	dic[3] = PairInt(1, 1);
	CompositeBuilder builder(img,PairInt(32,32),dic);
	Grid grid;
	grid.Resize(20, 10);
	grid.SetCell(5, 6, 2);
	builder.BuildCompositeTex(grid, &_CompositeTex);
};
void MainScene::End()
{
	
};
void MainScene::Pause()
{

};
void MainScene::Resume()
{

};
void MainScene::Update(float dt)
{
	sf::Event Event;
	while (_Window->pollEvent(Event))
	{
		if (Event.type == sf::Event::Closed)
			SetRunning(false);
		else if (Event.type == sf::Event::KeyPressed && Event.key.code == sf::Keyboard::Escape)
			SetRunning(false);
		
	}

};
void MainScene::DrawScreen()
{
	sf::Sprite temp = _CompositeTex.BuildSprite();
	_Window->draw(temp);
};