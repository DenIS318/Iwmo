#pragma once
#include "IwmoEntity.h"
class iwmoEffect :
	public iwmoEntity
{
public:
	iwmoEffect();
	~iwmoEffect();
	void play(string animationname);
	bool DestroyAfterFinish = false;
	void tick(float t);
	bool Started = false;
	//TODO
};

