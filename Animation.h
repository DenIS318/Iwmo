#ifndef ANIMATION_H
#define ANIMATION_H

#include "tinyxml\tinyxml.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#define coutFloatRect m_c_f_r
using namespace std;
using namespace sf;

#define cp ColPoint
enum ColPoint
{
	left,
	right,
	up,
	down
};
class Animation
{
public:
	FloatRect
		Col_up,
		Col_down,
		Col_right,
		Col_left
		;
	vector<vector<FloatRect>> ColRect;
	vector<vector<FloatRect>> ColRectFlip;
	std::vector<IntRect> frames;
	std::vector<IntRect> frames_flip;
	float currentFrame, speed;
	bool loop, flip, isPlaying;   // loop ïîêàçâàåò çàöèêëåíà ëè àíèìàöèÿ. Íàïðèìåð àíèìàöèÿ âçðûâà äîëæíà ïðîèãðàòüñÿ îäèí ðàç è îñòàíîâèòüñÿ, loop=false
	Sprite sprite;

	Animation()
	{
		/*frames.clear();
		frames_flip.clear();
		frames.reserve(0);
		frames_flip.reserve(0);*/

		currentFrame = 0;
		isPlaying = true;
		flip = false;
		loop = true;
		
		ColRect.reserve(0);
		ColRect.resize(3);
		ColRectFlip.reserve(0);
		ColRectFlip.resize(3);
		vector<FloatRect> tempvec;
		tempvec.reserve(0);
		ColRect.push_back(tempvec);
		ColRectFlip.push_back(tempvec);
	}
	bool isFlip()
	{
		return flip;
	}
	void coutFloatRect(FloatRect R)
	{
		cout << R.left << " " << R.top << " " << R.width << " " << R.height << endl;
	}
	void tick(float time)
	{
		if (!isPlaying) return;

		currentFrame += speed * time;

		if (currentFrame > frames.size()) {
			currentFrame -= frames.size();
			if (!loop) { isPlaying = false; return; }
		}

		int i = currentFrame;
		//cout << "i = " << i << endl;
		//cout << "left = " << frames[i].left << endl;
		if (i < frames.size())
		{
			sprite.setTextureRect(frames[i]);
			if (!flip)
			{
				sprite.setOrigin(frames[currentFrame].width / 2, frames[currentFrame].height / 2);
			}
			if (flip) {
				sprite.setTextureRect(frames_flip[i]);
				//FloatRect boundss = sprite.getGlobalBounds();
				//fsprite.setOrigin(boundss);
				//sprite.setOrigin(frames_flip[currentFrame].width / 2, frames_flip[currentFrame].height / 2);
			}
		}

	}

};



class AnimationManager
{

public:
	std::string currentAnim;
	std::map<std::string, Animation> animList;

	AnimationManager()
	{}

	~AnimationManager()
	{
		animList.clear();
	}
	Sprite* getSprite()
	{
		return &(animList[currentAnim].sprite);
	}
	//ñîçäàíèå àíèìàöèé âðó÷íóþ
	void create(std::string name, Texture &texture, int x, int y, int w, int h, int count, float speed, int step = 0, bool Loop = true)
	{
		Animation a;
		a.speed = speed;
		a.loop = Loop;
		a.sprite.setTexture(texture);
		a.sprite.setOrigin(0, h);

		for (int i = 0; i < count; i++)
		{
			a.frames.push_back(IntRect(x + i*step, y, w, h));
			a.frames_flip.push_back(IntRect(x + i*step + w, y, -w, h));
		}
		animList[name] = a;
		currentAnim = name;
	}

