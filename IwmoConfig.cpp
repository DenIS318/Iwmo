#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include "tinyxml\tinyxml.h"
#include "IwmoMath.h"
#include "IwmoConfig.h"
namespace Iwmo {
	int Width = 800;
	int Height = 608;
	std::string WindowName = "I wanna maker online";
	short framerate = 60;
	std::string res = "resources\\";
	std::string but = "button_";
	bool debug = true;
	unsigned short port = 25565;
	int GRAVITY = 10;
	Math IWMOMATH;
	vector <Keyboard::Key*> Hotkeys = {
		&HotkeyMake,&HotkeyMinimap,&HotkeyTeleport,&HotkeyDeath,&HotkeyRestart,&HotkeyShoot,&HotkeyJump,&HotkeyJumpThru,
		&HotkeyNoGrid,&HotkeyMoveLeft,&HotkeyMoveRight,&HotkeyScrollUp,&HotkeyScrollLeft,&HotkeyScrollDown,&HotkeyScrollRight,
		&HotkeyFastBuild,&HotkeyImGui,&HotkeyFlip,&HotkeyDelete,&HotkeyListener,&HotkeyTeleportMusic
	};
	vector<string> HotkeysName = { "Make mode", "Minimap", "Teleport","Death","Restart","Shoot","Jump","Jump-thru",
		"No grid creating mode(hold)", "Move left","Move right","Scroll up","Scroll left","Scroll down","Scroll right",
		"Fast build mode(hold)","Show/hide maker window","Flip selected block","Delete selected block","Teleport listener to mouse",
		"Teleport playing music to mouse"
	};
}