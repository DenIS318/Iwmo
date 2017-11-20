#include "mytextbox.h"
using namespace myState;

myState::State statenow = myState::Enabled;
mytextbox::mytextbox(Vector2f size,string* ptr,Font* fptr,RenderWindow* wind)
{
	window = wind;
	setSize(size);
	setFillColor(Color::White);
	setOutlineColor(Color::Black);
	text.setFillColor(Color::Black);
	stringptr = ptr;
	text.setCharacterSize(12);
	text.setFont(*fptr);
	text.setFillColor(Color::Black);
}
mytextbox::mytextbox()
{
}
void mytextbox::update()
{
	text.setString(*stringptr);
	text.setPosition(getPosition().x + 5, getPosition().y + 2);
	if (AllowAutoEnable)
	{
		auto cords = window->mapPixelToCoords(Vector2i(sf::Mouse::getPosition(*window)));
		if (this->getGlobalBounds().contains(cords))
		{
			setState(Enabled);
		}
		else
		{
			setState(Disabled);
		}
	}
}

mytextbox::~mytextbox()
{
}
void mytextbox::showText(bool b)
{
	if (!b)
	{
		text.setFillColor(sf::Color::Transparent);
	}
	else
	{
		text.setFillColor(sf::Color::Black);
	}
}
bool mytextbox::visible()
{
	return m_visible;
}
void mytextbox::setVisible(bool b)
{
	m_visible = b;
}
void mytextbox::setState(State state)
{
	statenow = state;
	if (statenow == myState::Disabled)
	{
		setOutlineThickness(0);
	}
	else
	{
		if (statenow == myState::Enabled)
		{
			setOutlineThickness(thickness);
		}
	}
}
void mytextbox::GetEvent(Event event)
{
	if (statenow == Enabled)
	{
		switch (event.type)
		{
		case Event::KeyPressed:
		{
			if (event.key.code == sf::Keyboard::BackSpace)
			{
				if (sizeof(text.getString()) > 0 && text.getString() != "")
				{
						stringptr->pop_back();
				}

			}
		}
		break;
		case Event::TextEntered:
				if (filter == ip)
				{
					if (event.text.unicode >= 46 && event.text.unicode <= 57 && event.text.unicode != 47)
					{
						stringptr->push_back((char)event.text.unicode);
					}
				}
				else if (filter == none)
				{
					if (event.text.unicode != 8)
					{
						stringptr->push_back((char)event.text.unicode);
					}
				}
			break;
		}
	}
}
myState::State mytextbox::getState()
{
	return statenow;
}