#include "kid.h"
using namespace tmx;
iwmoEntity* kid::GetEntity()
{
	return kidentity;
}
kid::kid()
{

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
		if (kidentity->state != jump)
		{
			if (kidentity->state == fall)
			{
				if (jumpcount == 0)
				{
					jumpcount = 1;
				}
			}
			kidentity->m_move(0, SpeedY);
			
		}
	}
}
void kid::control()
{
	
	m_p = false;
	Sprite* kidspr = &anim.animList[anim.currentAnim].sprite;
	Vector2f mtv;
	
		for (vector<Block>::iterator bl = m_engine->MapBlocks.begin(); bl != m_engine->MapBlocks.end(); bl++)	
		{
			
			if (!m_p)
			{
				if (m_engine->m_math.sat_test(*kidspr, bl->sprite, &mtv))
				{
					kidentity->setPos(kidentity->GetPos() + mtv);
					//kidspr->setPosition(kidentity->GetPos());
					//cout << mtv.x << endl;
					if (mtv.y <= bl->sprite.getTexture()->getSize().y / 2 && mtv.x < 1)
					{
						grounded = true;
						m_p = true;
						vel.y = 0;
						jumpcount = 0;
					
					}
				}
			}
		}
		if (!m_p)
		{
			grounded = false;
		}
	
		if (kidentity->state == jump && !grounded)
		{
			if (vel.y < 0)
			{
				vel.y += GRAVITY;
				kidentity->m_move(0, vel.y);
			}
			
			else
			{
				//мизерное замедление
				if (vel.y < SpeedY)
				{
					vel.y += GRAVITY * 2;
					if (vel.y > SpeedY)
					{
						vel.y = SpeedY;
					}
					kidentity->m_move(0, vel.y);
				}
				else
				{
					vel.y = 0;
					if (kidentity->state != fall)
					{
						kidentity->state = fall;
						kidentity->anim.play("fall");
					}
				}
			}
			
			

		}
		Col();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			kidentity->m_move(-SpeedX, 0);

			
			if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump && grounded)
			{
				kidentity->anim.play("walk");
				kidentity->state = walk;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			kidentity->m_move(SpeedX, 0);
		
			if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump && grounded)
			{
				kidentity->anim.play("walk");
				kidentity->state = walk;
			}
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (!grounded && kidentity->state != fall)
			{
				kidentity->state = fall;
				kidentity->anim.play("fall");
			}
			vel.y = 0;
		}
		
		
}
void kid::MGetEvent(Event event)
{
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::Left)
		{
		
				kidentity->anim.flip(true);
			
		}
		if (event.key.code == sf::Keyboard::Right)
		{
			
				kidentity->anim.flip(false);
			
		}
		if (event.key.code == Keyboard::LShift)
		{
			if (jumpcount <= 1)
			{

				if (jumpcount == 0)
				{
					jumps.setPosition(Vector3f(kidentity->GetX(), kidentity->GetY(), 0));
					jumps.play();
					vel.y = JumpPower;

				}
				else if (jumpcount == 1)
				{
					doublejumps.setPosition(Vector3f(kidentity->GetX(), kidentity->GetY(), 0));
					doublejumps.play();
					vel.y = (JumpPower) * 0.8;
					//cout << vel.y << endl;
				}
				jumpcount++;
				//grounded = false;
				if (kidentity->state != jump)
				{
					kidentity->anim.play("jump");
					kidentity->state = jump;

				}
			}
		}
	}
}
void kid::createKid(string filen, Texture* kidTexture, Vector2f position, Engine* engine)
{
	kidentity->initEntit(filen, kidTexture);
	kidentity->setPos(position);
	kidentity->anim.animList["idle"].loop = true;
	kidentity->anim.animList["walk"].loop = true;
	kidentity->anim.animList["slide"].loop = true;
	kidentity->anim.animList["fall"].loop = true;
	kidentity->anim.play("idle");
	kidentity->state = idle;
	SpeedX = 70;
	SpeedY = 100;
	m_engine = engine;
	map<string, SoundBuffer>* buflist = m_engine->buflist();
	jumps.setBuffer(buflist->at("kidjump"));
	doublejumps.setBuffer(buflist->at("kiddoublejump"));
	deaths.setBuffer(buflist->at("kiddeath"));
	fires.setBuffer(buflist->at("kidfire"));
	kidentity->anim.flip(true);
	kidentity->anim.flip(false);
}
