#pragma once
#include <stdio.h>  
#include <SFML\System.hpp>
#include <SFML\Graphics.hpp>
using namespace sf;


[event_source(native)]
class CSource {
public:
	__event void OnEvent(sf::Event event);
};
