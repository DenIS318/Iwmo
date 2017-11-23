#include "Engine.h"
const string m_spath = "resources/sounds/";
float fps;
bool CameraSetted = false;
View* CamPointer;
class kid;
kid* m_ClientKid = NULL;
void StopNoRemove(Music* music)
{
	if (music != NULL)
	{
		music->pause();
		music->setPlayingOffset(sf::seconds(0));
	}
}
kid* Engine::ClientKid()
{
	return m_ClientKid;
}
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
void Engine::RemoveAll(bool keep)
{
	for (unsigned int i = 0; i < boxvector.size(); i++)
	{
		removeTextBox(Engine::boxvector[i]);
	}
	for (unsigned int i = 0; i < textlist.size(); i++)
	{
		RemoveText(Engine::textlist[i]);
	}
	if (!keep)
	{
		for (unsigned int i = 0; i < Engine::layerrentity.size(); i++)
		{
			for (unsigned int i1 = 0; i1 < Engine::layerrentity.at(i).size(); i1++)
			{
				delete Engine::layerrentity.at(i).at(i1);
			}
		}
		layerrentity.clear();
		Engine::layerrentity = vector<vector<iwmoEntity*>>(maxlayersize);
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
		delete Engine::bulletlist.at(i);
	}
	effectlayers.clear();
	MapBlocks.clear();
	intlayer.clear();
	bulletlist.clear();
	textlist.clear();
	boxvector.clear();
	Engine::layerr.clear();
	Engine::layerr = vector<vector<Drawable*>>(maxlayersize);
	Engine::effectlayers = vector<vector<iwmoEffect*>>(maxlayersize);
	MapBlocks = vector<IwmoLayer>(maxlayersize);
	
}
Engine::Engine()
{
	
}
//absolute position, ie heard everythere
void Engine::AddMusic(Music* music,string name,bool absolute)
{
	music->setRelativeToListener(absolute);
	if (!absolute)
	{
		music->setPosition(boundsCenter().x, boundsCenter().y, 0);
	}
	string bonus = "";
	while (allmusic->count(name + bonus) > 0)
	{
		if (bonus == "")
		{
			bonus = "1";
		}
		else
		{
			bonus = to_string(stoi(bonus) + 1);
		}
	}
	string comboname = name + bonus;
	Sprite* spr = new Sprite();
	spr->setTexture(MusicTexture);
	spr->setOrigin(MusicTexture.getSize().x / 2, MusicTexture.getSize().y / 2);
	spr->setPosition(music->getPosition().x,music->getPosition().y);
	MusicSprites.insert(pair<string, Sprite*>(comboname, spr));
	allmusic->insert(pair<string, Music*>(comboname,music));
	NowPlaying.push_back(name+bonus);
}
void Engine::setListenerPosition(Vector3f pos)
{
	sf::Listener::setPosition(pos);
	ListenerSprite.setPosition(pos.x,pos.y);
	//TODO SEND PACKET
}
void Engine::SetSuperMaker(bool b)
{
	superMaker = b;
}
string Engine::FindMusicPtr(Music* music)
{
	for (auto it = allmusic->begin(); it != allmusic->end(); ++it)
	{
		auto val = *it._Ptr;
		if (val._Myval.second == music)
		{
			return val._Myval.first;
		}
	}
	return "";
}
void Engine::RemoveMusic(Music* music)
{
	music->stop(); 
	auto musicname = FindMusicPtr(music);
	auto it = allmusic->find(musicname);
	auto itSpr = MusicSprites.find(musicname);
	NowPlaying.erase(remove(NowPlaying.begin(), NowPlaying.end(), musicname), NowPlaying.end());
	delete MusicSprites[musicname];
	MusicSprites.erase(itSpr);
	allmusic->erase(it);
	music->~Music();
	if (CurrentMusic = music)
	{
		CurrentMusic = NULL;
	}
}
void Engine::PlayMusic(Music* music,bool StopPrev)
{
	if (StopPrev)
	{
		if (CurrentMusic != NULL)
		{
			StopNoRemove(CurrentMusic);
		}
	}
	CurrentMusic = music;
	music->play();
}
Engine::~Engine()
{
}
bool compareLen(const std::string& a, const std::string& b)
{
	return (a.length() < b.length());
}
void sortmusic(vector<string>* vec)
{
	std::sort(vec->begin(), vec->end(), compareLen);
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
void Engine::RemoveText(Text* text)
{
	delete text;
	textlist.erase(std::remove(textlist.begin(),textlist.end(), text),textlist.end());
}
void Engine::AddText(Text* text)
{
	textlist.push_back(text);
}
void Engine::addTextBox(mytextbox* textbox)
{
	boxvector.push_back(textbox);
}
void Engine::removeTextBox(mytextbox* textbox)
{
	boxvector.erase(std::remove(boxvector.begin(), boxvector.end(), textbox), boxvector.end());
	delete textbox;
}
void Engine::AddLayer()
{
	vector<Drawable*> tempvector(0);
	Engine::layerr.push_back(tempvector);
	vector<iwmoEntity*> tempvectorentity(0);
	Engine::layerrentity.push_back(tempvectorentity);
	IwmoLayer templayer;
	templayer.objects.resize(0);
	Engine::MapBlocks.push_back(templayer);
	vector<iwmoEffect*> tempvectoreffects(0);
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
bool Engine::EffectIsOK(iwmoEffect* effect)
{
	return effect->anim.currentAnim!="";
}
void Engine::RemoveEffect(iwmoEffect* ef, unsigned short layernum)
{
	if (EffectIsOK(ef))
	{
		effectlayers[layernum].erase(std::remove(effectlayers[layernum].begin(), effectlayers[layernum].end(), ef), effectlayers[layernum].end());
		delete ef;
		ef = NULL;
	}
}
void Engine::RemoveEffect(iwmoEffect* ef)
{
	if (EffectIsOK(ef))
	{
		for (unsigned int i = 0; i < effectlayers.size(); i++)
		{
			effectlayers[i].erase(std::remove(effectlayers[i].begin(), effectlayers[i].end(), ef), effectlayers[i].end());
		}
		delete ef;
		ef = NULL;
	}
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
bool compareNoCase(const string& s1, const string& s2) {
	return strcasecmp(s1.c_str(), s2.c_str()) <= 0;
}
bool CompareBlockNames(IwmoBlock elem1, IwmoBlock elem2)
{
	return compareNoCase(elem1.blockname, elem2.blockname);
}
void Engine::UpdateBlockList(vector<IwmoBlock>* newlist)
{

	//sorting
	std::sort(newlist->begin(), newlist->end(), CompareBlockNames);
	listboxvector.clear();
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
		blockprototype->UpdateSettings(blockSettings);
	}
}
void Engine::UpdateMouseRect()
{
	auto mousepos = Mouse::getPosition(window);
	auto newpos = window.mapPixelToCoords(mousepos);
	if (!sf::Keyboard::isKeyPressed(HotkeyNoGrid))
	{
		int x = newpos.x;
		int y = newpos.y;
		newpos.x = (x / (GridSize.x)) * (GridSize.x);
		newpos.y = (y / (GridSize.y)) * (GridSize.y);
		newpos += Vector2f(GridSize.x / 2, GridSize.y / 2);
	}	
		
	mouseboundsshow.setPosition(newpos);
	mouseboundsshow.setSize(Vector2f(GridSize));
	int x = mouseboundsshow.getPosition().x;
	int y = mouseboundsshow.getPosition().y;
	float posx, posy;
	posx = x - (x % 800) + 400;
	posy = y - (y % 608) + 304;
	Vector2f vec(posx, posy);
	vec = vec - Vector2f(Width / 2, Height / 2);
	//vec.y = vec.y + 2;
	bounds.setPosition(vec);
	minimap.setCenter(vec);
}
void Engine::BlockListSelectBlock(Block* b)
{
	for (auto it = listboxvector.begin(); it != listboxvector.end(); ++it)
	{
		auto val = *it._Ptr;
		
			if (val == remove_extension(b->blockname))
			{
				listbox_item_current = it - listboxvector.begin();
				return;
			}
			
	}
}
struct is_valid
{
	is_valid(const std::string& a_wanted) : wanted(a_wanted) {}
	std::string wanted;
	bool operator()(const std::string& str)
	{
		return str.compare(wanted) == 0;
	}
};
template<typename Base, typename T>
inline bool instanceof(const T *ptr) {
	return dynamic_cast<const Base*>(ptr) != nullptr;
}
static std::wstring charToWString(const char* text)
{
	const size_t size = std::strlen(text);
	std::wstring wstr;
	if (size > 0) {
		wstr.resize(size);
		std::mbstowcs(&wstr[0], text, size);
	}
	return wstr;
}
void Engine::FilterVector(string filter)
{
	FilteredElements = vector<string>(0);
	auto it = std::copy_if(listboxvector.begin(), listboxvector.end(), std::back_inserter(FilteredElements), is_valid(filter));

}
View* Engine::GetCam()
{
	return CamPointer;
}
void Engine::clearMusiclist()
{
	for (auto it = allmusic->begin(); it != allmusic->end(); ++it)
	{
		auto val = *it._Ptr;
		val._Myval.second->~Music();
		//val->~Music();
	}
	allmusic->clear();
	NowPlaying.clear();
	CurrentMusic = NULL;
	//not need
	//MusicList.clear();
}
Engine::MusicPrototype Engine::MusicToPrototype(Music* music)
{
	MusicPrototype prototype;
	prototype.attention = music->getAttenuation();
	prototype.loop = music->getLoop();
	prototype.MinDistance = music->getMinDistance();
	prototype.name = FindMusicPtr(music);
	return prototype;
}
void Engine::UpdateMusicList()
{
	using namespace boost::filesystem;
	path p = "resources/Music/";
	std::vector<std::map<string, string>> filevector(0);
	MusicList.clear();
	if (exists(p))    // does path p actually exist?
	{

		filevector = get_file_list(p.string());
			for (unsigned int i = 0; i < filevector.size(); i++)
			{

				for (auto it = filevector[i].begin(); it != filevector[i].end(); ++it)
				{
					string name = it->second;
					MusicList.push_back(name);
				}
			}
		sortmusic(&MusicList);
	}
	else
	{
		error = true;
		errorfile = "resources/Music";
	}
}
void Engine::PickMusic(bool StopPrevious,bool absolute)
{
	if (musicPrototype != NULL)
	{
		Music* PickedMusic = new Music();
		if (PickedMusic->openFromFile("resources/Music/" + musicPrototype->name))
		{
			PickedMusic->setAttenuation(musicPrototype->attention);
			PickedMusic->setLoop(musicPrototype->loop);
			
			AddMusic(PickedMusic,musicPrototype->name);
			PlayMusic(PickedMusic,StopPrevious);
		}
		else
		{
			error = true;
			errorfile = musicPrototype->name;
			PickedMusic->~Music();
		}
	}
}
static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(450.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}
Vector2f Engine::boundsCenter()
{
	auto center = bounds.getPosition() + Vector2f(bounds.getSize().x / 2, bounds.getSize().y / 2);
	return center;
}
void Engine::DrawImguiTilesets()
{
	if (ShowTilesets)
	{
		if (ImGui::TreeNode("Tilesets"))
		{

			ShowFilters = !ImGui::IsWindowCollapsed();
			if (ImGui::Checkbox("Make", &make))
			{
				if (make)
				{
					//duplicate
					if (blockprototype != NULL)
					{
						delete blockprototype;
						if (blockprototype != NULL)
						{
							blockprototype = NULL;
						}
					}
					BlockType type = blocklistptr->at(listbox_item_current).blocktype;
					//block selected
					//let allow to create his prototype
					blockprototype = new Block(blocklistptr->at(listbox_item_current).blockname, blocklistptr->at(listbox_item_current).folder, type);
					UpdatePrototype();

				}
			}
			ImGui::Checkbox("Show mouse bounds", &showbounds);
			if (ImGui::InputInt("Grid size X", &GridSize.x))
			{
				if (GridSize.x < 1)
				{
					GridSize.x = 1;
				}
				UpdateMouseRect();
			}
			if (ImGui::InputInt("Grid size Y", &GridSize.y))
			{
				if (GridSize.y < 1)
				{
					GridSize.y = 1;
				}
				UpdateMouseRect();
			}
			if (ImGui::ListBox("Select block", &listbox_item_current, listboxvector))
			{
				if (make)
				{
					if (blockprototype != NULL)
					{
						delete blockprototype;
						if (blockprototype != NULL)
						{
							blockprototype = NULL;
						}
					}
					blockSettings = BlockSettings();
					blockSettings.layer = selectedlayer;
					BlockType type = blocklistptr->at(listbox_item_current).blocktype;
					//block selected
					//let allow to create his prototype
					blockprototype = new Block(blocklistptr->at(listbox_item_current).blockname, blocklistptr->at(listbox_item_current).folder, type);
					UpdatePrototype();
				}

			}

			ImGui::TreePop();
		}
		if (!make)
		{
			bool finded;
			for (int i = 0; i < MapBlocks.size(); i++)
			{
				auto v = MapBlocks[i].objects;
				if (std::find(v.begin(), v.end(), blockprototype) != v.end()) {
					//contains
					blockSettings = BlockSettings();
					delete blockprototype;
					blockprototype = NULL;
					finded = true;
					UpdatePrototype();
					break;
				}

			}
			if (!finded)
			{
				//not contains
				blockSettings = BlockSettings();
				delete blockprototype;
				if (blockprototype != NULL)
				{
					blockprototype = NULL;
				}
				UpdatePrototype();
			}



		}
		///Layers editor
		//ImGui::BeginChild("Layers editor", Vector2f(350, 200), false);
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
		//ImGui::EndChild();
		///TEXT EDITOR
		//ImGui::BeginChild("Text editor", Vector2f(350, 200), false);

		if (ImGui::TreeNode("Text"))
		{
			ImGui::PushFont(defaultfont);
			ImGui::InputTextMultiline("##source", textbuffer, IMGUI_ARRAYSIZE(textbuffer), Vector2f(-1.0f, ImGui::GetTextLineHeight() * 8), ImGuiInputTextFlags_AllowTabInput);
			ImGui::PopFont();
			ImGui::InputInt("Text character size", &textcharsize);
			ImGui::InputFloat("Text scale X", &textscale.x);
			ImGui::InputFloat("Text scale Y", &textscale.y);
			///
			//we dont want null,yeah?
			if (textscale.x <= 0)
			{
				textscale.x = 1;
			}
			if (textscale.y <= 0)
			{
				textscale.y = 1;
			}
			if (textcharsize <= 0)
			{
				textcharsize = 1;
			}
			///
			ImGui::ColorEdit4("Color", textcolor, ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_RGB | ImGuiColorEditFlags_NoOptions);
			if (ImGui::Button("Pick text"))
			{
				blockprototype = NULL;
				if (textprototype != NULL)
				{
					delete textprototype;
				}
				UpdatePrototype();
				String txt(textbuffer); // note String(SFML STRING), not an std string
				textprototype = new Text();
				textprototype->setString(txt);
				textprototype->setFont(font);
				textprototype->setCharacterSize(textcharsize);
				textprototype->setOrigin(textprototype->getLocalBounds().width / 2, textprototype->getLocalBounds().height / 2);
				textprototype->setPosition(mouseboundsshow.getPosition());
				Color color;
				color.r = (textcolor[0] * 255.f);
				color.g = (textcolor[1] * 255.f);
				color.b = (textcolor[2] * 255.f);
				color.a = (textcolor[3] * 255.f);
				textprototype->setFillColor(color);
				textprototype->setScale(textscale);
			}

			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Camera"))
		{
			ImGui::Checkbox("Show minimap", &ShowMinimap);
			if (ShowMinimap)
			{
				ImGui::InputFloat("Minimap Size X", &MinimapSize.x, 10.F, 100.0F);
				ImGui::InputFloat("Minimap Size Y", &MinimapSize.y, 10.F, 100.0F);
				if (MinimapSize.x <= 0)
				{
					MinimapSize.x = 1;
				}
				if (MinimapSize.y <= 0)
				{
					MinimapSize.y = 1;
				}
				ImGui::InputFloat("Minimap viewport Size X", &MinimapViewportSize.x, 0.05F, 0.1F);
				ImGui::InputFloat("Minimap viewport Size Y", &MinimapViewportSize.y, 0.05F, 0.1F);
				if (MinimapViewportSize.x > 0.50)
				{
					MinimapViewportSize.x = 0.50;
				}
				if (MinimapViewportSize.y > 0.50)
				{
					MinimapViewportSize.y = 0.50;
				}
				if (ImGui::Button("Reset minimap", Vector2f(100, 20)))
				{
					MinimapSize = Vector2f(Width * 3, Height * 3);
					MinimapViewportSize = Vector2f(0.25, 0.25);
				}
			}
			ImGui::Checkbox("Show screen bounds", &ShowScreenBounds);
			if (ImGui::Checkbox("Free camera", &FreeCamera))
			{
				for (auto it = layerrentity.begin(); it != layerrentity.end(); ++it)
				{
					auto firstval = *it._Ptr;
					for (auto it2 = firstval.begin(); it2 != firstval.end(); ++it2)
					{
						auto val = *it2._Ptr;

						val->ScreenCamera = !FreeCamera;

					}
				}

			}
			if (FreeCamera)
			{
				ImGui::InputFloat("Scrolling speed X axis", &Scrollingratio.x, 1.0F, 10.0F);
				ImGui::InputFloat("Scrolling speed Y axis", &Scrollingratio.y, 1.0F, 10.0F);
				if (Scrollingratio.x <= 0)
				{
					Scrollingratio.x = 1;
				}
				if (Scrollingratio.y <= 0)
				{
					Scrollingratio.y = 1;
				}

			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Music"))
		{
			ImGui::Text("Place all your music to 'Music' folder (resources/Music/)");
			ShowHelpMarker("If you will have many music (above 256) in game, you can obtain many troubles, keep it in mind");
			if (ImGui::Button("Update music list", Vector2f(150, 20)))
			{
				UpdateMusicList();
			}
			if (ImGui::ListBox("Music list", &selectedMusicIndex, MusicList))
			{
				musicPrototype = new MusicPrototype();
				musicPrototype->name = MusicList[selectedMusicIndex];

			}
			if (error)
			{
				auto message = "Error! '" + errorfile + "' not opened";
				if (errorfile == "resources/Music")
				{
					message = "Error! resources/Music not exists, or game has not permission to open it";
				}
				ImGui::TextColored(Color::Red, message.c_str());
			}
			ImGui::Separator();
			if (ImGui::ListBox("Now playing", &nowplayingIndex, NowPlaying))
			{
				CurrentMusic = allmusic->at(NowPlaying[nowplayingIndex]);
				*musicPrototype = MusicToPrototype(CurrentMusic);
				//currentMusicSprite.setPosition(CurrentMusic->getPosition().x, CurrentMusic->getPosition().y);

			}
			if (ImGui::Button("Play/pause", Vector2f(100, 20)))
			{
				if (CurrentMusic != NULL)
				{
					if (CurrentMusic->getStatus() == Music::Status::Paused)
					{
						CurrentMusic->play();
					}
					else if (CurrentMusic->getStatus() == Music::Status::Playing)
					{
						CurrentMusic->pause();
					}
				}				
			}
			if (ImGui::Button("Stop", Vector2f(40, 20)))
			{
				StopNoRemove(CurrentMusic);
			}
			if (CurrentMusic != NULL)
			{
				if (ImGui::Button("Remove current music"))
				{
					RemoveMusic(CurrentMusic);
				}
			}
			if (musicPrototype != NULL)
			{
				ImGui::Checkbox("Stop previous music", &StopPrev);
				if (ImGui::Button("Pick music and play"))
				{
					error = false;
					errorfile = "";
					PickMusic(StopPrev);
				}
				ImGui::SameLine();
				ShowHelpMarker("Music position will be setted to selected screen, you can teleport current playing music to your mouse by pressing N");
				if (ImGui::InputInt("Attenuation", &musicPrototype->attention,1,100))
				{
					if (musicPrototype->attention < 0)
					{
						musicPrototype->attention = 0;
					}
					if (musicPrototype->attention > 100)
					{
						musicPrototype->attention = 100;
					}
				}
				ImGui::SameLine();
				ShowHelpMarker("Set the attenuation factor of the sound. The attenuation is a multiplicative factor which makes the sound more or less loud according to its distance from the listener. An attenuation of 0 will produce a non - attenuated sound, i.e. its volume will always be the same whether it is heard from near or from far. On the other hand, an attenuation value such as 100 will make the sound fade out very quickly as it gets further from the listener.");
				if (ImGui::InputFloat("Minimal distance", &musicPrototype->MinDistance,1,10,1))
				{
					if (musicPrototype->MinDistance < 0)
					{
						musicPrototype->MinDistance = 0;
					}
					if (musicPrototype->MinDistance > FLT_MAX)
					{
						musicPrototype->MinDistance = FLT_MAX;
					}
				}
				ImGui::SameLine();
				ShowHelpMarker("The 'minimum distance' of a sound is the maximum distance at which it is heard at its maximum volume.Further than the minimum distance, it will start to fade out according to its attenuation factor.A value of 0 ('inside the head of the listener') is an invalid value and is forbidden.");
				ImGui::Checkbox("Loop", &musicPrototype->loop);
				
			}
			ImGui::Checkbox("Show music location",&showMusicsSpr);
			if (superMaker)
			{
				if (ImGui::TreeNode("Listener"))
				{
					ImGui::TextColored(Color::Yellow, "Listener are global for all makers");
					ImGui::Checkbox("Show listener", &ShowListener);
					if (ImGui::Button("Teleport listener to this screen", Vector2f(220, 20)))
					{
						setListenerPosition(Vector3f(boundsCenter().x, boundsCenter().y, 0));
					}
					ImGui::TreePop();
				}
			}
			if (superMaker)
			{
				if (ImGui::Button("Clear ALL music"))
				{
					clearMusiclist();
				}
			}
			ImGui::TreePop();
		}
		else
		{
			if (error)
			{
				error = false;
				errorfile = "";
			}
		}
		if (ImGui::TreeNode("Hotkeys"))
		{
			Color color(255, 127, 80, 255);
			for (int i = 0; i < Hotkeys.size(); i++)
			{
				auto key = *Hotkeys[i];
				auto tooltip = HotkeysName.at(i).c_str();
				ImGui::Text(tooltip);
				ImGui::SameLine();
				ImGui::TextColored(color, getKeyName(key));
			}
			ImGui::TreePop();
		}
		if (ImGui::TreeNode("Misc"))
		{
			if (ImGui::Button("Clear selected screen", Vector2f(160, 20)))
			{
				auto vec = GetBlocksAtRect(bounds);
				if (!vec.empty())
				{
					for (auto it = vec.begin(); it != vec.end(); it++)
					{
						auto val = *it._Ptr;
						RemoveBlock(val,val->GetSettings().layer);
					}
				}
			}
			if (superMaker)
			{
				if (ImGui::Button("Clear map", Vector2f(80, 20)))
				{
					for (auto layerit = MapBlocks.begin(); layerit != MapBlocks.end(); ++layerit)
					{
						auto layer = *layerit._Ptr;
						for (auto it = layer.objects.begin(); it != layer.objects.end(); ++it)
						{
							auto b = *it._Ptr;
							RemoveBlock(b, b->GetSettings().layer);
						}
					}

				}
				ImGui::SameLine();
				ImGui::TextColored(ImVec4(Color::Red), "Delete ALL blocks!");
			}
			ImGui::TreePop();
		}
		///property editor
		if (blockprototype != NULL)
		{
			blockSettings.layer = selectedlayer;
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
					"Type","Killable","Resetable","ScaleX","ScaleY","Fake","Jump-thru","Transparency"
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
							ImGui::Checkbox("##1", &blockSettings.Killable);
						}
						if (i == 2)
						{
							ImGui::Checkbox("##2", &blockSettings.Resetable);
						}
						if (i == 3)
						{
							ImGui::InputFloat("##3", &blockSettings.ScaleX, 0.1f);
						}
						if (i == 4)
						{
							ImGui::InputFloat("##4", &blockSettings.ScaleY, 0.1f);
						}
						if (i == 5)
						{
							ImGui::Checkbox("##5", &blockSettings.fake);
							ImGui::SameLine();
							ShowHelpMarker("Disable behaviors, like collision, jumpthru, etc...");
						}
						if (i == 6)
						{
							ImGui::Checkbox("##6", &blockSettings.jumpthru);
							ImGui::SameLine();
							ShowHelpMarker("Block type must be solid. Press down arrow to jump-through block.");
						}
						if (i == 7)
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
		}
		
	}
}
void Engine::ImguiMaker()
{
	//main tooltip
	ImGuiWindowFlags flags = 
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_AlwaysAutoResize;
		ImguiOpen = true;
		ImGui::Begin("Maker", &ImguiOpen, flags);
		ImguiCollappsed = ImGui::IsWindowCollapsed();
		ImGui::SetWindowSize("Maker", Vector2f(300, 300));
		Vector2f v = ImGui::GetWindowSize();
		auto ppos = window.getSize();
		ImGui::SetWindowPos(Vector2f(ppos.x- v.x-10 , 10));
		ImGui::Text("Welcome, again!");
		ImGui::Checkbox("Keep mouse inside window", &KeepMouse);
		DrawImguiTilesets();
		imguisize = ImGui::GetWindowSize();
		imguipos = ImGui::GetWindowPos();
		ImGui::End();
}
void Engine::AddBullet(Bullet* bul)
{
	bulletlist.push_back(bul);
}
//at layer
vector<Block*> Engine::GetBlocksAtRect(RectangleShape rect, int layer)
{
	vector<Block*> vec;
	for (auto it = MapBlocks[layer].objects.begin(); it != MapBlocks[layer].objects.end(); ++it)
	{
		auto val = *it._Ptr;
		if (rect.getGlobalBounds().contains(val->sprite.getPosition()) && val != blockprototype)
		{
			vec.push_back(val);
		}
	}
	return vec;
}
//at all layers
vector<Block*> Engine::GetBlocksAtRect(RectangleShape rect)
{
	vector<Block*> vec;
	for (int layer = 0; layer < MapBlocks.size(); layer++)
	{
		for (auto it = MapBlocks[layer].objects.begin(); it != MapBlocks[layer].objects.end(); ++it)
		{
			auto val = *it._Ptr;
			if (rect.getGlobalBounds().contains(val->sprite.getPosition()) && val != blockprototype)
			{
				vec.push_back(val);
			}
		}
	}
	return vec;
}
///

//at layer
vector<Block*> Engine::GetBlocksAtRect(FloatRect rect, int layer)
{
	vector<Block*> vec;
	for (auto it = MapBlocks[layer].objects.begin(); it != MapBlocks[layer].objects.end(); ++it)
	{
		auto val = *it._Ptr;
		if (rect.contains(val->sprite.getPosition()) && val != blockprototype)
		{
			vec.push_back(val);
		}
	}
	return vec;
}
//at all layers
vector<Block*> Engine::GetBlocksAtRect(FloatRect rect)
{
	vector<Block*> vec;
	for (int layer = 0; layer < MapBlocks.size(); layer++)
	{
		for (auto it = MapBlocks[layer].objects.begin(); it != MapBlocks[layer].objects.end(); ++it)
		{
			auto val = *it._Ptr;
			if (rect.contains(val->sprite.getPosition()) && val != blockprototype)
			{
				vec.push_back(val);
			}
		}
	}
	return vec;
}
//at all layers
vector<Block*> Engine::GetBlocksIntersectedAtRect(FloatRect rect)
{
	vector<Block*> vec;
	for (int layer = 0; layer < MapBlocks.size(); layer++)
	{
		for (auto it = MapBlocks[layer].objects.begin(); it != MapBlocks[layer].objects.end(); ++it)
		{
			auto val = *it._Ptr;
			if (rect.intersects(val->sprite.getGlobalBounds()) && val != blockprototype)
			{
				vec.push_back(val);
			}
		}
	}
	return vec;
}

///
//at all layers
vector<Text*> Engine::GetTextAtRect(RectangleShape rect)
{
	auto newsize = rect.getSize();
	auto newpos = rect.getPosition();
	rect.setSize(newsize);
	rect.setPosition(newpos);
	vector<Text*> vec;
		for (auto it = textlist.begin(); it != textlist.end(); ++it)
		{
			auto val = *it._Ptr;
			if (rect.getGlobalBounds().contains(val->getPosition()) && val != textprototype)
			{
				vec.push_back(val);
			}
		}
	return vec;
}
void Engine::DrawMap(float m__time,bool Minimap)
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
	for (int i = 0; i < textlist.size(); i++)
	{
		if(textlist.at(i)->getString().toAnsiString() != NameStringHelp && textlist.at(i)->getString().toAnsiString() != IpStringHelp)
		window.draw(*textlist.at(i));
	}
	for (unsigned int myi = 0; myi < Engine::bulletlist.size(); myi++)
	{
		if (!Minimap)
		{
			Engine::bulletlist.at(myi)->tick();
		}
		Engine::bulletlist.at(myi)->Draw(&window, m__time);
	}
	for (unsigned int i = 0; i < Engine::layerrentity.size(); i++)
	{
		for (unsigned int i1 = 0; i1 < Engine::layerrentity.at(i).size(); i1++)
		{
			{
				if (!Minimap)
				{
					Engine::layerrentity.at(i).at(i1)->updatetime(m__time);
					Engine::layerrentity.at(i).at(i1)->anim.tick(m__time);
					if(Engine::layerrentity.at(i).at(i1)->yourkid)
					{
						Engine::layerrentity.at(i).at(i1)->tick(m__time);
						Engine::layerrentity.at(i).at(i1)->control();
					}
					Engine::layerrentity.at(i).at(i1)->UpdateState();
				}
				if (Engine::layerrentity.at(i).at(i1)->visible)
				{
					Engine::layerrentity.at(i).at(i1)->draw(&window);
				}
			}

		}
	}
	for (unsigned int myi = 0; myi < effectlayers.size(); myi++)
	{
		for (unsigned int myi1 = 0; myi1 < effectlayers.at(myi).size(); myi1++)
		{
			if (effectlayers.at(myi)[myi1] != NULL)
			{
				auto val = effectlayers.at(myi)[myi1];
				if (EffectIsOK(val))
				{
					auto check = (iwmoEntity*)val;
					if (check != NULL)
					{
						if (!Minimap)
						{
							val->updatetime(m__time);
							val->tick(m__time);
						}
						if (val->visible)
						{

							val->draw(&window);
						}

					}
				}
			}
		}
	}
	if (showMusicsSpr)
	{
		for (auto it = MusicSprites.begin(); it != MusicSprites.end(); ++it)
		{
			auto val = it._Ptr->_Myval;
			auto curmusicname = FindMusicPtr(CurrentMusic);
			if (val.first == curmusicname)
			{
				window.draw(*val.second);
			}
			else
			{
				window.draw(*val.second, &shader);
			}
		}
	}
	if (ShowListener)
	{
		window.draw(ListenerSprite);
	}
}
void Engine::SetCamFromGame(View* ptr)
{
	CamPointer = ptr;
	ptr->setViewport(FloatRect(0, 0, 1, 1));
}
void Engine::Render()
{
	float m__time = clock.getElapsedTime().asMicroseconds();
	m__time = m__time / 500;
	if (m__time > framerate) { m__time = framerate; }
	window.clear();
	ImGui::SFML::Update(window, clock.restart());
	if (gamestarted)
	{
		UpdateMouseRect();
	}

	if (CamPointer != NULL)
	{
		window.setView(*CamPointer);
		DrawMap(m__time, false);
	}
	if (ClientIsMaker && ShowMinimap && gamestarted)
	{
		minimap.setSize(MinimapSize);
		minimap.setViewport(FloatRect(Vector2f(0, 0), MinimapViewportSize));
		window.setView(minimap);
		DrawMap(m__time, true);
	}
	if (CamPointer != NULL)
	{
		window.setView(*CamPointer);
	}
	for (unsigned int myi = 0; myi < Engine::layerr.size(); myi++)
	{
		for (unsigned int myi1 = 0; myi1 < Engine::layerr.at(myi).size(); myi1++)
		{
			window.draw(*(Engine::layerr.at(myi).at(myi1)));
		}
	}

	UpdatePrototype();
	if (ClientIsMaker && ShowScreenBounds && gamestarted)
	{
		window.draw(bounds);
	}
	if (blockprototype != NULL)
	{
		window.draw(blockprototype->sprite);
	}
	if (textprototype != NULL)
	{
		window.draw(*textprototype);
	}
	///
	if (gamestarted)
	{
		if (ClientIsMaker)
		{
			ImguiMaker();
		}
	}
	if (ClientIsMaker && showbounds)
	{
		window.draw(mouseboundsshow);
		
	}
	for (auto it = boxvector.begin(); it != boxvector.end(); ++it)
	{
		auto val = *it._Ptr;
		val->update();
		if ( val->visible())
		{
			window.draw(*val);
			window.draw(val->text);
		}
	}
	for (unsigned int i = 0; i < textlist.size(); i++)
	{
		if (textlist.at(i)->getString().toAnsiString() == NameStringHelp || textlist.at(i)->getString().toAnsiString() == IpStringHelp)
		{
			window.draw(*textlist.at(i));
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
	if (!font.loadFromFile("resources/Arial.ttf"))
	{
		cout << "Font not loaded" << endl;
	}
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
	mouseboundsshow.setFillColor(Color::Transparent);
	mouseboundsshow.setOutlineColor(Color::Red);
	mouseboundsshow.setOutlineThickness(1);
	mouseboundsshow.setOrigin(GridSize.x / 2, GridSize.y / 2);
	ImGui::SFML::Init(window);
	font_config.OversampleH = 1; //or 2 is the same
	font_config.OversampleV = 1;
	font_config.PixelSnapH = 1;

	static const ImWchar ranges[] =
	{
		0x0020, 0x00FF, // Basic Latin + Latin Supplement
		0x0400, 0x044F, // Cyrillic
		0,
	};
	ImGuiIO& io = ImGui::GetIO();
	defaultfont = io.Fonts->AddFontFromFileTTF("resources/Arial.ttf", 14,&font_config,ranges);
	io.FontDefault = io.Fonts->AddFontDefault();
	ImGui::SFML::UpdateFontTexture();
	bounds.setOutlineColor(Color::Red);
	bounds.setOutlineThickness(-1);
	bounds.setSize(Vector2f(Width,Height));
	bounds.setFillColor(Color::Transparent);
	if (tex.loadFromFile("resources/listener.png"))
	{
		ListenerSprite.setTexture(tex);
		ListenerSprite.setOrigin(tex.getSize().x / 2, tex.getSize().y / 2);
	}
	else
	{
		cout << "Listener image not loaded!" << endl;
	}
	MusicTexture.loadFromFile("resources/music.png");
}