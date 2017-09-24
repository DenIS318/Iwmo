#include "kid.h"

Sprite kidsprite;
/*kid::kid()
{
}*/


void kid::createKid(string filen, Texture* kidTexture, Vector2f position, Engine* engine)
{
	//kidentity = iwmoEntity();
	kidentity->initEntit(filen, kidTexture);

	kidentity->setPos(position);
	//TODO 3
	//kidentity->eng = new MyKidEngine();
	kidentity->anim.animList["idle"].loop = true;
	kidentity->anim.play("idle");
	kidentity->anim.currentAnim = "idle";
}
//TODO 4
/*void kid::SetHandler(GameHandler* h)
{
	kidentity->SettingHandler(h);
}*/



/*kid::~kid()
{
//	cout << "Kid destructor" << endl;
}*/