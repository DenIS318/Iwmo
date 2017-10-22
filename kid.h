#pragma once
#include "Engine.h"
#include "Animation.h"
#include <iostream>
#include "MyListener.h"
#include "iwmoEntity.h"
#include "Collision.h"
#include "iwmoConfig.h"
#include "Bullet.h"
#include "iwmoEffect.h"
using namespace Iwmo;
using namespace Iwmo::Events;
class kid : public iwmoEntity
{
public:
	~kid();
	kid();
	/*
	Creates a kid with given XML document filename, texture, position, engine and GameHandler*.
	*/
	void createKid(string filen, Texture* kidTexture, sf::Vector2f position, Engine* engine,CSource* eventsource,Texture* kidDeathSheet,View* camera);
	void control();
	Engine* m_engine;
	bool grounded = false;
	iwmoEntity* GetEntity();
	int jumpcount = 0;
	Sound jumps;
	Sound doublejumps;
	Sound deaths;
	Sound fires;
	
	void MGetEvent(Event event);
	sf::Vector2f vel;
	int JumpPower = -260;
	void deleteentity();
	bool Alive = true;
	void death();
	bool JumpPassed = false;
	//bool IsMove = false;
	void Restart();
	sf::Vector2f LastSave = KidSpawn;
	unsigned int maxbullets = 4;
	unsigned int currentbullets = 0;
	void shoot();
	vector<Bullet*>Bulletlist;
	void tick(float time);
	sf::Vector2i bulletscale = sf::Vector2i(1,1);
private:
	View* m_camera;
	//sf::Vector2f LastPos;
	int lshiftcounter = 0;
	void ProcessKeyboard(Event event);
	//bool animchanged=false;
	void Col();
	void CheckState();
	bool m_p = false;
	Texture* m_deathsheet;
	Texture* m_texture;
	iwmoEntity* kidentity = iwmoEntity::MGetBase();
	iwmoEffect* effect = new iwmoEffect;
};