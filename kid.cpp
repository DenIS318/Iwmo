#include "kid.h"
using namespace tmx;
#define cp ColPoint
/*kid::kid()
{
}*/

iwmoEntity* kid::GetEntity()
{
	return kidentity;
}
void coutMTV(Vector2f mtv)
{
	cout << "MTV = " << mtv.x << ", " << mtv.y << endl;
}
string checkbol(bool b)
{
	if (b)
	{
		return ("true");
	}
	else
	{
		return ("false");
	}
}
void coutFloatRect2(FloatRect R)
{
	cout << R.left << " " << R.top << " " << R.width << " " << R.height << endl;
}
void kid::Col()
{
	if (grounded)
	{

		if (kidentity->state != walk && kidentity->state != idle) {
			kidentity->state = idle;
			kidentity->anim.play("idle");

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
	}
	if (!grounded)
	{
		if (kidentity->state != fall && kidentity->state != jump)
		{
			kidentity->anim.play("fall");
			kidentity->state = fall;

			//	cout << "fall" << endl;
		}
		kidentity->m_move(0, SpeedY);
	}
}
void kid::control()
{
	static bool m_p = false;
	m_p = false;
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if (!kidentity->anim.isFlip())
		{
			kidentity->anim.flip(true);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (kidentity->anim.isFlip())
		{
			kidentity->anim.flip(false);
		}
	}
	Sprite* kidspr = kidentity->anim.getSprite();
	
		for each (Block bl in m_engine->MapBlocks)
		{
			FloatRect blrect = bl.sprite.getGlobalBounds();
			FloatRect kidrect = kidentity->anim.getSprite()->getGlobalBounds();
			Vector2f mtv;
			
			if (m_engine->m_math.sat_test(bl.sprite, *kidspr, &mtv))
			{
				kidspr->move(mtv);
				if (mtv.y <= 5)
				{
					grounded = true;
					//cout << "grounded" << endl;
					m_p = true;
				}
				

			}
			else
			{
				if (!m_p)
				{
					grounded = false;
				}
			}
		}
		Col();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			kidentity->m_move(-SpeedX, 0);

			//kidentity->anim.flip(true);
			if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump && grounded)
			{
				kidentity->anim.play("walk");
				kidentity->state = walk;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			kidentity->m_move(SpeedX, 0);
			//kidentity->anim.flip(false);
			if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump && grounded)
			{
				kidentity->anim.play("walk");
				kidentity->state = walk;
			}


		}

	
	 //delete [] passed;
	 //passed = nullptr;
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
	kidentity->state = idle;
	kidentity->anim.currentAnim = "idle";
	SpeedX = 70;
	SpeedY = 70;
	m_engine = engine;
	
	
	
}
void kid::MGetEvent(Event event)
{
}