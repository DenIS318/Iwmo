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
	Engine::layerrentity.clear();
	Engine::layerr.clear();
	Engine::layerr = vector<vector<Drawable*>>(maxlayersize);
	Engine::layerrentity = vector<vector<iwmoEntity*>>(maxlayersize);
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
void Engine::AddLayer()
{
	vector<Drawable*> tempvector;
	Engine::layerr.push_back(tempvector);
	vector<iwmoEntity*> tempvectorentity;
	Engine::layerrentity.push_back(tempvectorentity);
	vector<Block*> tempvectorblock;
	Engine::MapBlocks.push_back(tempvectorblock);
	vector<iwmoEffect*> tempvectoreffects;
	Engine::effectlayers.push_back(tempvectoreffects);
}
void Engine::RemoveLayer(unsigned short layernum)
{
	Engine::layerr.erase(std::remove(Engine::layerr.begin(), Engine::layerr.end(), Engine::layerr[layernum]), Engine::layerr.end());
	Engine::effectlayers.erase(std::remove(Engine::effectlayers.begin(), Engine::effectlayers.end(), Engine::effectlayers[layernum]), Engine::effectlayers.end());
	Engine::layerrentity.erase(std::remove(Engine::layerrentity.begin(), Engine::layerrentity.end(), Engine::layerrentity[layernum]), Engine::layerrentity.end());
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
vector<vector<iwmoEntity*>>& Engine::getEntityLayers()
{
	return Engine::layerrentity;
}
vector<vector<iwmoEffect*>>* Engine::getEffectLayers()
{
	return &effectlayers;
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
void Engine::AddEffect(iwmoEffect* effect, unsigned short layernum)
{
	Engine::effectlayers.at(layernum).push_back(effect);
}
void Engine::RemoveEffect(iwmoEffect* ef, unsigned short layernum)
{
	effectlayers[layernum].erase(std::remove(effectlayers[layernum].begin(), effectlayers[layernum].end(), ef), effectlayers[layernum].end());
	delete ef;
}
void Engine::RemoveEffect(iwmoEffect* ef)
{
	for (unsigned int i = 0; i < effectlayers.size(); i++)
	{
		effectlayers[i].erase(std::remove(effectlayers[i].begin(), effectlayers[i].end(), ef), effectlayers[i].end());
	}
	delete ef;
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
///WRAPPERS
namespace ImGui
{
	static auto vector_getter = [](void* vec, int idx, const char** out_text)
	{
		auto& vector = *static_cast<std::vector<std::string>*>(vec);
		if (idx < 0 || idx >= static_cast<int>(vector.size())) { return false; }
		*out_text = vector.at(idx).c_str();
		return true;
	};

	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return Combo(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

	bool ListBox(const char* label, int* currIndex, std::vector<std::string>& values)
	{
		if (values.empty()) { return false; }
		return ListBox(label, currIndex, vector_getter,
			static_cast<void*>(&values), values.size());
	}

}
std::string remove_extension(const std::string& filename) {
	size_t lastdot = filename.find_last_of(".");
	if (lastdot == std::string::npos) return filename;
	return filename.substr(0, lastdot);
}
void Engine::UpdateBlockList(vector<IwmoBlock>* newlist)
{
	//get name without extension
	for (auto it = newlist->begin(); it != newlist->end(); ++it)
	{
		auto val = *it._Ptr;
		listboxvector.push_back(remove_extension(val.blockname));
	}
	blocklistptr = newlist;
}
void Engine::DrawImguiTilesets()
{
	if (ShowTilesets)
	{
		if (ImGui::TreeNode("Tilesets"))
		{
			ImGui::BeginChild("make", Vector2f(60, 30), false);
			if (ImGui::Checkbox("Make", &make))
			{
				if (make)
				{
					//duplicate
					BlockType type = solid;
					//block selected
					//let allow to create his prototype
					selectedblock = new Sprite();
					selectedblock->setTexture(*blocklistptr->at(listbox_item_current).textureptr);
					blockprototype = new Block(blocklistptr->at(listbox_item_current).blockname, type);
				}
			}
			ImGui::EndChild();
			ImGui::BeginChild("BlockList", Vector2f(300, 200), false);
		
		if (ImGui::ListBox("Select block", &listbox_item_current, listboxvector))
		{
			if (make)
			{
				BlockType type = solid;
				//block selected
				//let allow to create his prototype
				selectedblock = new Sprite();
				selectedblock->setTexture(*blocklistptr->at(listbox_item_current).textureptr);
				blockprototype = new Block(blocklistptr->at(listbox_item_current).blockname, type);
				
			}
			
		}
		///
		//popup
		//ImGui::BeginPopup("BlockPop");
		//blocklist->at(listbox_item_current).textureptr;
		//ImGui::EndPopup();
		///
		ImGui::EndChild();
		ImGui::TreePop();
		}
		if(!make)
		{
			delete selectedblock;
			delete blockprototype;
			if (selectedblock != NULL)
			{
				selectedblock = NULL;
				blockprototype = NULL;
			}
		}
		//ImGui::TreePop();
	
	}
}
void Engine::ImguiMaker()
{
	//main tooltip
	if (ShowImgui)
	{
		ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize |
			ImGuiWindowFlags_NoMove |
			ImGuiWindowFlags_AlwaysAutoResize
			;

		//ImGui::ShowUserGuide();
		//ImGui::ShowTestWindow(&ShowImgui);
		//flags |= ImGuiWindowFlags_NoTitleBar;
		ImGui::Begin("Maker", &ShowImgui, flags);
		ImGui::SetWindowSize("Maker", Vector2f(300, 300));
		Vector2f v = ImGui::GetWindowSize();
		ImGui::SetWindowPos(Vector2f(WinSize.x - v.x - 50 , 0));
		ImGui::Text("Welcome, again!");
		DrawImguiTilesets();
		imguisize = ImGui::GetWindowSize();
		imguipos = ImGui::GetWindowPos();
		ImGui::End();
	}
}
void Engine::Render()
{



	float m__time = clock.getElapsedTime().asMicroseconds();

	m__time = m__time / 500; 

	if (m__time > 40) { m__time = 40; }
	window.clear();
	if (CameraSetted)
	{
		window.setView(*CamPointer);
	}
	ImGui::SFML::Update(window, clock.restart());

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
			window.draw(*(Engine::layerr.at(myi).at(myi1)));
		}
	}
	gg:
	for (unsigned int myi = 0; myi < effectlayers.size(); myi++)
	{
		for (unsigned int myi1 = 0; myi1 < effectlayers.at(myi).size(); myi1++)
		{
			try {
				effectlayers.at(myi).at(myi1)->updatetime(m__time);
				effectlayers.at(myi).at(myi1)->anim.tick(m__time);
				effectlayers.at(myi).at(myi1)->tick(m__time);
				effectlayers.at(myi).at(myi1)->draw(&window);
			}
			catch (out_of_range e)
			{
				goto gg;
			}
		}
	}
	if (selectedblock != NULL)
	{
		window.draw(*selectedblock);
	}
	///
	if (gamestarted)
	{
		if (ClientIsMaker)
		{
			if (!ShowImgui)
			{
				ShowImgui = true;
			}
			ImguiMaker();
		}
	}

	///
	ImGui::SFML::Render(window);
	//cout << ImGui::GetIO().Framerate << endl;
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
	ImGui::SFML::Init(window);
	//window.setVerticalSyncEnabled(true);
}