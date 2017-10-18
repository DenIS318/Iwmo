#include "Game.h"
#include <future>
const string m_res = "resources/blocks/";

GameHandler* eventhandler;
Game* instanceEH ;

map<string,Texture*>* Game::GetBlockList()
{
	return &IwmoBlocks;
}
void Game::AddIwmoBlock(string name)
{
	Texture* texture = TextureManager::loadTexture(name, m_res+name);
	IwmoBlocks.insert(std::pair<string, Texture*>(name, texture));
}

Block Game::CreateBlockByName(string name)
{
	for (auto it = IwmoBlocks.begin(); it != IwmoBlocks.end(); ++it)
	{
		if (it->first == name)
		{
			return Block(it->first);
		}
	}
	cout << "Block '" << name << "'" << " not found!" << endl;
	return Block(new Texture(), 0, 0);
}
Texture* Game::GetBlockTextureByName(string name)
{
	for (auto it = IwmoBlocks.begin(); it != IwmoBlocks.end(); ++it)
	{
		if (it->first == name)
		{
		return	TextureManager::getTexture(name);
		}
		//cout << it->first << endl;
	}
	cout << "Block texture '" << name << "'" << " not found!" << endl;
	return new Texture;
}
vector<map<string, string>> get_file_list(const std::string& path)
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
			/*stringstream ss;
			ss << cp.filename()/* << "." << cp.extension();*/
			m_file.insert(std::pair<string, string>(cp.string(),cp.filename().string()));
			filevector.push_back(m_file);
		}
	}
	return filevector;
}
void Game::InitIwmoBlocks()
{
	path p("resources/blocks/");  // avoid repeated path construction below
	std::vector<std::map<string, string>> filevector(0);
	filevector.reserve(0);
	if (exists(p))    // does path p actually exist?
	{

		filevector = get_file_list("resources/blocks/");
	}
	else
	{
		cout << "ERROR!!!! resources/blocks dont exists!!!" << endl;
	}
	map<string, string>::const_iterator map_iter;
	for (unsigned int i = 0; i < filevector.size(); i++)
	{
	
	for (map_iter = filevector[i].begin(); map_iter != filevector[i].end(); ++map_iter)
	{
		
		string bname;
		//auto btexture = TextureManager::loadTexture(bname, m_res);
	/*	if (!btexture.loadFromFile(map_iter->first))
		{
			cout << map_iter->first << " not loaded!" << endl;
		}*/
		bname = map_iter->second;
		AddIwmoBlock(bname);
	}
	}
	

}

/*void Game::EventHandling(CSource* sourc)
{
	m_ls = sourc;
	instanceEH = dynamic_cast<Game*>(eventhandler);
	instanceEH->m_hookEvent(m_ls);
	__raise sourc->OnEvent(sf::Event());
}*/
void Game::m_hookEvent(CSource* pSource)
{
	if (debug)
	{
		cout << "Not hooked... Called from game" << endl;
	}
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
void Game::LS()
{
	m_engine->AddSoundBuffer("kidjump");
	m_engine->LoadSound("jump1.ogg", "kidjump");
	m_engine->AddSoundBuffer("kiddoublejump");
	m_engine->LoadSound("jump2.ogg", "kiddoublejump");
	m_engine->AddSoundBuffer("kiddeath");
	m_engine->LoadSound("death.ogg", "kiddeath");
	m_engine->AddSoundBuffer("kidfire");
	m_engine->LoadSound("fire.ogg", "kidfire");
}
void Game::StartGame(Engine* engine,CSource* source)
{
	eventhandler = new GameHandler(this);
	instanceEH = eventhandler;
	
	m_ls = source;
	instanceEH = dynamic_cast<Game*>(eventhandler);
	instanceEH->m_hookEvent(m_ls);
	__raise source->OnEvent(sf::Event());
	static kid mykid;
	auto lss = this->m_ls;
	mykid.createKid("resources/kid.xml", kidSheet, sf::Vector2f(100, 100), m_engine, lss,kidDeathSheet,&camera);
	m_engine->Addentity(&mykid, 0);
	mykid.setPos(Iwmo::KidSpawn);
	m_engine->gamestarted = true;
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
void Game::LoadSheets()
{
	if (!kidSheet->loadFromFile("resources/kid.png"))
	{
		cout << "Kid spritesheet not loaded!" << endl;
	}
	if (!kidDeathSheet->loadFromFile("resources/effects/poof.png"))
	{
		cout << "Poof spritesheet not loaded!" << endl;
	}
}
Game::Game(Engine* engine, RenderWindow* wind,CSource* source)
{
	InitIwmoBlocks();
	
	window = wind;
	m_engine = engine;
	m_engine->RemoveAll();
	LoadSheets();
	
	LS();

	for (int i = 0; i < 10; i++)
	{
		engine->AddLayer(i);
	}
	engine->LoadMap("map.tmx");

	camera.setCenter(CAM_CENTER);
	camera.setSize(CAM_SIZE);
	window->setView(camera);
	engine->SetCam(&camera);
	engine->GetWindow()->setKeyRepeatEnabled(false);
	Texture* wall = GetBlockTextureByName("wall.png");
	for (int i = 0; i < 10; i++)
	{
		sf::Vector2f offset(wall->getSize().x*i, (-32));
		m_engine->AddBlock(new Block(wall, sf::Vector2f(0,3200) + offset));
	}
	//
	StartGame(m_engine,source);
}


Game::~Game()
{
}

GameHandler::GameHandler()
{

}
GameHandler::GameHandler(const Game* geim)
{
	gameinstance = const_cast<Game*> (geim);
	m_engine = gameinstance->m_engine;
}
GameHandler::~GameHandler()
{

}

void GameHandler::m_hookEvent(CSource* pSource) {
	cout << "Hooked! Called from GameHandler!" << endl;
	__hook(&CSource::OnEvent, pSource, &GameHandler::OnEvent, this);
	__hook(&CSource::OnCustomEvent, pSource, &GameHandler::OnCustomEvent, this);
}

void GameHandler::m_unhookEvent(CSource* pSource) {
	__unhook(&CSource::OnEvent, pSource, &GameHandler::OnEvent);
}
void GameHandler::OnCustomEvent(CustomEvent event)
{

	switch (event.eventtype)
	{
	case Types::EntityMoveEvent:
		break;
	case Types::EntityShootEvent:
		{	
		EntityShootEvent* e = reinterpret_cast<EntityShootEvent*>(&event);
		//cout << e->whichEntity << endl;
		}
		break;
	case Types::KidShootEvent:
		{	
		KidShootEvent* e = reinterpret_cast<KidShootEvent*>(&event);
		e->whichKid = static_cast<kid*>(e->whichEntity);
		}
		break;
	}

}
void GameHandler::OnEvent(Event eventt)
{
	
	event = eventt;
	if (m_engine != NULL)
	{
		if (event.type == Event::Resized)
		{
			auto win = m_engine->GetWindow();
			sf::Vector2u size = win->getSize();
			win->setSize(size);

			camera.setSize(size.x, size.y);
		}
		try {
			vector<vector<iwmoEntity*>> entities = gameinstance->m_engine->GetEntities();
			for (unsigned int i = 0; i < entities.size(); i++)
			{
				for (unsigned int i1 = 0; i1 < entities.at(i).size(); i1++)
				{
					{

						entities.at(i).at(i1)->MGetEvent(eventt);
						
					}

				}
			}
		}
		catch (exception e)
		{
			cout << e.what() << endl;
		}
	}
}