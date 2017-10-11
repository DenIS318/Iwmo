#include "kid.h"
using namespace tmx;
const Vector2f koctil(0,1.1);
iwmoEntity* kid::GetEntity()
{
	return kidentity;
}
kid::kid()
{

}
void kid::Col()
{
	if (Alive)
	{
		m_p = false;
		Sprite* kidspr = &anim.animList[anim.currentAnim].sprite;
		Vector2f mtv;
		for (auto bl = m_engine->MapBlocks.begin(); bl != m_engine->MapBlocks.end(); bl++)
		{

			if (!m_p)
			{
				auto bl2 = *bl._Ptr;
				float beforecol = kidentity->GetY();
				if (m_engine->m_math.sat_test(*kidspr, bl2->sprite, &mtv))
				{

					if (bl2->blocktype == Block::BlockType::solid)
					{
						kidentity->setPos(kidentity->GetPos() + mtv + koctil);
						if (mtv.y <= bl2->sprite.getTexture()->getSize().y / (-2) && mtv.x < 1)
						{
							grounded = true;
							m_p = true;
							vel.y = 0;
							lshiftcounter = 0;
							jumpcount = 0;
						}
					}
				}
			}
		}
		if (!m_p)
		{

			grounded = false;
		}
		if (JumpPassed)
		{
			JumpPassed = false;
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
				grounded = false;
				if (kidentity->state != jump)
				{

					kidentity->state = jump;

				}
			}
		}
		if (kidentity->state == jump)
		{
			//grounded = false;
			//�������� �������������!
			if (vel.y < 0)
			{
				vel.y += GRAVITY;
				kidentity->m_move(0, vel.y);
			}

			else
			{
				//�������� ����������
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

					}
				}
			}

		}
		if (grounded)
		{

			if (kidentity->state != walk && kidentity->state != idle) {
				kidentity->state = idle;


			}
			if (kidentity->state != jump && kidentity->state != fall)
			{
				if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
					!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
					!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
				{
					if (kidentity->state != idle)
					{
						kidentity->state = idle;
					}

				}
			}
		}
		if (!grounded)
		{
			if (kidentity->state != fall && kidentity->state != jump)
			{
				kidentity->state = fall;
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
}
void kid::Restart()
{
	m_engine->ResetBlocks();
	Alive = true;
	visible = true;
	state = unknown;
	setPos(LastSave);
}
void kid::death()
{
	Alive = false;
	state = EntityState::death;
	visible = false;
	iwmoEntity eff;
	eff.initEntit("resources/effects/poof.xml", kidDeathSheet);
}
void kid::CheckState()
{
	if (Alive)
	{
		switch (state)
		{
		case idle:
			if (anim.currentAnim != "idle")
			{
				anim.play("idle");
			}
			break;
		case walk:
			if (anim.currentAnim != "walk")
			{
				anim.play("walk");
			}
			break;
		case fall:

			if (anim.currentAnim != "fall")
			{
				anim.play("fall");
			}
			break;
		case jump:
			if (anim.currentAnim != "jump")
			{
				anim.play("jump");
			}
			break;
		case unknown:

			if (anim.currentAnim != "idle")
			{
				anim.play("idle");

			}
			break;
		case channel:
			//NA for kid
			//anim.play("channel");
			break;
		case slide:
			if (anim.currentAnim != "slide")
			{
				anim.play("slide");

			}
			break;
		case EntityState::death:
			//NA for kid
			//anim.play("death");
			break;
		default:
			state = unknown;
			if (anim.currentAnim != "idle")
			{
				anim.play("idle");
			}
		}
	}
}
void kid::control()
{
	Col();
	if (Alive)
	{
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			kidentity->m_move(-SpeedX, 0);


			if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump && grounded)
			{

				kidentity->state = walk;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			kidentity->m_move(SpeedX, 0);

			if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump && grounded)
			{

				kidentity->state = walk;
			}
		}
		if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
		{
			if (!grounded)
			{
				//�������� ���������� ������ ���� �� �������� �����
				if (vel.y < 0)
				{
					if (lshiftcounter < 2)
					{
						int val = (-GRAVITY *(-vel.y * 0.005));
						vel.y += val;
						kidentity->m_move(0, vel.y);
						kidentity->state = jump;
						lshiftcounter++;
					}
					else
					{
						int val2 = ((JumpPower * 0.05)*(vel.y*0.01)*7);
						vel.y += val2;
						kidentity->m_move(0, vel.y);
					}
				}
				else
				{

					state = fall;
				}
			}
		}
	}
	
	CheckState();
}
void kid::ProcessKeyboard(Event event)
{
	if (event.type == Event::KeyPressed)
	{
		if (event.key.code == sf::Keyboard::R)
		{
			Restart();
		}
	}
	if (Alive)
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
				JumpPassed = true;
			}
			if (event.key.code == Keyboard::Q)
			{
				death();
			}
		}
	}
}
void kid::MGetEvent(Event event)
{
	ProcessKeyboard(event);
}
void kid::createKid(string filen, Texture* kidTexture, Vector2f position, Engine* engine,CSource* eventsource)
{
	kidentity->initEntit(filen, kidTexture);
	kidentity->setPos(position);
	kidentity->anim.animList["idle"].loop = true;
	kidentity->anim.animList["walk"].loop = true;
	kidentity->anim.animList["slide"].loop = true;
	kidentity->anim.animList["fall"].loop = true;
	kidentity->GetEventSource(eventsource);
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
