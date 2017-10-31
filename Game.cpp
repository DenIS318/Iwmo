#include "Game.h"

GameHandler* eventhandler;
Game* instanceEH ;

vector<IwmoBlock>* Game::GetBlockList()
{
	return &IwmoBlocks;
}

void Game::AddIwmoBlock(string name,BlockType type,string mpath)
{
	/*
	name,texture,type,subfolder
	*/
	Texture* texture = TextureManager::loadTexture(name, mpath+name);
	if (texture == NULL)
	{
		return;
	}
	IwmoBlock blockmap;
	blockmap.blockname = name;
	blockmap.textureptr = texture;
	blockmap.blocktype = type;
	blockmap.folder = mpath;
	IwmoBlocks.push_back(blockmap);
}

Block Game::CreateBlockByName(string name)
{
	for (auto it = IwmoBlocks.begin(); it != IwmoBlocks.end(); ++it)
	{
		if (it->blockname == name)
		{
			Block b(it->blockname, it->folder, it->blocktype);
			return b;
		}
	}
	cout << "Block '" << name << "'" << " not found!" << endl;
	return Block(new Texture(), 0, 0,BlockType::unknownblock);
}
Texture* Game::GetBlockTextureByName(string name)
{
	for (auto it = IwmoBlocks.begin(); it != IwmoBlocks.end(); ++it)
	{
		if (it->blockname == name)
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
void Game::InitIwmoBlocks(string filter)
{
	BlockType bltype = BlockType::unknownblock;
	path p;
	
	string subpath;
	bool trap = false;
	bool success = false;
	if (filter == "solids")
	{
		// avoid repeated path construction below
		subpath = respath + "blocks/";
		bltype = BlockType::solid;
		p = subpath;
		success = true;
	}
	if (!success && filter == "traps")
	{
		// avoid repeated path construction below
		subpath = respath + "traps/";
		bltype = BlockType::solid;
		p = subpath;
		success = true;
	}
	if (!success && filter == "decorations")
	{
		// avoid repeated path construction below
		subpath = respath + "decorations/";
		bltype = BlockType::decoration;
		p = subpath;
		success = true;
	}
	if (!success && filter == "animated")
	{
		// avoid repeated path construction below
		subpath = respath + "animated/";
		p = subpath;
		success = true;
		
	}
	if (!success)
	{
		cout << "Invalid filter '" << filter << "', blocks not initialized" << endl;
		return;
	}
	std::vector<std::map<string, string>> filevector(0);
	filevector.reserve(0);
	if (exists(p))    // does path p actually exist?
	{

		filevector = get_file_list(subpath);
	}
	else
	{
		cout << "ERROR!!!! " << subpath << " dont exists!!!" << endl;
	}
	map<string, string>::const_iterator map_iter;
	for (unsigned int i = 0; i < filevector.size(); i++)
	{

		for (map_iter = filevector[i].begin(); map_iter != filevector[i].end(); ++map_iter)
		{

			string bname;
			bname = map_iter->second;
			AddIwmoBlock(bname, bltype,subpath);
		}
	}


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
	m_engine->AddSoundBuffer("castleentrance");
	m_engine->LoadSound("castleentrance.ogg", "castleentrance");
	m_engine->AddSoundBuffer("kidjump");
	m_engine->LoadSound("jump1.ogg", "kidjump");
	m_engine->AddSoundBuffer("kiddoublejump");
	m_engine->LoadSound("jump2.ogg", "kiddoublejump");
	m_engine->AddSoundBuffer("kiddeath");
	m_engine->LoadSound("death.ogg", "kiddeath");
	m_engine->AddSoundBuffer("kidfire");
	m_engine->LoadSound("bullet.flac", "kidfire");
}
void Game::StartGame(Engine* engine, CSource* source)
{
	eventhandler = new GameHandler(this);
	instanceEH = eventhandler;

	m_ls = source;
	instanceEH = dynamic_cast<Game*>(eventhandler);
	instanceEH->m_hookEvent(m_ls);
	__raise source->OnEvent(sf::Event());
	static kid mykid;
	auto lss = this->m_ls;
	mykid.createKid("resources/kid.xml", kidSheet, sf::Vector2f(100, 100), m_engine, lss, kidDeathSheet, &camera);
	m_engine->Addentity(&mykid, 0);
	mykid.setPos(Iwmo::KidSpawn);
	m_engine->gamestarted = true;
	

	if (!castleent.openFromFile("resources/sounds/castleentrance.ogg"))
	{
		cout << "castle entrance not loaded!" << endl;
	}
	m_engine->allmusic.push_back(&castleent);
	castleent.setLoop(true);
	castleent.play();
	if (debug)
	{

	}
	m_engine->ShowTilesets = true;
	cout << "Game started!" << endl;
	
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
//TODO
void Game::INITMAP()
{
	
	Texture* castle2 = GetBlockTextureByName("castle2.png");
	Texture* castlewall2 = GetBlockTextureByName("castlewall2.png");
	Texture* liana = GetBlockTextureByName("liana.png");
	for (int i = 0; i < 25; i++)
	{
		if (i == 0)
		{
			//vertical wall
			sf::Vector2f offset(castle2->getSize().x*i, (32));
			Block* b = new Block("castle2.png", "resources/blocks/", Iwmo::BlockType::solid);
			b->SetPos((sf::Vector2f(0, 3600) + offset));
			m_engine->AddBlock(b, tilesl);

		}
		else
		{
			//horizontal wall
			sf::Vector2f offset(castlewall2->getSize().x*i, (32));
			Block* b = new Block("castlewall2.png", "resources/blocks/", Iwmo::BlockType::solid);
			b->SetPos((sf::Vector2f(0, 3600) + offset));
			m_engine->AddBlock(b, tilesl);
		}
	}
	/*auto pos1 = Vector2f(200, 3500);
	auto pos2 = Vector2f(300, 3500);
	Block* l = new Block("liana.png","resources/blocks/", Iwmo::BlockType::slidable);
	l->SetPos(pos1);
	Block* lf = new Block("liana.png", "resources/blocks/", Iwmo::BlockType::slidable);
	lf->SetPos(pos2 + Vector2f(18, 0));
	m_engine->FlipBlock(lf);
	m_engine->AddBlock(l,tiles2l);
	Block* bb = new Block("castle2.png", "resources/blocks/", BlockType::solid);
	bb->SetPos(pos1);
	Block* bb2 = new Block("castle2.png", "resources/blocks/", BlockType::solid);
	bb2->SetPos(pos2);
	m_engine->AddBlock(bb, tilesl);
	m_engine->AddBlock(bb2, tilesl);
	m_engine->AddBlock(lf, tiles2l);*/
		
		
	
}
Game::Game(Engine* engine, RenderWindow* wind,CSource* source)
{
	window = wind;
	m_engine = engine;
	m_engine->RemoveAll();
	//
	/*
	Inits layers
	*/
	for (int i = 0; i < 7; i++)
	{
		engine->AddLayer();
	}
	//
	//init blocks by filters
	InitIwmoBlocks("solids");
	InitIwmoBlocks("traps");
	InitIwmoBlocks("decorations");
	InitIwmoBlocks("animated");
	m_engine->UpdateBlockList(&IwmoBlocks);
	//
	//load sprites sheets
	LoadSheets();
	//load sounds
	LS();
	//camera
	camera.setCenter(CAM_CENTER);
	camera.setSize(CAM_SIZE);
	window->setView(camera);
	engine->SetCam(&camera);
	engine->GetWindow()->setKeyRepeatEnabled(false);
	INITMAP();
	
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
	__hook(&CSource::OnEvent, pSource, &GameHandler::OnEvent, this);
	__hook(&CSource::OnCustomEvent, pSource, &GameHandler::OnCustomEvent, this);
}

void GameHandler::m_unhookEvent(CSource* pSource) {
	__unhook(&CSource::OnEvent, pSource, &GameHandler::OnEvent);
}
void GameHandler::OnCustomEvent(CustomEvent* event)
{

	switch (event->eventtype)
	{
	case Types::EntityMoveEvent:
		break;
	case Types::DestroyEffectEvent:
		{
		DestroyEffectEvent* e = reinterpret_cast<DestroyEffectEvent*>(event);
		m_engine->RemoveEffect(e->whichEffect);
		//auto kekus = m_engine->effectlayers;
		//cout << &kekus << endl;
		//cout << &m_engine->effectlayers << endl;
		}
		break;
	case Types::EntityShootEvent:
		{	
		EntityShootEvent* e = reinterpret_cast<EntityShootEvent*>(event);
		//cout << e->whichEntity << endl;
		}
		break;
	case Types::KidShootEvent:
		{	
		KidShootEvent* e = reinterpret_cast<KidShootEvent*>(event);
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
			m_engine->WinSize = size;
			camera.setSize(size.x, size.y);
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == Keyboard::M)
			{
				if (!m_engine->make)
				{
					m_engine->make = true;
				}
				else
				{
					m_engine->make = false;
				}
			}
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