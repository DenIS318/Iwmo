#pragma once
#include <iostream>
#include <SFML\Graphics.hpp>
#include <SFML\Network.hpp>
#include "IwmoMath.h"
#include <stdio.h>
#include "iwmoTypes.h"
#include <boost/filesystem.hpp>
extern class Network;
extern class Player;
//CONFIG
namespace Iwmo {
	//defines layers
#define bg2l 0
#define bgl 1
#define tilesl 2
#define tiles2l 3
#define boundsl 4
#define deathzonel 5
#define objectsl 6
#define textlayerl 7
#define IWMOPHIE 3.1415926535897932384626433832795
	extern int Width;
	extern int Height;
	extern std::string WindowName;
	extern short framerate;
	extern std::string res;
	extern std::string but;
	extern bool debug;
	extern unsigned short port;
	extern int GRAVITY;
	const sf::Vector2f KidSpawn(100, 3600-32);
	auto static HotkeyMake = sf::Keyboard::M;
	auto static HotkeyMinimap = sf::Keyboard::Y;
	auto static HotkeyTeleport = sf::Keyboard::T;
	auto static HotkeyDeath = sf::Keyboard::Q;
	auto static HotkeyRestart = sf::Keyboard::R;
	auto static HotkeyShoot = sf::Keyboard::Z;
	auto static HotkeyJump = sf::Keyboard::LShift;
	auto static HotkeyJumpThru = sf::Keyboard::Down;
	auto static HotkeyNoGrid = sf::Keyboard::LControl;
	auto static HotkeyMoveLeft = sf::Keyboard::Left;
	auto static HotkeyMoveRight = sf::Keyboard::Right;
	auto static HotkeyScrollUp = sf::Keyboard::W;
	auto static HotkeyScrollLeft = sf::Keyboard::A;
	auto static HotkeyScrollDown = sf::Keyboard::S;
	auto static HotkeyScrollRight = sf::Keyboard::D;
	auto static HotkeyFastBuild = sf::Keyboard::X;
	auto static HotkeyImGui = sf::Keyboard::Tab;
	auto static HotkeyFlip = sf::Keyboard::F;
	auto static HotkeyDelete = sf::Keyboard::Delete;
	auto static HotkeyListener = sf::Keyboard::L;
	auto static HotkeyTeleportMusic = sf::Keyboard::N;
	extern string NameStringHelp;
	extern string MyName;
	extern string IpStringHelp;
	extern vector <Keyboard::Key*> Hotkeys;
	extern vector<string> HotkeysName;
	extern Math IWMOMATH;
	extern Player* myplayer;
	extern TcpSocket* mysocket;
	extern Network* mynetwork;
	namespace Textures {
		extern sf::Texture* kidDeathSheet;
		extern sf::Texture* kidSheet;
	}
	static vector<map<string, string>> get_file_list(const std::string& path)
	{
		vector<map<string, string>> filevector = vector<map<string, string>>(0);
		filevector.reserve(0);
		if (!path.empty())
		{
			namespace fs = boost::filesystem;

			fs::path apk_path(path);
			fs::recursive_directory_iterator end;

			for (fs::recursive_directory_iterator i(apk_path); i != end; ++i)
			{
				map<string, string> m_file;
				const fs::path cp = (*i);
				m_file.insert(std::pair<string, string>(cp.string(), cp.filename().string()));
				filevector.push_back(m_file);
			}
		}
		return filevector;
	}
	static const char *getKeyName(const sf::Keyboard::Key key) {
		switch (key) {
		default:
		case sf::Keyboard::Unknown:
			return "Unknown";
		case sf::Keyboard::A:
			return "A";
		case sf::Keyboard::B:
			return "B";
		case sf::Keyboard::C:
			return "C";
		case sf::Keyboard::D:
			return "D";
		case sf::Keyboard::E:
			return "E";
		case sf::Keyboard::F:
			return "F";
		case sf::Keyboard::G:
			return "G";
		case sf::Keyboard::H:
			return "H";
		case sf::Keyboard::I:
			return "I";
		case sf::Keyboard::J:
			return "J";
		case sf::Keyboard::K:
			return "K";
		case sf::Keyboard::L:
			return "L";
		case sf::Keyboard::M:
			return "M";
		case sf::Keyboard::N:
			return "N";
		case sf::Keyboard::O:
			return "O";
		case sf::Keyboard::P:
			return "P";
		case sf::Keyboard::Q:
			return "Q";
		case sf::Keyboard::R:
			return "R";
		case sf::Keyboard::S:
			return "S";
		case sf::Keyboard::T:
			return "T";
		case sf::Keyboard::U:
			return "U";
		case sf::Keyboard::V:
			return "V";
		case sf::Keyboard::W:
			return "W";
		case sf::Keyboard::X:
			return "X";
		case sf::Keyboard::Y:
			return "Y";
		case sf::Keyboard::Z:
			return "Z";
		case sf::Keyboard::Num0:
			return "Num0";
		case sf::Keyboard::Num1:
			return "Num1";
		case sf::Keyboard::Num2:
			return "Num2";
		case sf::Keyboard::Num3:
			return "Num3";
		case sf::Keyboard::Num4:
			return "Num4";
		case sf::Keyboard::Num5:
			return "Num5";
		case sf::Keyboard::Num6:
			return "Num6";
		case sf::Keyboard::Num7:
			return "Num7";
		case sf::Keyboard::Num8:
			return "Num8";
		case sf::Keyboard::Num9:
			return "Num9";
		case sf::Keyboard::Escape:
			return "Escape";
		case sf::Keyboard::LControl:
			return "LControl";
		case sf::Keyboard::LShift:
			return "LShift";
		case sf::Keyboard::LAlt:
			return "LAlt";
		case sf::Keyboard::LSystem:
			return "LSystem";
		case sf::Keyboard::RControl:
			return "RControl";
		case sf::Keyboard::RShift:
			return "RShift";
		case sf::Keyboard::RAlt:
			return "RAlt";
		case sf::Keyboard::RSystem:
			return "RSystem";
		case sf::Keyboard::Menu:
			return "Menu";
		case sf::Keyboard::LBracket:
			return "LBracket";
		case sf::Keyboard::RBracket:
			return "RBracket";
		case sf::Keyboard::SemiColon:
			return "SemiColon";
		case sf::Keyboard::Comma:
			return "Comma";
		case sf::Keyboard::Period:
			return "Period";
		case sf::Keyboard::Quote:
			return "Quote";
		case sf::Keyboard::Slash:
			return "Slash";
		case sf::Keyboard::BackSlash:
			return "BackSlash";
		case sf::Keyboard::Tilde:
			return "Tilde";
		case sf::Keyboard::Equal:
			return "Equal";
		case sf::Keyboard::Dash:
			return "Dash";
		case sf::Keyboard::Space:
			return "Space";
		case sf::Keyboard::Return:
			return "Return";
		case sf::Keyboard::BackSpace:
			return "BackSpace";
		case sf::Keyboard::Tab:
			return "Tab";
		case sf::Keyboard::PageUp:
			return "PageUp";
		case sf::Keyboard::PageDown:
			return "PageDown";
		case sf::Keyboard::End:
			return "End";
		case sf::Keyboard::Home:
			return "Home";
		case sf::Keyboard::Insert:
			return "Insert";
		case sf::Keyboard::Delete:
			return "Delete";
		case sf::Keyboard::Add:
			return "Add";
		case sf::Keyboard::Subtract:
			return "Subtract";
		case sf::Keyboard::Multiply:
			return "Multiply";
		case sf::Keyboard::Divide:
			return "Divide";
		case sf::Keyboard::Left:
			return "Left";
		case sf::Keyboard::Right:
			return "Right";
		case sf::Keyboard::Up:
			return "Up";
		case sf::Keyboard::Down:
			return "Down";
		case sf::Keyboard::Numpad0:
			return "Numpad0";
		case sf::Keyboard::Numpad1:
			return "Numpad1";
		case sf::Keyboard::Numpad2:
			return "Numpad2";
		case sf::Keyboard::Numpad3:
			return "Numpad3";
		case sf::Keyboard::Numpad4:
			return "Numpad4";
		case sf::Keyboard::Numpad5:
			return "Numpad5";
		case sf::Keyboard::Numpad6:
			return "Numpad6";
		case sf::Keyboard::Numpad7:
			return "Numpad7";
		case sf::Keyboard::Numpad8:
			return "Numpad8";
		case sf::Keyboard::Numpad9:
			return "Numpad9";
		case sf::Keyboard::F1:
			return "F1";
		case sf::Keyboard::F2:
			return "F2";
		case sf::Keyboard::F3:
			return "F3";
		case sf::Keyboard::F4:
			return "F4";
		case sf::Keyboard::F5:
			return "F5";
		case sf::Keyboard::F6:
			return "F6";
		case sf::Keyboard::F7:
			return "F7";
		case sf::Keyboard::F8:
			return "F8";
		case sf::Keyboard::F9:
			return "F9";
		case sf::Keyboard::F10:
			return "F10";
		case sf::Keyboard::F11:
			return "F11";
		case sf::Keyboard::F12:
			return "F12";
		case sf::Keyboard::F13:
			return "F13";
		case sf::Keyboard::F14:
			return "F14";
		case sf::Keyboard::F15:
			return "F15";
		case sf::Keyboard::Pause:
			return "Pause";
		}
	}
	template< typename T >
	void coutVector2(Vector2<T> vector)
	{
		cout << vector.x << ", " << vector.y << endl;
	}

	struct IwmoBlock {
		/*
		Block name without dot
		*/
		string blockname;
		/*
		Pointer to block texture
		*/
		Texture* textureptr;
		/*
		Blocktype, see Block::BlockType
		*/
		BlockType blocktype;
		/*
		Block folder, likes resources/blocks/,resources/decorations/...
		*/
		string folder;
	};
}