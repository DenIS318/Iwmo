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
	for each (Block bl in m_engine->MapBlocks)
	{
		auto POS = GetPos();
		//auto B = bl.sprite.getLocalBounds();
		auto curAnim = anim.animList[anim.currentAnim].ColRect[anim.animList[anim.currentAnim].currentFrame];
		
		//RectangleShape colupshape(Vector2f(curAnim.Col_up.width,curAnim.Col_up.height));
		//colupshape.setPosition(curAnim.Col_up.left, curAnim.Col_up.top);
	//	m_engine->AddSprite(&colupshape, 0);
		Vector2f mtv;
		bool b = m_engine->m_math.sat_test(bl.sprite, *kidentity->anim.getSprite(), &mtv);
		//int;
		if (b)
		{
			Vector2u siz = bl.sprite.getTexture()->getSize();
			//cout << "intersect" << endl;
			//cout << mtv.x <<", "<<mtv.y << endl;
			
		}
		else
		{
		
		}
		if (curAnim[ColPoint::up].contains(mtv))
		{
			cout << "COLUP" << endl;
			colUP = true;
		}
		if (curAnim[ColPoint::left].contains(mtv))
		{
			cout << "COLLEFT" << endl;
			colLEFT = true;
			setPos(
				Vector2f(
					bl.sprite.getPosition().x
					+
					kidentity->anim.getSprite()->getOrigin().x
					, POS.y)
			);
		}
		if (curAnim[ColPoint::right].contains(mtv))
		{
			colRIGHT = true;
			cout << "COLRIGHT" << endl;
		}
		
		if (curAnim[ColPoint::down].contains(mtv))
		{
			cout << "COL DOWN" << endl;
			colDOWN = true;
			setPos(
				Vector2f(
					POS.x
					, bl.sprite.getPosition().y - anim.getSprite()->getOrigin().y)
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