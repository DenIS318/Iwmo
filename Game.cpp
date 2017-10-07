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
const Vector2f KidSpawn(50, 3100);
void Game::EventHandling(CSource* sourc)
{
	m_ls = sourc;
	instanceEH = dynamic_cast<Game*>(eventhandler);
	instanceEH->m_hookEvent(m_ls);
	__raise sourc->OnEvent(sf::Event());
}
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
	m_engine->LoadSound("death.wav", "kiddeath");
	m_engine->AddSoundBuffer("kidfire");
	m_engine->LoadSound("fire.wav", "kidfire");
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
	eventhandler = new GameHandler(this);
	instanceEH = eventhandler;
	engine->GetWindow()->setKeyRepeatEnabled(false);
	
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
	InitIwmoBlocks();
	
	window = wind;
	m_engine = engine;
	m_engine->RemoveAll();
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
	LS();
	static kid mykid;
	mykid.createKid("resources/kid.xml", kidSheet, Vector2f(100, 100), m_engine);
	//mykid.SettingHandler((GameHandler*)eventhandler);
	m_engine->Addentity(&mykid, 0);
	mykid.setPos(KidSpawn);
	Texture* wall = GetBlockTextureByName("wall.png");
	for (int i = 0; i < 10; i++)
	{
		Vector2f offset(wall->getSize().x*i, (-32));
		
		
		m_engine->AddBlock(Block(wall, Vector2f(0,3200) + offset));
	}
	m_engine->gamestarted = true;
	//
	StartGame(m_engine);
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
}
GameHandler::~GameHandler()
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
	//cout << "0 BIETCH" << endl;
	try {
		vector<vector<iwmoEntity*>> entities = gameinstance->m_engine->GetEntities();
		for (unsigned int i = 0; i < entities.size(); i++)
		{
			for (unsigned int i1 = 0; i1 <  entities.at(i).size(); i1++)
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