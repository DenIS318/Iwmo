#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <windows.h>
using namespace std;
using namespace sf;


namespace myState
{
	enum State
	{
		Disabled,
		Enabled
	};
}
class mytextbox : public sf::RectangleShape
{

public:
	//State state2 = myState::Enabled;
	/*
	Creates textbox with given size, string pointer, font pointer, window poniter.
	*/
	mytextbox(sf::Vector2f,string*,Font*,RenderWindow*);
	//deprecated, not creating box
	mytextbox();
	/*
	Enables or disables textbox.
	*/
	void setState(myState::State state);
	/*
	Gets current state of textbox.
	*/
	myState::State getState();
	~mytextbox();
	Text text;
	void update();
	void showText(bool b);
	bool AllowAutoEnable = true;
	bool visible();
	int thickness = 3;
	void setVisible(bool b);
	void GetEvent(Event event);
	enum textboxFilters
	{
		none,
		ip
	};
	textboxFilters filter = none;
private:
	bool m_visible = true;
	Font* font;
	RenderWindow* window;
	string* stringptr = NULL;
	myState::State statenow = myState::Disabled;
};
