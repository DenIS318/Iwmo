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
	if (!success && filter == "background")
	{
		// avoid repeated path construction below
		subpath = respath + "background";
		bltype = BlockType::decoration;
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
	/*m_engine->AddSoundBuffer("castleentrance");
	m_engine->LoadSound("castleentrance.ogg", "castleentrance");*/
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
	sf::View standard = camera;
	auto minimap = View(camera);
	engine->minimap = minimap;
	auto nullval = m_engine->ClientKid();
	nullval = &mykid;
	if (!castleent.openFromFile("resources/Music/castleentrance.ogg"))
	{
		cout << "castle entrance not loaded!" << endl;
	}
	else
	{
		castleent.setAttenuation(0);
		m_engine->AddMusic(&castleent);
		castleent.setLoop(true);
		m_engine->PlayMusic(&castleent);
	}
	m_engine->UpdateMusicList();
	m_engine->ShowTilesets = true;
	m_engine->gamestarted = true;
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
	//std::ofstream filestream("resources/maps/Default");
	
	std::ifstream ifs("resources/maps/default.im");
	if (ifs.good())
	{
		BlockSettings settings;
		Vector2f ppos;
		/*
		boost::archive::binary_iarchive ia(ifs);
		ia >> settings;
		ia >> ppos;
		*/
		Block newblock;
		newblock.read(&ifs);
		//TODO
		cout << "loaded block " << newblock.blockname << endl;
		m_engine->AddBlock(&newblock, newblock.GetSettings().layer);

	}
	else
	{
		///bad archive
		Texture* castle2 = GetBlockTextureByName("castle2.png");
		Texture* castlewall2 = GetBlockTextureByName("castlewall2.png");
		for (int i = 0; i < 25; i++)
		{
			if (i == 0)
			{
				//vertical wall
				sf::Vector2f offset(castle2->getSize().x*i + 16, (32));
				Block* b = new Block("castle2.png", "resources/blocks/", Iwmo::BlockType::solid);
				
				b->SetPos((sf::Vector2f(0, 3600) + offset));
				auto set = b->GetSettings();
				set.layer = tilesl;
				b->UpdateSettings(set);
				m_engine->AddBlock(b, tilesl);

			}
			else
			{
				//horizontal wall
				sf::Vector2f offset(castlewall2->getSize().x*i + 16, (32));
				Block* b = new Block("castlewall2.png", "resources/blocks/", Iwmo::BlockType::solid);
				b->SetPos((sf::Vector2f(0, 3600) + offset));
				auto set = b->GetSettings();
				set.layer = tilesl;
				b->UpdateSettings(set);
				m_engine->AddBlock(b, tilesl);
			}
		}
	}
	
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
	InitIwmoBlocks("background");
	m_engine->UpdateBlockList(&IwmoBlocks);
	//
	//load sprites sheets
	LoadSheets();
	//load sounds
	LS();
	//camera
	camera.setCenter(CAM_CENTER);
	camera.setSize(CAM_SIZE);
	engine->SetCamFromGame(&camera);
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
			if (event.key.code == HotkeyMake)
			{
				m_engine->make = !m_engine->make;
			}
		}
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == HotkeyMinimap)
			{
				m_engine->ShowMinimap = !m_engine->ShowMinimap;
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