#ifndef ANIMATION_H
#define ANIMATION_H

#include "tinyxml\tinyxml.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <boost\math_fwd.hpp>
using namespace std;
using namespace sf;
enum ColPoint
{
	left,
	up,
	right,
	down
};
const float ColPointDivide = 10;
#define cp ColPoint

class Animation
{

public:

	/*FloatRect
		Col_up,
		Col_down,
		Col_right,
		Col_left
		;*/
	/*
	ПОИНТ
	АНИМАЦИЯ
	ФРЕЙМЫ
	*/
	vector<FloatRect> ColRect[4];
	vector<FloatRect> ColRectFlip[4];
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
		
		ColRect[0].reserve(0);
		ColRect[1].reserve(0);
		ColRect[2].reserve(0);
		ColRect[3].reserve(0);
		ColRectFlip[0].reserve(0);
		ColRectFlip[1].reserve(0);
		ColRectFlip[2].reserve(0);
		ColRectFlip[3].reserve(0);
		
	

		
		/*
		АНИМАЦИЯ
		ФРЕЙМЫ
		*/
		/*vector<vector<FloatRect>> tempvec;
		tempvec.reserve(0);
		ColRect[0].push_back(tempvec);
		ColRect[1].push_back(tempvec);
		ColRect[2].push_back(tempvec);
		ColRect[3].push_back(tempvec);
		ColRectFlip[0].push_back(tempvec);
		ColRectFlip[1].push_back(tempvec);
		ColRectFlip[2].push_back(tempvec);
		ColRectFlip[3].push_back(tempvec);*/
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
	void setPoints(IntRect R,FloatRect* leftRect,FloatRect* upRect,FloatRect* rightRect ,FloatRect* downRect)
	{
		
		
		*leftRect = FloatRect(
			0,
			R.height / ColPointDivide,
			R.width / 2,
			R.height - R.height / ColPointDivide
		);
		*upRect = FloatRect(R.width / ColPointDivide,
			0,
			R.width - R.width / ColPointDivide,
			R.height / 2);
		*rightRect = FloatRect(R.width / 2, R.height / ColPointDivide, R.width / 2, R.height - R.height / ColPointDivide);
		*downRect = FloatRect(R.width / ColPointDivide, R.height / 2, R.width - R.width / ColPointDivide, R.height / 2);
		
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
			int curf = anim.currentFrame;
			
			
			while (cut)
			{
				int x = atoi(cut->Attribute("x"));
				int y = atoi(cut->Attribute("y"));
				int w = atoi(cut->Attribute("w"));
				int h = atoi(cut->Attribute("h"));
				//
				anim.frames.push_back(IntRect(x, y, w, h));
				auto R = anim.frames[i];
				//
				FloatRect leftRect,leftRectf;
				FloatRect upRect,upRectf;
				FloatRect rightRect,rightRectf;
				FloatRect downRect, downRectf;
				//
				setPoints(R, &leftRect, &upRect, &rightRect, &downRect);
				//
				/*anim.ColRect[cp::left].push_back(leftRect);
				anim.ColRect[cp::up].push_back(upRect);
				anim.ColRect[cp::right].push_back(rightRect);
				anim.ColRect[cp::down].push_back(downRect);*/
				anim.ColRect[cp::left].push_back(leftRect);
				anim.ColRect[cp::up].push_back(upRect);
				anim.ColRect[cp::right].push_back(rightRect);
				anim.ColRect[cp::down].push_back(downRect);
				//
				anim.frames_flip.push_back(IntRect(x+w, y, -w, h));
				R = anim.frames_flip[i];
				setPoints(R, &leftRectf, &upRectf, &rightRectf, &downRectf);
				//
				/*anim.ColRectFlip[cp::left].push_back(leftRect);
				anim.ColRectFlip[cp::up].push_back(upRect);
				anim.ColRectFlip[cp::right].push_back(rightRect);
				anim.ColRectFlip[cp::down].push_back(downRect);*/
				//
				anim.ColRectFlip[cp::left].push_back(leftRectf);
				anim.ColRectFlip[cp::up].push_back(upRectf);
				anim.ColRectFlip[cp::right].push_back(rightRectf);
				anim.ColRectFlip[cp::down].push_back(downRectf);// массив фреймов
				//anim.coutFloatRect(downRect);
			/*	tmpvcframes[0].push_back(tmpvc[0]); // массив
				tmpvcframes[1].push_back(tmpvc[1]);
				tmpvcframes[2].push_back(tmpvc[2]);
				tmpvcframes[3].push_back(tmpvc[3]);
				tmpvcframesf[0].push_back(tmpvcf[0]);
				tmpvcframesf[1].push_back(tmpvcf[1]);
				tmpvcframesf[2].push_back(tmpvcf[2]);
				tmpvcframesf[3].push_back(tmpvcf[3]);*/
				
				i++;
				cut = cut->NextSiblingElement("cut");
			}

			anim.sprite.setOrigin(0, anim.frames[0].height);
			//anim.sprite.setTexture(t);
			animList[currentAnim] = anim;
			
			/*anim.ColRect[cp::left].push_back((tmpvc[cp::left]));
			anim.ColRect[cp::up].push_back((tmpvc[cp::up]));
			anim.ColRect[cp::right].push_back((tmpvc[cp::right]));
			anim.ColRect[cp::down].push_back((tmpvc[cp::down]));
			anim.ColRectFlip[cp::left].push_back((tmpvcf[cp::left]));
			anim.ColRectFlip[cp::up].push_back((tmpvcf[cp::up]));
			anim.ColRectFlip[cp::right].push_back((tmpvcf[cp::right]));
			anim.ColRectFlip[cp::down].push_back((tmpvcf[cp::down]));*/

			/*anim.ColRectFlip[cp::left][i][curf].push_back(tmpvcf[cp::left][curf]);
			anim.ColRectFlip[cp::up][i][curf].push_back(tmpvcf[cp::left][curf]);
			anim.ColRectFlip[cp::right][i][curf].push_back(tmpvcf[cp::left][curf]);
			anim.ColRectFlip[cp::down][i][curf].push_back(tmpvcf[cp::left][curf]);*/
			animList[currentAnim] = anim;
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
		//int i = animList[currentAnim].currentFrame;
		//FloatRect fr = animList[currentAnim].ColRect[cp::up][i];
		//static RectangleShape* r1 = new RectangleShape(Vector2f(fr.width, fr.height));
		//r1->setPosition(fr.left, fr.top);
		//r1->setFillColor(Color::Red);
		//r1->setOrigin(Vector2f(fr.width / 2, fr.height / 2));
		window->draw(animList[currentAnim].sprite);
		//x = r1->getPosition().x;
		//y = r1->getPosition().y;
		//window->draw(*r1);
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