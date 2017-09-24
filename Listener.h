#pragma once
#include <stdio.h>  
using namespace sf;

 
	[event_source(native)]
	class CSource {
	public:
		__event void OnEvent(sf::Event event);
	};

