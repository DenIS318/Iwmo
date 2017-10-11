#include "Engine.h"
static tmx::MapLoader m_map("resources/");
const string m_spath = "resources/sounds/";
float fps;
bool CameraSetted = false;
View* CamPointer;
void Engine::AddSoundBuffer(string name)
{
	bufferlist->insert(pair<string,SoundBuffer>(name,SoundBuffer()));
}
map<string, sf::SoundBuffer>* Engine::buflist()
{
	return bufferlist;
}
void Engine::ResetBlock(Block* b)
{
	Block ResetedBlock = b->Reset();
	b = new Block(ResetedBlock);
}
void Engine::ResetBlocks()
{
	for (auto it = MapBlocks.begin(); it != MapBlocks.end(); ++it)
	{
		auto p = *it;
		if (p->Resetable)
		{
			this->ResetBlock(p);
		}
	}
}
bool Engine::LoadSound(string name,string buffername)
{
	
	if (bufferlist->find(buffername) == bufferlist->end()) {
		return false;
	}
	else {
		if (!bufferlist->at(buffername).loadFromFile(m_spath + name))
		{
			cout << "'" << name << "'" << " not loaded!!!" << endl;
			return false;
		}
	}
	return true;
}
void Engine::RemoveAll()
{
	Engine::layerr.clear();
	Engine::layerr = vector<vector<Drawable*>>(maxlayersize);
}
Engine::Engine()
{

}
void Engine::SetCam(View* campoint)
{
	CamPointer = campoint;
	CameraSetted = true;
}
Engine::~Engine()
{
}
void Engine::AddLayer(unsigned short layernum)
{
	vector<Drawable*> tempvector;
	Engine::layerr.push_back(tempvector);
}
void Engine::RemoveLayer(unsigned short layernum)
{

	Engine::layerr.erase(std::remove(Engine::layerr.begin(), Engine::layerr.end(), Engine::layerr[layernum]), Engine::layerr.end());
}
vector<vector<iwmoEntity*>>& Engine::GetEntities()
{
	return Engine::layerrentity;
}
vector<vector<Drawable*>>& Engine::getLayers()
{
	return Engine::layerr;
}
void Engine::AddSprite(Drawable* drawable, unsigned short layernum)
{
	Engine::layerr.at(layernum).push_back(drawable);
}
void Engine::RemoveSprite(Drawable* drawable, unsigned short layernum)
{
	Engine::layerr[layernum].erase(std::remove(Engine::layerr[layernum].begin(), Engine::layerr[layernum].end(), drawable), Engine::layerr[layernum].end());

	delete drawable;
}
void Engine::RemoveSprite(Drawable* drawable)
{
	for (unsigned int i = 0; i < Engine::layerr.size(); i++)
	{
		Engine::layerr[i].erase(std::remove(Engine::layerr[i].begin(), Engine::layerr[i].end(), drawable), Engine::layerr[i].end());
	}

	delete drawable;
}
void Engine::Addentity(iwmoEntity* man, unsigned short layernum)
{
	Engine::layerrentity.at(layernum).push_back(man);
}
void Engine::Removeentity(iwmoEntity* man, unsigned short layernum)
{
	Engine::layerrentity[layernum].erase(std::remove(Engine::layerrentity[layernum].begin(), Engine::layerrentity[layernum].end(), man), Engine::layerrentity[layernum].end());

	delete man;
}
void Engine::Removeentity(iwmoEntity* man)
{
	for (unsigned int i = 0; i < Engine::layerrentity.size(); i++)
	{
		Engine::layerrentity[i].erase(std::remove(Engine::layerrentity[i].begin(), Engine::layerrentity[i].end(), man), Engine::layerrentity[i].end());
	}

	delete man;
}
void Engine::AddBlock(Block* b)
{
	MapBlocks.push_back(b);
}
void Engine::LoadMap(string mapname)
{

	m_map.addSearchPath("resources/blocks/");
	if (m_map.load(mapname))
	{
		if (debug) {
			cout << "m_map loaded!" << endl;
		}
	}
	else
	{
		if (debug) {
			cout << "m_map NOT LOADED!" << endl;
		}
	}
	
	auto l = m_map.getLayers();
	cout << "SIZE IS " << l.at(0).tiles.size() << endl;
	
	for each (tmx::MapTile tile in l.at(0).tiles)
	{
		maptiles.push_back(&tile.sprite);
	}
	for each (tmx::MapTile tile in l.at(1).tiles)
	{
		maptiles.push_back(&tile.sprite);
	}
}
tmx::MapLoader* Engine::GetMap()
{
	return &m_map;
}
unsigned int Engine::GetFrameRate()
{

	time = clock.getElapsedTime();
	clock.restart().asSeconds();
	fps = 1.0f / time.asSeconds();
	return unsigned int(fps + 0.5);
}

void Engine::Render()
{



	float m__time = clock.getElapsedTime().asMicroseconds();
	clock.restart();

	m__time = m__time / 500;  // çäåñü ðåãóëèðóåì ñêîðîñòü èãðû

	if (m__time > 40) { m__time = 40; }
	window.clear();
	if (CameraSetted)
	{
		window.setView(*CamPointer);
	}
	if (gamestarted)
	{
		//window.draw(m_map);

		for (unsigned int i = 0; i < Engine::MapBlocks.size(); i++)
		{
			window.draw((Engine::MapBlocks.at(i)->sprite));
			//cout << MapBlocks[i].sprite.getPosition().x << ", " << MapBlocks[i].sprite.getPosition().y << endl;
		
		}
	}
	
		for (unsigned int myi = 0; myi < Engine::layerr.size(); myi++)
		{
			for (unsigned int myi1 = 0; myi1 < Engine::layerr.at(myi).size(); myi1++)
			{
				//cout << Engine::layerr.at(myi).size()<<endl; 

				window.draw(*(Engine::layerr.at(myi).at(myi1)));
			}
		}
	

	for (unsigned int i = 0; i < Engine::layerrentity.size(); i++)
	{
		for (unsigned int i1 = 0; i1 < Engine::layerrentity.at(i).size(); i1++)
		{
			//cout << Engine::layerrentity.at(i).size()<<endl; 
			//cout << 0;
			
			{
				//cout << this_thread::get_id() << " THREAD ID IN RENDER" << endl;
				Engine::layerrentity.at(i).at(i1)->updatetime(m__time);
				Engine::layerrentity.at(i).at(i1)->anim.tick(m__time);
				Engine::layerrentity.at(i).at(i1)->control();
				//cout << Engine::layerrentity.at(i).at(i1)->anim.currentAnim.at(0) << endl;
				if (Engine::layerrentity.at(i).at(i1)->visible)
				{
					Engine::layerrentity.at(i).at(i1)->draw(&window);
				}
			}

		}
	}
	//cout << GetFrameRate() << endl;
	window.display();




}
RenderWindow* Engine::GetWindow()
{
	return &window;
}

void Engine::init(int Width, int Height, string title, short fm)
{

	window.create(VideoMode(Width, Height), title);
	window.setFramerateLimit(fm);
	window.setSize(Vector2u(Width, Height));
	//window.setVerticalSyncEnabled(true);
}