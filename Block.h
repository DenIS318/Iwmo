#pragma once
#pragma warning(disable : 4996)
#include <SFML\Graphics.hpp>
#include <iostream>
#include <fstream>
#include "TextureManager.h"
//#include "IwmoConfig.h"
#include "iwmoTypes.h"
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>
#include <boost/serialization/version.hpp>
#include <boost/serialization/split_member.hpp>
using namespace sf;
using namespace std;
using namespace Iwmo;
namespace Iwmo {
	class Block
	{
	public:
		Uint8 GetTransparency();
		/*For serizialization-constructor*/
		Block(BlockSettings settings, Vector2f pos) : Block(settings.name, settings.folder, settings.blocktype) { 
		thisSettings = settings;
		sprite.setPosition(pos); 
		}
		[[deprecated("only for serialization")]]
		Block();
		Block(string str, string folder,BlockType blocktype);
		[[deprecated("use string constructor, or set blockname after creation")]]
		 Block(Texture* texture,int x,int y,BlockType blocktype);
		 [[deprecated("use string constructor, or set blockname after creation")]]
		 Block(Texture* texture, sf::Vector2<int>  position, BlockType blocktype);
		 [[deprecated("use string constructor, or set blockname after creation")]]
		Block(Texture* texture, sf::Vector2f  position, BlockType blocktype);
		Block Reset();
		//Block(BlockSettings settings, Vector2f position) : thisSettings(settings), StartPosition(position) {}
		void SetPos(sf::Vector2f pos);
		sf::FloatRect GetGlobalRect();
		~Block();
		Sprite sprite;
		void SetTransparency(Uint8 transparency);
		BlockType blocktype = unknownblock;
		bool killable = false;
		bool animated = false;
		bool Resetable = false;
		bool flipped = false;
		bool trap = false;
		bool fake = false;
		bool jumpthru = false;
		string blockname;
		BlockSettings GetSettings();
		void UpdateSettings(BlockSettings newSettings);

		void read(std::ifstream *in) { in->read((char *)this, sizeof(Block)); }
		void write(std::ofstream *out) { out->write((char *)this, sizeof(Block)); }
	private:
		int transparency = 255;
		void AddToManager(string texturename, string folder);
		///SERIZALIZATION
		BlockSettings thisSettings;

		/*
		friend class boost::serialization::access;
		template<class Archive>
		void save(Archive & ar, const unsigned int version) const
		{
			// note, version is always the latest when saving
		/*	ar  & thisSettings;
			ar  & StartPosition;
		}
		template<class Archive>
		void load(Archive & ar, const unsigned int version)
		{
			if (version > 0)
			{
				ar & thisSettings;
				ar  & StartPosition;
			}
		}
		*/
		//BOOST_SERIALIZATION_SPLIT_MEMBER()
		///END
	};
	
}
//BOOST_CLASS_VERSION(Block, 1)