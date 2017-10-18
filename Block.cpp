#include "Block.h"


namespace Iwmo {
	void Block::SetPos(Vector2f pos)
	{
		sprite.setPosition(pos);
	}
	void Block::AddToManager(string texturename)
	{
		TextureManager::loadTexture(texturename,"resources/blocks/"+texturename);
	}
	Block Block::Reset()
	{
		Texture* t = const_cast<Texture*>(sprite.getTexture());
		float mx = sprite.getPosition().x;
		float my = sprite.getPosition().y;
		//mx = 0;
		//my = 0;
		return Block(t, mx, my);
	}
	FloatRect Block::GetGlobalRect()
	{
		return sprite.getGlobalBounds();
	}
	Block::Block(string str)
	{
		AddToManager(str);
		sprite.setTexture(*TextureManager::getTexture(str));
		auto size = TextureManager::getTexture(str)->getSize();
		sprite.setOrigin(size.x / 2, size.y / 2);
	}
	Block::Block( Texture* texture,int x,int y)
	{
		Vector2<int> vecpos(x, y);
		
		sprite.setTexture(*texture);
		SetPos(Vector2f(vecpos));
		//sprite.setTextureRect(IntRect(x, y, texture->getSize().x, texture->getSize().y));
	}
	Block::Block( Texture* texture,Vector2<int> position)
	{
		
		sprite.setTexture(*texture);
		SetPos(Vector2f(position));
		//sprite.setTextureRect(IntRect(position.x, position.y, texture->getSize().x, texture->getSize().y));
	}
	Block::Block(Texture* texture, Vector2f position)
	{
		
		sprite.setTexture(*texture);
		SetPos(position);
		//sprite.setTextureRect(IntRect(position.x, position.y, texture->getSize().x, texture->getSize().y));
	}

	Block::~Block()
	{
	}
}