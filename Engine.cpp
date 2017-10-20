#include "Engine.h"
const string m_spath = "resources/sounds/";
float fps;
bool CameraSetted = false;
View* CamPointer;

//
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
#define vector2d MapBlocks
void Engine::ResetBlocks()
{
	//TODO vector2d iterator template

	vector< vector<Block*> >::iterator row;
	vector<Block*>::iterator col;
	for (row = vector2d.begin(); row != vector2d.end(); row++) {
		for (col = row->begin(); col != row->end(); col++) {
			// do stuff ...
			auto p = *col;
			if (p->Resetable)
			{
				this->ResetBlock(p);
			}
		}
	}
}
#undef vector2d
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
	for (unsigned int i = 0; i < Engine::layerrentity.size(); i++)
	{
		for (unsigned int i1 = 0; i1 < Engine::layerrentity.at(i).size(); i1++)
		{
			delete Engine::layerrentity.at(i).at(i1);
		}
	}
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
	vector<Block*> tempvectorblock;
	Engine::MapBlocks.push_back(tempvectorblock);
}
void Engine::RemoveLayer(unsigned short layernum)
{
	Engine::layerr.erase(std::remove(Engine::layerr.begin(), Engine::layerr.end(), Engine::layerr[layernum]), Engine::layerr.end());
	Engine::MapBlocks.erase(std::remove(Engine::MapBlocks.begin(), Engine::MapBlocks.end(), Engine::MapBlocks[layernum]), Engine::MapBlocks.end());
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
void Engine::AddBlock(Block* b,int layernumber)
{
	MapBlocks[layernumber].push_back(b);
}
void Engine::RemoveBlock(Block* b, unsigned short layernumber)
{
	Engine::MapBlocks[layernumber].erase(std::remove(Engine::MapBlocks[layernumber].begin(), Engine::MapBlocks[layernumber].end(), b), Engine::MapBlocks[layernumber].end());


	delete b;
}
void Engine::RemoveBlock(Block* b)
{
	for (unsigned int i = 0; i < Engine::MapBlocks.size(); i++)
	{
		Engine::MapBlocks[i].erase(std::remove(Engine::MapBlocks[i].begin(), Engine::MapBlocks[i].end(), b), Engine::MapBlocks[i].end());
	}
	delete b;
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
		
		for (unsigned int i = 0; i < Engine::MapBlocks.size(); i++)
		{
			for (unsigned int i1 = 0; i1 < Engine::MapBlocks[i].size(); i1++)
			{
				window.draw((Engine::MapBlocks.at(i)[i1]->sprite));

			}
		}
		for (unsigned int i = 0; i < Engine::layerrentity.size(); i++)
		{
			for (unsigned int i1 = 0; i1 < Engine::layerrentity.at(i).size(); i1++)
			{
				{
					Engine::layerrentity.at(i).at(i1)->updatetime(m__time);
					Engine::layerrentity.at(i).at(i1)->anim.tick(m__time);
					Engine::layerrentity.at(i).at(i1)->tick(m__time);
					Engine::layerrentity.at(i).at(i1)->control();
					if (Engine::layerrentity.at(i).at(i1)->visible)
					{
						Engine::layerrentity.at(i).at(i1)->draw(&window);
					}
				}

			}
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
	window.setSize(sf::Vector2u(Width, Height));
	//window.setVerticalSyncEnabled(true);
}