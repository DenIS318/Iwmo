#include "iwmoEffect.h"



iwmoEffect::iwmoEffect()
{
}


iwmoEffect::~iwmoEffect()
{
}
void iwmoEffect::play(string animname)
{
	anim.play(animname);
	Started = true;
}
void coutTwoi(int val1, int val2)
{
	cout << val1 << ", " << val2 << endl;
}
void coutTwof(float val1, float val2)
{
	cout << val1 << ", " << val2 << endl;
}
void iwmoEffect::tick(float t)
{
		auto curanim = anim.animList[anim.currentAnim];
		//coutTwof(curanim.currentFrame, curanim.frames.size());
		if (!curanim.isPlaying && !curanim.loop && DestroyAfterFinish && Started)
		{
			DestroyEffectEvent e;
			e.eventtype = Types::EventTypes::DestroyEffectEvent;
			iwmoEffect* ef = this;
			e.whichEffect = ef;
			//cout << e.eventtype << endl;
			__raise m_souc->OnCustomEvent(e);
		}
}