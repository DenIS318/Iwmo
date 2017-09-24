#pragma once
#include "IwmoConfig.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Listener.h"
#include <tmx\MapLayer.hpp>
#include "Animation.h"
#include "kid.h"
#include "Engine.h"
#include "Player.h"
#include "tmx\Log.hpp"
	const bool constantdebug = true;
	using namespace std;
	using namespace sf;
	using namespace tmx;
	using namespace IV;
		class Game
		{

		public:

		/*static Game* GInstance()
			{
				// согласно стандарту, этот код ленивый и потокобезопасный
				static Game s;
				return &s;
			}*/
			Game();
			/*
			Initalizates games with engine.
			*/
			Game(Engine*, RenderWindow*);
			 ~Game();
			void StartGame(Engine* engine);
			/*
			Sending event source and handler to Game, yeap, perfect explanation
			*/
			void EventHandling(CSource* sourc);


			virtual void m_hookEvent(CSource* pSource);
			virtual void m_unhookEvent(CSource* pSource);
			View* GetCam();
			Game* getGame();
			const Vector2f CAM_SIZE = Vector2f(800, 600);
			const Vector2f CAM_CENTER = Vector2f(300, 2900);
			RenderWindow* window;
			RenderWindow* Getwindow();
			
			sf::View camera;
			CSource* m_ls;
			private:
			TiXmlDocument kidXML;
			TiXmlDocument LevelXML;
			Texture* kidSheet = new Texture;
			};



		[event_receiver(native)]
		class GameHandler : public Game
		{

		public:
		
			bool debuggg;
			Event event;
			Game* gameinstance = Game::getGame();
			RenderWindow* windinst = Game::Getwindow();
			Event GameHandler::GetEvent()
			{
				return event;

			}
			void m_hookEvent(CSource* pSource) {
				cout << "Hooked! Called from GameHandler!" << endl;

				__hook(&CSource::OnEvent, pSource, &GameHandler::OnEvent, this);
			}

			void m_unhookEvent(CSource* pSource) {
				__unhook(&CSource::OnEvent, pSource, &GameHandler::OnEvent);
			}
		private:
			View* camerapointer = gameinstance->GetCam();
			void GameHandler::OnEvent(Event eventt)
			{
				event = eventt;

				if (constantdebug)
				{
				}
				if (event.type == sf::Event::KeyPressed)
				{
					if (event.key.code == sf::Keyboard::X)
					{

						if (constantdebug)
						{
							int x = 0;
							int y = 0;
							cout << "Enter x" << endl;
							cin >> x;
							cout << "Enter y" << endl;
							cin >> y;
							Vector2f vec(x, y);
							cout << "Camera centered to " << x << ", " << y << endl;
							gameinstance->camera.setCenter(vec);
							//cout << "Camera pointer in derived is %p" << camerapointer << endl;
							cout << "And now camera centered to " << camerapointer->getCenter().x << ", " << camerapointer->getCenter().y << endl;
						}
					}
				}
			}


		};
	