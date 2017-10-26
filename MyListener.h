#pragma once
#include <stdio.h>  
#include "CustomEvents.h"
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
using namespace sf;
using namespace Iwmo::Events;

[event_source(native)]
class CSource {
public:
	__event void OnEvent(sf::Event event);
	__event void OnCustomEvent(CustomEvent* e);
};
