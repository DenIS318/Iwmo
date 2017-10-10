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
	m_p = false;
	Sprite* kidspr = &anim.animList[anim.currentAnim].sprite;
	Vector2f mtv;
	/*auto an = anim.getSprite();
	auto ann = an->getLocalBounds();
	int f = anim.animList[anim.currentAnim].currentFrame;
	cout << "origin ";
	cout << an->getOrigin().x << ", " << an->getOrigin().y << endl;
	cout << "bounds ";
	cout << ann.width << ", " <<ann.height << endl;*/
	for (vector<Block>::iterator bl = m_engine->MapBlocks.begin(); bl != m_engine->MapBlocks.end(); bl++)
	{

		if (!m_p)
		{
			float beforecol = kidentity->GetY();
			if (m_engine->m_math.sat_test(*kidspr, bl->sprite, &mtv))
			{
				if (bl->blocktype == Block::BlockType::solid)
				{
					
					//cout << beforecol << endl;
					//cout << "kidpos " << kidentity->GetPos().y << endl;
					kidentity->setPos(kidentity->GetPos() + mtv + koctil);
					//kidspr->setPosition(kidentity->GetPos() + mtv);
					//kidspr->setPosition(kidentity->GetPos());
					//cout << "mtv " << mtv.x << ", " << mtv.y << endl;
					//cout << "kidposchanged " << kidentity->GetPos().y << endl;
					//cout << "kid " << kidentity->GetPos().y + k<< endl;
					//cout << "block "<< bl->sprite.getPosition().y << endl;
					//cout << kidentity->anim.currentAnim << ", " << kidentity->anim.animList[kidentity->anim.currentAnim].currentFrame << endl;

					//kidspr->setPosition(kidentity->GetPos());
					//cout << mtv.x << endl;
					if (mtv.y <= bl->sprite.getTexture()->getSize().y / (-2) && mtv.x < 1)
					{
						//kidentity->setPos(kidentity->GetPos() + Vector2f(0,-mtv.y));
						//cout << "collided up " << kidentity->GetX() << ", " << kidentity->GetY() << endl;
						//cout << "mtv is " << mtv.x << ", " << mtv.y << endl;
						grounded = true;
						m_p = true;
						vel.y = 0;
						lshiftcounter = 0;
						jumpcount = 0;
						//mtv = Vector2f(0, 0);
						
					}
				}
			}
		}
	}
	if (!m_p)
	{
	//		cout << "isnt ground " << kidentity->GetX() << ", " << kidentity->GetY() << endl;
		
		grounded = false;
	}
	else
	{
		//cout << "grounded " << kidentity->GetX() << ", " << kidentity->GetY() << endl;
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
		//скорость отрицательная!
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
			if (
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Right) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) &&
				!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)
				)
			{
				//cout << 2 << endl;
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
void kid::death()
{
	Alive = false;
	state = EntityState::death;
}
void kid::CheckState()
{
	switch (state)
	{
	case idle:
/*		if (anim.currentAnim == "fall")
		{
			auto curan = anim.animList[anim.currentAnim];
			auto idan = anim.animList["idle"];
			cout << "ALERT!" << endl;
			cout << curan.frames[curan.currentFrame].height << " and " << idan.frames[idan.currentFrame].height << endl;
			anim.play("idle");
			//kidentity->setPos(kidentity->GetPos() + Vector2f(0, -1));
			break;
		}*/
		/*if (anim.currentAnim == "fall")
		{
			cout << "ALERT FALL SWITCH" << endl;
			anim.play("idle");
			//kidentity->setPos(kidentity->GetPos() + Vector2f(0,2));
		}*/
		if (anim.currentAnim!= "idle")
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
	/*if (anim.currentAnim == "idle" && anim.currentAnim != "channel")
	{
		IsMove = true;
	}
	else
	{
		IsMove = false;
	}
	if (IsMove)
	{
		/*KidMoveEvent e;
		e.whichkid = this;
		__raise kidentity->m_souc->OnMove(e);
	}*/
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
				if (vel.y < 0)
				{
					if (lshiftcounter < 2)
					{
						vel.y += GRAVITY;
						kidentity->m_move(0, vel.y);
						cout << vel.y << endl;
						kidentity->state = jump;
						lshiftcounter++;
					}
					else
					{
						state = fall;
					}
				}
				
			}
			/*if (!grounded && kidentity->state != fall)
			{
				kidentity->state == fall;
			}
			if (!grounded && kidentity->state == fall)
			{
				if (lshiftcounter == 0)
				{
					lshiftcounter = 10;
				}
				else
				{
					lshiftcounter++;
				}
				if (m_engine->m_math.InRange(lshiftcounter,10,13))
				{
					cout << "INRANGE" << endl;
					vel.y += GRAVITY;
					kidentity->m_move(0, vel.y);
					cout << vel.y << endl;
				}
				else
				{
					vel.y = 0;
					state = fall;
					lshiftcounter = 0;
				}
				if (lshiftcounter > 15)
				{
					lshiftcounter = 0;
				}
			}*/
			
			
		}
	}
	
	CheckState();
}
void kid::ProcessKeyboard(Event event)
{
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
