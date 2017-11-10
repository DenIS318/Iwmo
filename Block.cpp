#include "Block.h"


namespace Iwmo {
	Block::Block()
	{

	}
	BlockSettings Block::GetSettings()
	{
		return thisSettings;
	}
	void Block::SetTransparency(Uint8 t)
	{
		Color c = sprite.getColor();
		sprite.setColor(sf::Color(c.r, c.g, c.b, t));
		transparency = t;
	}
	void Block::UpdateSettings(BlockSettings newSettings)
	{
		thisSettings = newSettings;
		///
		killable = thisSettings.Killable;
		Resetable = thisSettings.Resetable;
		blocktype = thisSettings.blocktype;
		sprite.setScale(thisSettings.ScaleX, thisSettings.ScaleY);
		fake = thisSettings.fake;
		SetTransparency(thisSettings.transparency);
		jumpthru = thisSettings.jumpthru;
		///
	}
	Uint8 Block::GetTransparency()
	{
		return transparency;
	}
	void Block::SetPos(Vector2f pos)
	{
		sprite.setPosition(pos);
	}
	void Block::AddToManager(string texturename,string folder)
	{
		TextureManager::loadTexture(texturename,folder+texturename);
	}
	Block Block::Reset()
	{
		Texture* t = TextureManager::getTexture(blockname);
		float mx = sprite.getPosition().x;
		float my = sprite.getPosition().y;
		//mx = 0;
		//my = 0;
		Block b(t, mx, my, blocktype);
		b.blockname = blockname;
		return b;
	}
	FloatRect Block::GetGlobalRect()
	{
		return sprite.getGlobalBounds();
	}
	Block::Block(string str, string folder,BlockType bltype)
	{
		
		if (folder.find("/") == string::npos)
		{
			folder = "resources/" + folder + "/";
		}
		AddToManager(str,folder);
		sprite.setTexture(*TextureManager::getTexture(str));
		auto size = TextureManager::getTexture(str)->getSize();
		sprite.setOrigin(size.x / 2, size.y / 2);
		blockname = (str);
		blocktype = bltype;
	}
	
	Block::Block( Texture* texture,int x,int y,BlockType bltype)
	{
		Vector2<int> vecpos(x, y);
		
		sprite.setTexture(*texture);
		SetPos(Vector2f(vecpos));
		blocktype = bltype;
	}
	
	Block::Block( Texture* texture,Vector2<int> position, BlockType bltype)
	{
		
		sprite.setTexture(*texture);
		SetPos(Vector2f(position));
		blocktype = bltype;
	}
	
	Block::Block(Texture* texture, Vector2f position, BlockType bltype)
	{
		
		sprite.setTexture(*texture);
		SetPos(position);
		blocktype = bltype;
	}

	Block::~Block()
	{
	}
}