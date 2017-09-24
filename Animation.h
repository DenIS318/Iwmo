#ifndef ANIMATION_H
#define ANIMATION_H

#include "tinyxml\tinyxml.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>

using namespace std;
using namespace sf;


class Animation
{
public:
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
			sprite.setOrigin(frames[currentFrame].width / 2, frames[currentFrame].height / 2);
			if (flip) {
				sprite.setTextureRect(frames_flip[i]);
				sprite.setOrigin(frames_flip[currentFrame].width / 2, frames_flip[currentFrame].height / 2);
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
			cout << "Animation loaded" << endl;
		}

		TiXmlElement *head;
		head = animFile.FirstChildElement("sprites");

		TiXmlElement *animElement;
		animElement = head->FirstChildElement("animation");
		std::stringstream ss;
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
			while (cut)
			{
				int x = atoi(cut->Attribute("x"));
				int y = atoi(cut->Attribute("y"));
				int w = atoi(cut->Attribute("w"));
				int h = atoi(cut->Attribute("h"));

				anim.frames.push_back(IntRect(x, y, w, h));
				anim.frames_flip.push_back(IntRect(x + w, y, -w, h));
				cut = cut->NextSiblingElement("cut");
			}

			anim.sprite.setOrigin(0, anim.frames[0].height);
			//anim.sprite.setTexture(t);
			animList[currentAnim] = anim;

			animElement = animElement->NextSiblingElement("animation");
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

	void pause() { animList[currentAnim].isPlaying = false; }

	void play() { animList[currentAnim].isPlaying = true; }

	void play(std::string name) { animList[name].isPlaying = true; }

	bool isPlaying() { return animList[currentAnim].isPlaying; }

	float getH() { return animList[currentAnim].frames[0].height; }

	float getW() { return animList[currentAnim].frames[0].width; }

};

#endif ANIMATION_H