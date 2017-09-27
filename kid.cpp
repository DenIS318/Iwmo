#include "kid.h"

Sprite kidsprite;
/*kid::kid()
{
}*/

void kid::control()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		kidentity->m_move(-SpeedX, 0);
		kidentity->anim.flip(true);
		if (kidentity->state != walk)
		{
			kidentity->anim.play("walk");
			kidentity->state = walk;
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		kidentity->m_move(SpeedX, 0);
		kidentity->anim.flip(false);
		if (kidentity->state != walk)
		{
			kidentity->anim.play("walk");
			kidentity->state = walk;
		}
		
		
	}
	if (kidentity->state != jump && kidentity->state != fall)
	{	
		if (
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
			!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
			)
		{
			//cout << 2 << endl;
			if (kidentity->state != idle)
			{
				kidentity->anim.play("idle");
				kidentity->state = idle;
			}

		}
	}
	//cout << kidentity->anim.currentAnim << endl;
}
void kid::createKid(string filen, Texture* kidTexture, Vector2f position, Engine* engine)
{
	//kidentity = iwmoEntity();
	kidentity->initEntit(filen, kidTexture);

	kidentity->setPos(position);
	//TODO 3
	//kidentity->eng = new MyKidEngine();
	kidentity->anim.animList["idle"].loop = true;
	kidentity->anim.animList["walk"].loop = true;
	kidentity->anim.animList["slide"].loop = true;
	kidentity->anim.animList["fall"].loop = true;
	kidentity->anim.play("idle");
	kidentity->anim.currentAnim = "idle";
	SpeedX = 70;
	
}
void kid::MGetEvent(Event event)
{
/*	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		kidentity->m_move(-SpeedX, 0);
		kidentity->anim.flip(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		kidentity->m_move(SpeedX, 0);
		kidentity->anim.flip(false);
	}
		*/
	//cout << "lel" << endl;
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