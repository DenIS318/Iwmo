#ifndef ANIMATION_H
#define ANIMATION_H

#include "tinyxml\tinyxml.h"
#include <SFML/Graphics.hpp>
#include <iostream>
//#include <sstream>
//#include <boost\math_fwd.hpp>
using namespace std;
using namespace sf;
class Animation
{

public:
	std::vector<IntRect> frames;
	std::vector<IntRect> frames_flip;
	float currentFrame, speed;
	bool loop, flip, isPlaying;
	Sprite sprite;
	Animation()
	{

		currentFrame = 0;
		isPlaying = true;
		flip = false;
		loop = true;
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
			if (!loop) {
				isPlaying = false;
				return;
			}
		}

		int i = currentFrame;
		if (i < frames.size())
		{

			if (!flip)
			{
				sprite.setTextureRect(frames[i]);

			}
			if (flip) {
				sprite.setTextureRect(frames_flip[i]);

			}
			sprite.setOrigin(frames[i].width / 2, frames[i].height / 2);
		}
		auto R = sprite.getTextureRect();
		if (R == IntRect(0, 0, 0, 0)  || R == IntRect(0, 0, 174, 277))
		{
			cout << i << endl;
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
	int GetAnimNum(string m_anim)
	{
		int i = 0;
		map<string,Animation>::iterator it;
		for (it = animList.begin(); it != animList.end(); it++)
		{
			if (it->first == m_anim)
			{
				return i;
			}
			i++;
		}
	}
	Sprite* getSprite()
	{
		return &(animList[currentAnim].sprite);
	}
	//создание вручную
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

	//загрузка из XML (рекомендованно)
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
		
		while (animElement)
		{
			Animation anim;
			currentAnim = animElement->Attribute("title");
			int delay = atoi(animElement->Attribute("delay"));
			anim.speed = (1.0 / delay)*0.25;
			anim.sprite.setTexture(*t);
			TiXmlElement *cut;
			cut = animElement->FirstChildElement("cut");
			while (cut)
			{
				int x = atoi(cut->Attribute("x"));
				int y = atoi(cut->Attribute("y"));
				int w = atoi(cut->Attribute("w"));
				int h = atoi(cut->Attribute("h"));
				anim.frames.push_back(IntRect(x, y, w, h));
				anim.frames_flip.push_back(IntRect(x+w, y, -w, h));
				cut = cut->NextSiblingElement("cut");
				//anim.sprite.setOrigin(0, anim.frames[0].height);
				
			}
			animList[currentAnim] = anim;
			
			animElement = animElement->NextSiblingElement("animation");
		}
		
	}

	void set(std::string name)
	{
		currentAnim = name;
		
	}

	void draw(RenderWindow *window, float x, float y)
	{
		animList[currentAnim].sprite.setPosition(x, y);
		window->draw(animList[currentAnim].sprite);
	}

	void flip(bool b) { 
		typedef std::map<std::string, Animation>::iterator it_type;
		for (it_type iterator = animList.begin(); iterator != animList.end(); iterator++) {
			iterator->second.flip = b;
		}
		
	}

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