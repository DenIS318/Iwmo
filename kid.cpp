#include "kid.h"
using namespace tmx;
/*kid::kid()
{
}*/
iwmoEntity* kid::GetEntity()
{
	return kidentity;
}
void kid::control()
{
	
	grounded = false;
	colUP = false;
	colDOWN = false;
	colLEFT = false;
	colRIGHT = false;
	for each (Sprite* spr in m_engine->maptiles)
	{
		auto POS = GetPos();
		auto B = spr->getGlobalBounds();
		auto curAnim = anim.animList[anim.currentAnim];
		if (B.intersects(curAnim.Col_up))
		{
			colUP = true;
		}
		if (B.intersects(curAnim.Col_left))
		{
			colLEFT = true;
			setPos(
				Vector2f(
					spr->getPosition().x 
					+
					kidentity->anim.getSprite()->getOrigin().x
					, POS.y)
			);
		}
		if (B.intersects(curAnim.Col_right))
		{
			colRIGHT = true;
		}
		
		if (B.intersects(curAnim.Col_down))
		{
			cout << "COL DOWN" << endl;
			colDOWN = true;
			setPos(
				Vector2f(
					POS.x
					, spr->getPosition().y - anim.getSprite()->getOrigin().y)
			);
		}

	}

	if (colDOWN)
	{
		grounded = true;
	}
	else
	{
		if (kidentity->state != fall && kidentity->state != jump)
		{
			kidentity->anim.play("fall");
			kidentity->state = fall;
		}
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		kidentity->m_move(-SpeedX, 0);
		kidentity->anim.flip(true);
		if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump)
		{
			kidentity->anim.play("walk");
			kidentity->state = walk;
		}
		
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		kidentity->m_move(SpeedX, 0);
		kidentity->anim.flip(false);
		if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump)
		{
			kidentity->anim.play("walk");
			kidentity->state = walk;
		}


	}
	if(grounded)
	{ 
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
		kidentity->m_move(0, SpeedY);
	}
	/*
	for each (Sprite* block in m_engine->maptiles)
	{
		if (block->getGlobalBounds().intersects((anim.getSprite()->getGlobalBounds())))
		{
			col = true;
		}
		else
		{

		}
		if (col)
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
			//if (kidentity->state != jump && kidentity->state != fall)
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
	}
	if (!col)
	{
		if (kidentity->state != fall && kidentity->state != jump)
		{
			kidentity->anim.play("fall");
			kidentity->state = fall;
			kidentity->m_move(0, SpeedY);
		}
		return;

	}

	*/


		
	
	
	
				
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
	m_engine = engine;
	
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