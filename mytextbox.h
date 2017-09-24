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
		Enabled,
		Disabled
	};
}
class mytextbox : public sf::RectangleShape
{

public:
	//State state2 = myState::Enabled;
	/*
	Creates textbox with given size.
	*/
	mytextbox(Vector2f);
	/*
	Enables or disables textbox.
	*/
	void setState(myState::State state);
	/*
	Gets current state of textbox.
	*/
	myState::State getState();
	mytextbox();
	~mytextbox();

};