	//çàãðóçêà èç ôàéëà XML
	void loadFromXML(std::string fileName, Texture* t)
	{

		TiXmlDocument animFile(fileName.c_str());

		if (animFile.LoadFile())
		{
			//cout << "Animation loaded" << endl;
		}

		TiXmlElement *head;
		head = animFile.FirstChildElement("sprites");

		TiXmlElement *animElement;
		animElement = head->FirstChildElement("animation");
		/*std::stringstream ss;
		ss << std::hex << (head->Attribute("transparentColor"));
		Uint32 colorkey;
		ss >> colorkey;
		Uint8 result[3];

		result[0] = (colorkey & 0x000000ff);
		result[1] = (colorkey & 0x0000ff00) >> 8;
		result[2] = (colorkey & 0x00ff0000) >> 16;

		sf::Color colorr(result[0], result[1], result[2], 255);
		//cout << colorkey << endl;
		Image img = t->copyToImage();

		img.createMaskFromColor(colorr);

		t->loadFromImage(img);
		*/
		while (animElement)
		{


			Animation anim;
			//anim.sprite.setTexture(t);
			currentAnim = animElement->Attribute("title");
			int delay = atoi(animElement->Attribute("delay"));
			anim.speed = (1.0 / delay)*0.25;
			anim.sprite.setTexture(*t);
			//cout << anim.sprite.getColor().toInteger() << endl;
			//anim.sprite.getColor().Transparent = colorr;
			TiXmlElement *cut;
			cut = animElement->FirstChildElement("cut");
			int i = 0;
			while (cut)
			{
				int x = atoi(cut->Attribute("x"));
				int y = atoi(cut->Attribute("y"));
				int w = atoi(cut->Attribute("w"));
				int h = atoi(cut->Attribute("h"));

				anim.frames.push_back(IntRect(x, y, w, h));
				auto R = anim.frames[i];
			
				anim.ColRect[cp::left].push_back(FloatRect(0, 0, R.width / 2, R.height));
				anim.ColRect[cp::up].push_back(FloatRect(0, 0, R.width, R.height / 2));
				anim.ColRect[cp::right].push_back(FloatRect(R.width, 0, -(R.width / 2), R.height));
				anim.ColRect[cp::down].push_back(FloatRect(0, R.height, R.width, -(R.width, R.height / 2)));
				anim.frames_flip.push_back(IntRect(x+w, y, -w, h));
				R = anim.frames_flip[i];
				anim.ColRectFlip[cp::left].push_back(FloatRect(0, 0, R.width / 2, R.height));
				anim.ColRectFlip[cp::up].push_back(FloatRect(0, 0, R.width, R.height / 2));
				anim.ColRectFlip[cp::right].push_back(FloatRect(R.width, 0, -(R.width / 2), R.height));
				anim.ColRectFlip[cp::down].push_back(FloatRect(0, R.height, R.width, -(R.width, R.height / 2)));
				i++;
				cut = cut->NextSiblingElement("cut");
			}

			anim.sprite.setOrigin(0, anim.frames[0].height);
			//anim.sprite.setTexture(t);
			animList[currentAnim] = anim;

			animElement = animElement->NextSiblingElement("animation");
			
			//cout << "Col_left: ";
			/*coutFloatRect(anim.Col_left);
			cout << "Col_up: ";
			coutFloatRect(anim.Col_up);
			cout << "Col_right: ";
			coutFloatRect(anim.Col_right);
			cout << "Col_down: ";
			coutFloatRect(anim.Col_down);*/
			//anim.sprite.setTexture(t);
		}


	}

	void set(std::string name)
	{
		currentAnim = name;
		animList[currentAnim].flip = 0;
	}

	void draw(RenderWindow *window, int x, int y)
	{
		//cout << 2;
		animList[currentAnim].sprite.setPosition(x, y);
		//cout <<"x = "<< animList[currentAnim].sprite.getPosition().x << endl;
		//cout << "y = " << animList[currentAnim].sprite.getPosition().y << endl;
		
		window->draw(animList[currentAnim].sprite);
	}

	void flip(bool b = 1) { animList[currentAnim].flip = b; }

	void tick(float time) { animList[currentAnim].tick(time); }
	bool isFlip()
	{
		return animList[currentAnim].isFlip();
	}
	void pause() { animList[currentAnim].isPlaying = false; }

	void play() { animList[currentAnim].isPlaying = true; }
	
	void play(std::string name) { 
		currentAnim = name;
		animList[name].isPlaying = true;
		animList[name].currentFrame = 0;
	}

	bool isPlaying() { return animList[currentAnim].isPlaying; }

	bool isPlaying(string s) {
		if (s == currentAnim)
		{
			return true;
		}
		return false;
	}

	float getH() { return animList[currentAnim].frames[0].height; }

	float getW() { return animList[currentAnim].frames[0].width; }

};

#endif ANIMATION_H