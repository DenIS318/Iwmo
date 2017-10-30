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

	vector< IwmoLayer >::iterator row;
	vector<Block*>::iterator col;
	for (row = vector2d.begin(); row != vector2d.end(); row++) {
		
		for (col = row->objects.begin(); col != row->objects.end(); col++) {
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
	for (unsigned int i = 0; i < Engine::effectlayers.size(); i++)
	{
		for (unsigned int i1 = 0; i1 < Engine::effectlayers.at(i).size(); i1++)
		{
			delete Engine::effectlayers.at(i).at(i1);
		}
	}
	for (unsigned int i = 0; i < Engine::MapBlocks.size(); i++)
	{
		for (unsigned int i1 = 0; i1 < Engine::MapBlocks.at(i).objects.size(); i1++)
		{
			delete Engine::MapBlocks.at(i).objects.at(i1);
		}
	}
	for (unsigned int i = 0; i < Engine::bulletlist.size(); i++)
	{
		delete bulletlist.at(i);
	}
	effectlayers.clear();
	MapBlocks.clear();
	intlayer.clear();
	bulletlist.clear();
	Engine::layerrentity.clear();
	Engine::layerr.clear();
	Engine::layerr = vector<vector<Drawable*>>(maxlayersize);
	Engine::layerrentity = vector<vector<iwmoEntity*>>(maxlayersize);
	Engine::effectlayers = vector<vector<iwmoEffect*>>(maxlayersize);
	MapBlocks = vector<IwmoLayer>(maxlayersize);
	
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
bool compareLen(const std::string& a, const std::string& b)
{
	return (a.length() < b.length());
}
void sortstr(vector<string>* vec)
{
	
		for (int iX = 0; iX < vec->size(); iX++)
		{
			//int diff = std::abs(stoi(vec->at(iX)) - 1); 
			int intval = iX+1;
			string str = to_string(intval);
			vec->at(iX) = str;
		}
		std::sort(vec->begin(), vec->end(), compareLen);
		
}
void Engine::AddLayer()
{
	vector<Drawable*> tempvector;
	Engine::layerr.push_back(tempvector);
	vector<iwmoEntity*> tempvectorentity;
	Engine::layerrentity.push_back(tempvectorentity);
	IwmoLayer templayer;
	Engine::MapBlocks.push_back(templayer);
	vector<iwmoEffect*> tempvectoreffects;
	Engine::effectlayers.push_back(tempvectoreffects);
	intlayer.push_back(to_string(MapBlocks.size()));
	sortstr(&intlayer);
}
void Engine::RemoveBlockLayer(unsigned int layernum)
{
	Engine::MapBlocks.erase(MapBlocks.begin() + layernum);
	intlayer.erase(std::remove(intlayer.begin(), intlayer.end(), intlayer[layernum]), intlayer.end());
	sortstr(&intlayer);
}

void Engine::RemoveBullet(Bullet* bullet)
{
	delete bullet;
	bulletlist.erase(std::remove(bulletlist.begin(), bulletlist.end(), bullet), bulletlist.end());
}
void Engine::RemoveLayer(unsigned int layernum)
{
	//vectors are not pointers, this stores pointer, we dont need to delete layers
	Engine::layerr.erase(std::remove(Engine::layerr.begin(), Engine::layerr.end(), Engine::layerr[layernum]), Engine::layerr.end());
	Engine::effectlayers.erase(std::remove(Engine::effectlayers.begin(), Engine::effectlayers.end(), Engine::effectlayers[layernum]), Engine::effectlayers.end());
	Engine::layerrentity.erase(std::remove(Engine::layerrentity.begin(), Engine::layerrentity.end(), Engine::layerrentity[layernum]), Engine::layerrentity.end());
	/*if (&MapBlocks[layernum] != NULL)
	{
		if (&MapBlocks[layernum].objects != NULL)
		{
			delete &MapBlocks[layernum];
		}
	}*/
	//remove layer at index
	Engine::MapBlocks.erase(MapBlocks.begin() + layernum);
	//
	intlayer.erase(std::remove(intlayer.begin(), intlayer.end(), intlayer[layernum]), intlayer.end());
	sortstr(&intlayer);
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
	ef = NULL;
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
	MapBlocks[layernumber].objects.push_back(b);
}
void Engine::RemoveBlock(Block* b, unsigned short layernumber)
{
	Engine::MapBlocks[layernumber].objects.erase(std::remove(Engine::MapBlocks[layernumber].objects.begin(), Engine::MapBlocks[layernumber].objects.end(), b), Engine::MapBlocks[layernumber].objects.end());


	delete b;
}
void Engine::RemoveBlock(Block* b)
{
	for (unsigned int i = 0; i < Engine::MapBlocks.size(); i++)
	{
		Engine::MapBlocks[i].objects.erase(std::remove(Engine::MapBlocks[i].objects.begin(), Engine::MapBlocks[i].objects.end(), b), Engine::MapBlocks[i].objects.end());
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
void Engine::UpdatePrototype()
{
	if (blockprototype != NULL)
	{
		blockprototype->killable = blockSettings.Killable;
		blockprototype->Resetable = blockSettings.Resetable;
		blockprototype->blocktype = blockSettings.blocktype;
		blockprototype->sprite.setScale(blockSettings.ScaleX, blockSettings.ScaleY);
		blockprototype->fake = blockSettings.fake;
		blockprototype->SetTransparency(blockSettings.transparency);
		selectedblock->setColor(blockprototype->sprite.getColor());
		selectedblock->setScale(blockprototype->sprite.getScale());
	}
}
void Engine::DrawImguiTilesets()
{
	if (ShowTilesets)
	{
		if (ImGui::TreeNode("Tilesets"))
		{
			ImGui::BeginChild("make", Vector2f(60, 20), false);
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
			ImGui::BeginChild("BlockList", Vector2f(350, 125), false);
		
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
		///Layers editor
		ImGui::BeginChild("Layers editor", Vector2f(350, 200), false);
		if (ImGui::TreeNode("Layers"))
		{
			ImGui::ListBox("Layers list", &selectedlayer, intlayer);

			if (ImGui::Button("Add layer", Vector2f(100, 20)))
			{
				AddLayer();
				selectedlayer = MapBlocks.size() - 2;
			}
			if (ImGui::Button("Remove layer", Vector2f(100, 20)))
			{
				if (MapBlocks.size() != 0)
				{
					//int prev = 0;
					if (selectedlayer < 0)
					{
						selectedlayer = 0;
						//prev = 2;
					}
					/*if (prev != 0 )
					{
						prev = selectedlayer;
					}*/
					
					RemoveBlockLayer(selectedlayer);
					//begins with 1,not 0, so will -2 instead -1
					if (selectedlayer != 0)
					{
						selectedlayer = selectedlayer - 1;
					}
				}
			}
			ImGui::Checkbox("Layer are visible", &MapBlocks[selectedlayer].visible);
			ImGui::Checkbox("Flash invisible layers", &Flash);
			ImGui::TreePop();
		}
		ImGui::EndChild();
		///property editor
		if (blockprototype != NULL)
		{
			ImGui::BeginChild("propeditor", Vector2f(600, 300), false);
			ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
			ImGui::Columns(2);
			ImGui::Separator();
			ImGui::AlignFirstTextHeightToWidgets();  // Text and Tree nodes are less high than regular widgets, here we add vertical spacing to make the tree lines equal high.
			bool node_open = ImGui::TreeNode((remove_extension(blocklistptr->at(listbox_item_current).blockname)).c_str());
			ImGui::NextColumn();
			ImGui::AlignFirstTextHeightToWidgets();
			ImGui::Text("Selected block");
			ImGui::NextColumn();
			if (node_open)
			{
				string labels[] =
				{
					"Type","Killable","Resetable","ScaleX","ScaleY","Fake","Transparency"
				};
				for (int i = 0; i < (size(labels)); i++)
				{
					{
						ImGui::AlignFirstTextHeightToWidgets();
						ImGui::Text(labels[i].c_str());
						ImGui::NextColumn();
						ImGui::PushItemWidth(-1);
						if (i == 0)
						{
							if (ImGui::ListBox("Block Types", &curtype, blocktypesStr))
							{
								blockSettings.blocktype = blocktypesType[curtype];

							}
						}
						if (i == 1)
						{
							ImGui::Checkbox("Determines, will block kill kid", &blockSettings.Killable);
						}
						if (i == 2)
						{
							ImGui::Checkbox("Determines, will block reset on R press", &blockSettings.Resetable);
						}
						if (i == 3)
						{
							ImGui::InputFloat("Scale by X factor", &blockSettings.ScaleX, 0.1f);
						}
						if (i == 4)
						{
							ImGui::InputFloat("Scale by Y factor", &blockSettings.ScaleY, 0.1f);
						}
						if (i == 5)
						{
							ImGui::Checkbox("Disable collision, killable etc...", &blockSettings.fake);
						}
						if (i == 6)
						{
							ImGui::SliderInt("##line", &blockSettings.transparency, 0, 255);
						}
						ImGui::PopItemWidth();
						ImGui::NextColumn();
					}
				}
				ImGui::TreePop();
			}



			// Iterate dummy objects with dummy members (all the same data)
				///
			ImGui::Columns(1);
			ImGui::Separator();
			ImGui::PopStyleVar();
			ImGui::EndChild();
		}
		
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
		ImguiCollappsed = ImGui::IsWindowCollapsed();
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
void Engine::AddBullet(Bullet* bul)
{
	bulletlist.push_back(bul);
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
			if (MapBlocks[i].visible)
			{
				for (unsigned int i1 = 0; i1 < Engine::MapBlocks[i].objects.size(); i1++)
				{
					if ((Engine::MapBlocks.at(i).objects[i1]->GetTransparency() != 0))
					{
						window.draw((Engine::MapBlocks.at(i).objects[i1]->sprite));
					}

				}
			}
			else if (Flash && ClientIsMaker)
			{
				for (unsigned int i1 = 0; i1 < Engine::MapBlocks[i].objects.size(); i1++)
				{
					if ((Engine::MapBlocks.at(i).objects[i1]->GetTransparency() != 0))
					{
						window.draw((Engine::MapBlocks.at(i).objects[i1]->sprite), &shader);
					}
				}
			}
		}
		for (unsigned int myi = 0; myi < Engine::bulletlist.size(); myi++)
		{
			Engine::bulletlist.at(myi)->tick(&window,m__time);
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
	
	for (unsigned int myi = 0; myi < effectlayers.size(); myi++)
	{
		for (unsigned int myi1 = 0; myi1 < effectlayers.at(myi).size(); myi1++)
		{
			if (effectlayers.at(myi)[myi1] != NULL)
			{
				auto val = effectlayers.at(myi)[myi1];
				auto check = (iwmoEntity*)val;
				if (check != NULL)
				{
					if (val->visible)
					{
						val->updatetime(m__time);
						val->tick(m__time);
						val->draw(&window);
					}
				}
			}
		}
	}
	UpdatePrototype();
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
	debugger.DebugDraw(&window);
	///
	ImGui::SFML::Render(window);
	//cout << ImGui::GetIO().Framerate << endl;
	window.display();
}
RenderWindow* Engine::GetWindow()
{
	return &window;
}
void Engine::FlipBlock(Block* lf)
{
	auto b = lf->sprite.getLocalBounds();
	if (lf->flipped)
	{
		lf->sprite.setTextureRect(sf::IntRect(b.left, b.top, b.width, b.height));
	}
	else
	{		
		lf->sprite.setTextureRect(sf::IntRect(b.width, b.top, -b.width, b.height));
	}
	lf->flipped = !lf->flipped;
}
/*Getting block pointer that position matching point*/
Block* Engine::GetBlockAtPoint(Vector2f point, int layer)
{
	for (auto it = MapBlocks[layer].objects.begin(); it != MapBlocks[layer].objects.end(); ++it)
	{
		auto val = *it._Ptr;
		if (val->sprite.getPosition() == point && val != blockprototype)
		{
			return val;
		}
	}
	return NULL;
}
void Engine::init(int Width, int Height, string title, short fm)
{
	window.create(VideoMode(Width, Height), title);
	window.setFramerateLimit(fm);
	blocktypesStr.push_back("solid");
	blocktypesStr.push_back("decoration");
	blocktypesStr.push_back("slidable");
	blocktypesStr.push_back("unknownblock");
	blocktypesType.push_back(solid);
	blocktypesType.push_back(decoration);
	blocktypesType.push_back(slidable);
	if (!shader.loadFromFile("resources/blur.frag", sf::Shader::Fragment))
	{
		cout << "SHADER NOT LOADED" << endl;
		// error...
	}
	else
	{
		shader.setUniform("texture", sf::Shader::CurrentTexture);
		shader.setUniform("blur_radius",0.5f);
	}
	blocktypesType.push_back(unknownblock);
	ImGui::SFML::Init(window);
}