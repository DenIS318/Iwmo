#include "Game.h"
#include <future>


GameHandler* eventhandler = new GameHandler;
Game* instanceEH = eventhandler;
void Game::EventHandling(CSource* sourc)
{
	m_ls = sourc;
	instanceEH = dynamic_cast<Game*>(eventhandler);
	instanceEH->m_hookEvent(m_ls);
	__raise sourc->OnEvent(sf::Event());
}
void Game::m_hookEvent(CSource* pSource)
{
	cout << "Not hooked... Called from game" << endl;
}
void Game::m_unhookEvent(CSource* pSource)
{

}
RenderWindow* Game::Getwindow()
{
	return window;
}
View* Game::GetCam()
{
	return &camera;
}
void Game::StartGame(Engine* engine)
{

	for (int i = 0; i < 5; i++)
	{
		engine->AddLayer(i);
	}

	camera.setCenter(CAM_CENTER);
	camera.setSize(CAM_SIZE);
	window->setView(camera);
	engine->SetCam(&camera);
	cout << "Game started!" << endl;

	if (debug)
	{

	}
}

Game::Game()
{

}
Game* Game::getGame()
{
	return (Game*)this;

}
Game::Game(Engine* engine, RenderWindow* wind)
{
	window = wind;
	engine->RemoveAll();
	if (debug)
	{
		//cout << "debug detected!" << endl;
		tmx::setLogLevel(tmx::Logger::Error);
	}
	else
	{
		//cout << "debug disabled..." << endl;
	}

	if (kidSheet->loadFromFile("resources/kid.png"))
	{
		cout << "Kid spritesheet loaded" << endl;
	}
	static kid mykid;
	mykid.createKid("resources/kid.xml", kidSheet, Vector2f(100, 100), engine);
//	mykid.SettingHandler((GameHandler*)eventhandler);
	engine->Addentity(&mykid, 0);
	//
	engine->LoadMap("map.tmx");
	engine->GetMap()->getLayers()[2].visible = false;
	const auto& layers = engine->GetMap()->getLayers();
	for (const auto& layer : layers)
	{

		if (layer.name == "objects")
		{
			for (const auto& object : layer.objects)
			{

				if (object.getName() == "spawn")
				{


					mykid.setPos(object.getPosition());
				}
			}
		}
	}
	//

	engine->gamestarted = true;
	//
	StartGame(engine);
}


Game::~Game()
{
}



void GameHandler::m_hookEvent(CSource* pSource) {
	cout << "Hooked! Called from GameHandler!" << endl;

	__hook(&CSource::OnEvent, pSource, &GameHandler::OnEvent, this);
}

void GameHandler::m_unhookEvent(CSource* pSource) {
	__unhook(&CSource::OnEvent, pSource, &GameHandler::OnEvent);
}
void GameHandler::OnEvent(Event eventt)
{
	event = eventt;

	if (debug)
	{
	}
	if (event.type == sf::Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::X)
		{

			if (debug)
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