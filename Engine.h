#pragma once
#pragma warning(disable : 4996)
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>  
#include <iostream>
#include <vector> 
#include <chrono>
#include "Animation.h"
#include "IwmoConfig.h"
#include "iwmoEntity.h"
#include "Block.h"
#include "IwmoMath.h"
#include "iwmoEffect.h"
#include <algorithm>
#include <imgui.h>
#include <imgui-SFML.h>
#include<cstdlib>
#include <stdio.h>
#include "IwmoLayer.h"
#include <functional>
#include <atlstr.h>
#include "Debug.h"
#include <fstream>
#include <SFML/OpenGL.hpp>
#ifdef _MSC_VER 
//not #if defined(_WIN32) || defined(_WIN64) because we have strncasecmp in mingw
#define strncasecmp _strnicmp
#define strcasecmp _stricmp
#endif
#define IMGUI_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))
using namespace sf;
using namespace std;
using namespace Iwmo;
class Engine
{

public:
	//CONSTRUCT
	Engine();
	void SetCam(View*);
	void AddBlock(Block* b, int layernumber);
	void ResetBlock(Block* b);
	void ResetBlocks();
	vector<Sprite*> maptiles;
	///PROTOTYPES
	/*
	Initializates engine and creating main window with given width, height, title, max framerate.
	*/
	void init(int, int, std::string, short);
	/*
	Adding layer.
	*/
	void AddLayer();
	/*
	Removing layer.
	*/
	void RemoveLayer(unsigned int num);
	void RemoveBlockLayer(unsigned int num);
	/*
	Getting layers pointer.
	*/
	vector<vector<Drawable*>>& getLayers();
	/*
	Getting entity layers pointer.
	*/
	vector<vector<iwmoEntity*>>& getEntityLayers();
	/*
	Adding iwmoEntity pointer to layer and render.
	*/
	void Addentity(iwmoEntity*, unsigned short);
	/*
	Removes block by layer permament and clearing RAM.
	*/
	void RemoveBlock(Block*, unsigned short);
	/*
	Removes block permament and clearing RAM.
	*/
	void RemoveBlock(Block*);
	/*
	/*
	Removes iwmoEntity by layer permament and clearing RAM.
	*/
	void Removeentity(iwmoEntity*, unsigned short);
	/*
	Removes iwmoEntity permament and clearing RAM.
	*/
	void Removeentity(iwmoEntity*);
	/*
	Adding sprite pointer to layer and render.
	*/
	void AddSprite(Drawable*, unsigned short);
	/*
	Removes sprite by layer permament and clearing RAM.
	*/
	void RemoveSprite(Drawable*, unsigned short);
	/*
	Removes sprite permament and clearing RAM.
	*/
	void RemoveSprite(Drawable*);
	/*
	Getting main window pointer.
	*/
	RenderWindow* GetWindow();
	/*
	Rendering textures. Recommended after event pooling.
	*/
	void Render();
	/*
	Getting current fps.
	*/
	unsigned int GetFrameRate();
	/*
	Removes all sprites and permament destroyes its.
	*/
	void RemoveAll();
	//DESTRUCT
	~Engine();
	bool gamestarted = false;
	/*
	Returns all entities
	*/
	vector<vector<iwmoEntity*>>& GetEntities();
	void RemoveEffect(iwmoEffect* effect);
	void RemoveEffect(iwmoEffect* effect, unsigned short layernum);
	void AddEffect(iwmoEffect* effect,unsigned short layernum);
	vector<IwmoLayer> MapBlocks;
	Math m_math = Iwmo::IWMOMATH;
	bool LoadSound(string name,string buffername);
	void AddSoundBuffer(string name);
	map<string, sf::SoundBuffer>* buflist();
	vector<vector<iwmoEffect*>>* getEffectLayers();
	vector<Sound*> allsounds;
	vector<Music*> allmusic;
	bool ShowImgui = false;
	bool ShowTilesets = false;
	void UpdateBlockList(vector<IwmoBlock>*);
	bool ClientIsMaker = true;
	Block* blockprototype;
	Text* textprototype;
	sf::Font font;
	int selectedlayer = 0;
	Vector2u WinSize = Vector2u(Width, Height);
	Vector2i GridSize = Vector2i(32, 32);
	bool make = true;
	bool ImGuifocus = false;
	Vector2f imguipos = Vector2f(0, 0);
	Vector2f imguisize = Vector2f(0,0);
	Vector2f lastemplacedblockpos = Vector2f(-666, -666);
	vector<string> blocktypesStr;
	vector<BlockType> blocktypesType;
	vector<Bullet*> bulletlist;
	void AddBullet(Bullet* bullet);
	void AddText(Text* text);
	void RemoveText(Text* text);
	void RemoveBullet(Bullet* bullet);
	BlockSettings blockSettings;
	bool ImguiCollappsed = true;
	Debug debugger;
	Block* GetBlockAtPoint(Vector2f point, int layer);
	void FlipBlock(Block* lf);
	RectangleShape mouseboundsshow;
	bool showbounds = true;
	/*at one layer*/
	vector<Block*> GetBlocksAtRect(RectangleShape rect,int layer);
	/*at all layers(slower)*/
	vector<Block*> GetBlocksAtRect(RectangleShape rect);
	void UpdateMouseRect();
	void BlockListSelectBlock(Block* b);
	vector<string> listboxvectorFilters;
	vector<Text*> GetTextAtRect(RectangleShape rect);
private:
	void FilterVector(string filter);
	vector<string> FilteredElements;
	int FilteredCurrent;
	int listboxFiltersCurrent;
	bool ShowFilters = false;
	char textbuffer[5000];
	ImFont* defaultfont;
	ImFontConfig font_config;
	INT textcharsize = 14;
	Vector2f textscale = Vector2f(1, 1);
	float textcolor[4] = {0,0,0,1};
	void UpdatePrototype();
	vector<string> intlayer;
	int curtype = 0;
	bool Flash = true;
	int listbox_item_current = 0;
	void DrawImguiTilesets();
	vector<string> listboxvector;
	vector<IwmoBlock>* blocklistptr;
	void ImguiMaker();
	map<string, sf::SoundBuffer>* bufferlist = new map<string, sf::SoundBuffer>;
	const int maxlayersize = 1;
	vector<vector<Drawable*>> layerr = vector<vector<Drawable*>>(maxlayersize);
	vector<vector<iwmoEntity*>> layerrentity = vector<vector<iwmoEntity*>>(maxlayersize);
	vector<vector<iwmoEffect*>> effectlayers;
	vector<Text*> textlist;
	sf::Clock clock;
	sf::Time time;
	RenderWindow window;
	Shader shader;
};
