#include "Engine.h"

//using namespace IwmoEngine;
tmx::MapLoader m_map("resources/");
float fps;
bool CameraSetted = false;
View* CamPointer;
void Engine::RemoveAll()
{
	/*for (unsigned int i = 0; i < Engine::layerr.size(); i++)
	{
	Engine::layerr[i].clear();
	}*/

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
		window.draw(m_map);
	}
	for (unsigned int i = 0; i < Engine::layerr.size(); i++)
	{
		for (unsigned int i1 = 0; i1 < Engine::layerr.at(i).size(); i1++)
		{
			//cout << Engine::layerr.at(i).size()<<endl; 

			window.draw(*(Engine::layerr.at(i).at(i1)));
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
				Engine::layerrentity.at(i).at(i1)->anim.tick(m__time);
				Engine::layerrentity.at(i).at(i1)->updatetime(m__time);
				Engine::layerrentity.at(i).at(i1)->control();
				//cout << Engine::layerrentity.at(i).at(i1)->anim.currentAnim.at(0) << endl;
				Engine::layerrentity.at(i).at(i1)->draw(&window);
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
	//window.setVerticalSyncEnabled(true);
}