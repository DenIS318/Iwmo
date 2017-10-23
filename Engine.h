#pragma once
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
	void RemoveLayer(unsigned short);
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
	vector<vector<Block*>> MapBlocks;
	Math m_math = Iwmo::IWMOMATH;
	bool LoadSound(string name,string buffername);
	void AddSoundBuffer(string name);
	map<string, sf::SoundBuffer>* buflist();
	vector<vector<iwmoEffect*>> effectlayers;
	vector<Sound*> allsounds;
	vector<Music*> allmusic;
private:
	
	map<string, sf::SoundBuffer>* bufferlist = new map<string, sf::SoundBuffer>;
	const int maxlayersize = 1;
	vector<vector<Drawable*>> layerr = vector<vector<Drawable*>>(maxlayersize);
	vector<vector<iwmoEntity*>> layerrentity = vector<vector<iwmoEntity*>>(maxlayersize);
	//vector<tmx::Layer::Tile*> maptiles;
	sf::Clock clock;
	sf::Time time;
	RenderWindow window;
};
