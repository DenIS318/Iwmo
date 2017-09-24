#pragma once
#include <SFML/Graphics.hpp>
#include <thread>  
#include <iostream>
#include <vector> 
#include <chrono>
#include <tmx\MapLoader.hpp>
#include "Animation.h"
#include "iwmoEntity.h"
#include "IwmoConfig.h"
	using namespace sf;
	using namespace std;
	using namespace IV;
		//using namespace IwmoEngine;
		class Engine
		{

		public:
			//CONSTRUCT
			Engine();
			void SetCam(View*);

			///PROTOTYPES
			/*
			Initializates engine and creating main window with given width, height, title, max framerate.
			*/
			void init(int, int, std::string, short);
			/*
			Adding layer.
			*/
			void AddLayer(unsigned short);
			/*
			Removing layer.
			*/
			void RemoveLayer(unsigned short);
			/*
			Getting layer pointer.
			*/
			vector<vector<Drawable*>>& getLayers();
			/*
			Adding iwmoEntity pointer to layer and render.
			*/
			void Addentity(iwmoEntity*, unsigned short);
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
			tmx::MapLoader* GetMap();
			void LoadMap(string);

		private:

			const int maxlayersize = 1;
			vector<vector<Drawable*>> layerr = vector<vector<Drawable*>>(maxlayersize);
			vector<vector<iwmoEntity*>> layerrentity = vector<vector<iwmoEntity*>>(maxlayersize);
		
			sf::Clock clock;
			sf::Time time;
			RenderWindow window;
		};
	