#include "SceneTransition.h"

SceneTransition::SceneTransition(Scene* scene1, Scene* scene2, sf::RenderWindow* rw)
{
	_Scene1 = scene1;
	_Scene2 = scene2;
	_Window = rw;
};

void SceneTransition::Begin()
{

};
void SceneTransition::End()
{

};
void SceneTransition::Pause()
{

};
void SceneTransition::Resume()
{

};


FadeTransition::FadeTransition(Scene* scene1, Scene* scene2, sf::RenderWindow* rw, float time) : SceneTransition(scene1, scene2, rw)
{
	_TransitionTime = time;
};

void FadeTransition::Update(float dt)
{
	_ElapsedTime += dt;

	if (_ElapsedTime >= _TransitionTime)
		GetManager()->PushScene(_Scene2);
};

void FadeTransition::DrawScreen()
{
	if (this->_Window == 0)
	{
		Log("FadeTransition _Window is 0.");
		return;
	}

	if (_ElapsedTime < _TransitionTime / 2.f)
	{
		if (_Scene1 != 0)
			_Scene1->DrawScreen();
		sf::RectangleShape cover;
		cover.setSize(sf::Vector2f((float)_Window->getSize().x, (float)_Window->getSize().y));
		cover.setPosition(0.f, 0.f);
		cover.setFillColor(sf::Color(0, 0, 0, (_ElapsedTime / (_TransitionTime / 2.f)) * 255));
		_Window->draw(cover);
	}
	else
	{
		if (_Scene2 != 0)
			_Scene2->DrawScreen();
		sf::RectangleShape cover;
		cover.setSize(sf::Vector2f((float)_Window->getSize().x, (float)_Window->getSize().y));
		cover.setPosition(0.f, 0.f);
		cover.setFillColor(sf::Color(0, 0, 0, ((_ElapsedTime - (_TransitionTime / 2.f)) / (_TransitionTime / 2.f) ) * 255));
		_Window->draw(cover);
	}	
};