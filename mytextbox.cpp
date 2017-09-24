#include "mytextbox.h"
using namespace myState;

myState::State statenow = myState::Enabled;
mytextbox::mytextbox(Vector2f size)
{
	setSize(size);
	setFillColor(Color::White);
}
mytextbox::mytextbox()
{
	setFillColor(Color::White);
}


mytextbox::~mytextbox()
{
}
void mytextbox::setState(State state)
{
	statenow = state;
	if (statenow == myState::Disabled)
	{
		setFillColor(Color::Transparent);
	}
	else
	{
		if (statenow == myState::Enabled)
		{
			setFillColor(Color::White);
		}
	}
}
myState::State mytextbox::getState()
{
	return statenow;
}