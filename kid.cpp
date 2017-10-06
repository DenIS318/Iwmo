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
			kidentity->m_move(0, SpeedY);
			
		}
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
			Vector2f mtv;
			if (m_engine->m_math.sat_test(bl.sprite, *kidspr, &mtv))
			{
				kidspr->move(mtv);
				if (mtv.y <= 5)
				{
					grounded = true;
					//cout << "grounded" << endl;
					m_p = true;
					jumpcount = 0;
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
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (kidentity->state == jump)
			{

				if (vel.y < MAXVEL_Y)
				{
					vel.y = vel.y + GRAVITY;
				}
				else
				{
					vel.y = 0;
					kidentity->state = fall;
					kidentity->anim.play("fall");
				}
				cout << vel.y << endl;
				kidentity->m_move(0, -SpeedY + vel.y);
			}
			else
			{
				vel.y = 0;
			}
		}
		
		
}
void kid::MGetEvent(Event event)
{
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == Keyboard::LShift)
		{
			if (jumpcount <= 1)
			{

				if (jumpcount == 0)
				{
					jumps.setPosition(Vector3f(kidentity->GetX(), kidentity->GetY(), 0));
					jumps.play();

				}
				else if (jumpcount == 1)
				{
					doublejumps.setPosition(Vector3f(kidentity->GetX(), kidentity->GetY(), 0));
					doublejumps.play();

				}
				jumpcount++;
				grounded = false;
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
	kidentity->anim.currentAnim = "idle";
	SpeedX = 70;
	SpeedY = 70;
	m_engine = engine;
	map<string, SoundBuffer>* buflist = m_engine->buflist();
	jumps.setBuffer(buflist->at("kidjump"));
	doublejumps.setBuffer(buflist->at("kiddoublejump"));
	deaths.setBuffer(buflist->at("kiddeath"));
	fires.setBuffer(buflist->at("kidfire"));
}
