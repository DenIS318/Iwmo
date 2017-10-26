#include "kid.h"
#define math m_engine->m_math
iwmoEntity* kid::GetEntity()
{
	return kidentity;
}
kid::kid()
{
	
}
kid::~kid()
{
}

void kid::Col()
{
	if (Alive)
	{
		m_p = false;
		Sprite* kidspr = &anim.animList[anim.currentAnim].sprite;
		auto curf = anim.animList[anim.currentAnim].currentFrame;
		vector< vector<Block*> >::iterator row;
		vector<Block*>::iterator col;
		#define vector2d m_engine->MapBlocks
		for (row = vector2d.begin(); row != vector2d.end(); row++) {
			for (col = row->begin(); col != row->end(); col++) {
				if (!m_p)
				{
					auto bl2 = *col._Ptr;
					sf::Vector2f mtv;
						if (m_engine->m_math.sat_test(*kidspr, bl2->sprite, &mtv))
						{
							if (bl2->killable)
							{
								death();
								m_p = true;
								return;
							}
							if (bl2->blocktype == Iwmo::BlockType::solid)
							{
								kidentity->setPos(kidentity->GetPos() + mtv);
								if (mtv.y <= bl2->sprite.getTexture()->getSize().y / (-2) && mtv.x == 0)
								{
									grounded = true;
									m_p = true;
									vel.y = 0;
									lshiftcounter = 0;
									jumpcount = 0;

								}
								else if(state != slide)
								{
									state = fall;
									grounded = false;
									vel.y = 0;
								}

							}
							coutVector2(mtv);
							if (bl2->blocktype == slidable)
							{
								jumpcount = 1;
								m_p = true;
								state = slide;
							}
							
						}
						else
							if (m_engine->m_math.onblock(bl2, kidentity->anim.getSprite()->getGlobalBounds()))
							{
								grounded = true;
								m_p = true;
								vel.y = 0;
								lshiftcounter = 0;
								jumpcount = 0;
								if (state != walk && state != idle)
								{
									state = idle;
								}
							}
				}
			}
		}
		if (!m_p)
		{
			grounded = false;
			if (state == slide)
			{
				if (state != jump && state != fall)
				{
					state = fall;
				}
			}
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
		if (state != slide)
		{
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
		else
		{
			//slide
			kidentity->m_move(0, SpeedY/2);
		}
	}
}
#undef vector2d
void kid::Restart()
{
	m_engine->ResetBlocks();
	Alive = true;
	visible = true;
	state = unknown;
	setPos(LastSave);
	if (effect != NULL)
	{
		auto effectlayers = *m_engine->getEffectLayers();
		for (unsigned int i = 0; i < effectlayers.size(); i++)
		{
			if (std::find(effectlayers[i].begin(), effectlayers[i].end(), effect) != effectlayers[i].end()) {
				//contains
				m_engine->RemoveEffect(effect);
			}
		}	
	}
	for (auto it = m_engine->allsounds.begin(); it != m_engine->allsounds.end(); ++it)
	{
		auto sound = *it._Ptr;
		sound->setVolume(100);
		sound->setPlayingOffset(sf::seconds(0));
		
	}
	for (auto it = m_engine->allmusic.begin(); it != m_engine->allmusic.end(); ++it)
	{
		auto sound = *it._Ptr;
		sound->setVolume(100);
		sound->setPlayingOffset(sf::seconds(0));

	}
	volCounter = 100;
	anim.flip(false);
	jumpcount = 0;
}
void kid::death()
{
	if (Alive)
	{
		Alive = false;
		state = EntityState::death;
		visible = false;
		effect = new iwmoEffect;
		effect->initEntit("resources/effects/poof2.xml", m_deathsheet, m_souc);
		effect->anim.animList["poof"].loop = false;
		effect->DestroyAfterFinish = true;
		effect->setPos(kidentity->GetPos());
		effect->play("poof");
		m_engine->AddEffect(effect, 1);
		deaths.setPosition(Vector3f(kidentity->GetX(), kidentity->GetY(), 0));
		deaths.play();

	}
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
		//cout << anim.currentAnim << endl;
	}
}
void kid::tick(float time)
{
	int x = GetX();
	int y = GetY();
	float posx,posy;
	/*
	ORIGINAL KAIYAN FORMULA
	X( "Player" ) - ( X( "Player" ) mod 800 ) + 400
	Y( "Player" ) - ( Y( "Player" ) mod 608 ) + 304
	MOD = %
	*/
	posx = x - (x % 800) + 400;
	posy = y - (y % 600) + 300;
	Vector2f vec(posx, posy);
	//coutVector2(vec);
	m_camera->setCenter(vec);
	//TODOFUCKING
	for (auto bull = Bulletlist.begin(); bull != Bulletlist.end();)
	{

		auto bullet = *bull._Ptr;
		if (bullet->finisheddistance < bullet->maxdistance)
		{
			vector< vector<Block*> >::iterator row;
			vector<Block*>::iterator col;
			#define vector2d m_engine->MapBlocks
			for (row = vector2d.begin(); row != vector2d.end(); row++) {
				for (col = row->begin(); col != row->end(); col++) {
					auto bl2 = *col._Ptr;
					if (bl2->blocktype == solid)
					{
						auto ptr = bullet->sprite();
						if (bl2->GetGlobalRect().intersects(ptr->getGlobalBounds()))
						{
							delete bullet;
							Bulletlist.erase(bull);
							currentbullets--;
							if (bull != Bulletlist.end())
							{
								++bull;
								continue;
							}
							else
							{
								break;
							}
						}
					}
				}
			}
			if (bull != Bulletlist.end())
			{
				++bull;
				
			}
			else
			{
				break;
			}
			#undef vector2d
			
		}
		else
		{
			
			delete bullet;
			Bulletlist.erase(bull);
			currentbullets--;
			if (bull != Bulletlist.end())
			{
				++bull;
				continue;
			}
			else
			{
				break;
			}
			
		}
		bullet->tick(m_engine->GetWindow(), time);
	}
//	jmpb:
	//muting sounds
	if (!Alive)
	{
		if (volCounter != 0)
		{
			//cout << volCounter << endl;
			volCounter -= 2.5;
			for (auto it = m_engine->allsounds.begin(); it != m_engine->allsounds.end(); ++it)
			{
				auto sound = *it._Ptr;
				if (volCounter >= 0)
				{
					sound->setVolume(volCounter);
				}


			}
			for (auto it = m_engine->allmusic.begin(); it != m_engine->allmusic.end(); ++it)
			{
				auto sound = *it._Ptr;
				if (volCounter >= 0)
				{
					sound->setVolume(volCounter);
				}
			}
			
			
		}
		
	}
}
void kid::deleteentity()
{
	for (auto bull = Bulletlist.begin(); bull != Bulletlist.end(); ++bull)
	{
		delete *bull;
	}
	Bulletlist.clear();
	kid::~kid();
	
}
void kid::control()
{
	if (Alive)
	{
		if (sf::Keyboard::isKeyPressed(Keyboard::Left))
		{
			if (!anim.isFlip())
			{
				anim.flip(true);
			}
		}
		if (sf::Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (anim.isFlip())
			{
				anim.flip(false);
			}
		}
		Col();
		if (m_engine->GetWindow()->hasFocus())
		{
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				if (state != slide)
				{
					kidentity->m_move(-SpeedX, 0);
				}
				else if (state == slide && anim.isFlip())
				{
					kidentity->m_move(-SpeedX, 0);
				}


				if (kidentity->state != walk && kidentity->state != fall && state != slide && kidentity->state != jump && grounded)
				{

					kidentity->state = walk;
				}

			}
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				if (state != slide)
				{
					kidentity->m_move(SpeedX, 0);
				}
				else if (state == slide && !anim.isFlip())
				{
					kidentity->m_move(SpeedX, 0);
				}
				

				if (kidentity->state != walk && kidentity->state != fall &&state != slide && kidentity->state != jump && grounded)
				{

					kidentity->state = walk;
				}
			}
			if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
			{
				if (!grounded)
				{
					//мизерное замедление вверху чтоб не грохался сразу
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
							if (vel.y > JumpPower*0.4)
							{
								//- потомучто там и так на +гравити постоянно, нам нужно немного поднять кида вверх
								vel.y += (-GRAVITY / 1.75);
								//cout << vel.y << endl;
								//мы не двигаем кида здесь!
							}
							else
							{
								int val2 = ((JumpPower * 0.05)*(vel.y*0.01) * 7);
								vel.y += val2;
								if (vel.y < 0)
								{
									kidentity->m_move(0, vel.y);
								}
							}

						}
					}
					else
					{
						if (state != slide)
						{
							state = fall;
						}
					}
				}
			}
		}
		CheckState();
	}
	
}
void kid::shoot()
{
	
	
		if (currentbullets < maxbullets)
		{
			currentbullets++;
			fires.setPosition(Vector3f(kidentity->GetX(), kidentity->GetY(), 0));
			//fires.setVolume(15);
			fires.play();
			auto b = kidentity->anim.getSprite()->getGlobalBounds();
			sf::Vector2i bulpoint;
			bool flipped;
			if (!kidentity->anim.isFlip())
			{
				bulpoint = sf::Vector2i(b.left + b.width, b.top + (b.height / 2));
				flipped = false;
			}
			else
			{
				bulpoint = sf::Vector2i(b.left, b.top + (b.height / 2));
				flipped = true;
			}
			if (state == slide)
			{
				if (flipped)
				{
					bulpoint = sf::Vector2i(b.left + b.width, b.top + (b.height / 2));
					flipped = false;
					goto jmp2;
				}
				if (!flipped)
				{
					bulpoint = sf::Vector2i(b.left, b.top + (b.height / 2));
					flipped = true;
					goto jmp2;
				}
			
			}
			if (state == jump)
			{
				bulpoint.y -= 2;
			}
		jmp2:
			Bullet* bul = new Bullet(bulletscale, m_texture, bulpoint);
			if (flipped)
			{
				bul->sprite()->setRotation(180);
			}
			Bulletlist.push_back(bul);
			KidShootEvent e;
			e.eventtype = Types::EventTypes::KidShootEvent;
			e.whichEntity = this;
			e.whichBullet = bul;
			__raise m_souc->OnCustomEvent(&e);
		}
	
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
			if (event.key.code == Keyboard::LShift)
			{
				JumpPassed = true;
			}
			if (event.key.code == Keyboard::Z)
			{
				shoot();
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
void kid::createKid(string filen, Texture* kidTexture, sf::Vector2f position, Engine* engine,CSource* eventsource,Texture*  kidDeathSheet,View* camera)
{
	m_camera = camera;
	m_texture = kidTexture;
	m_deathsheet = kidDeathSheet;
	kidentity->initEntit(filen, kidTexture,eventsource);
	kidentity->setPos(position);
	kidentity->anim.animList["idle"].loop = true;
	kidentity->anim.animList["walk"].loop = true;
	kidentity->anim.animList["slide"].loop = true;
	kidentity->anim.animList["fall"].loop = true;
	kidentity->state = idle;
	SpeedX = 70;
	SpeedY = 100;
	m_engine = engine;
	map<string, SoundBuffer>* buflist = m_engine->buflist();
	jumps.setBuffer(buflist->at("kidjump"));
	doublejumps.setBuffer(buflist->at("kiddoublejump"));
	deaths.setBuffer(buflist->at("kiddeath"));
	fires.setBuffer(buflist->at("kidfire"));
	m_engine->allsounds.push_back(&fires);
	m_engine->allsounds.push_back(&deaths);
	m_engine->allsounds.push_back(&jumps);
	m_engine->allsounds.push_back(&doublejumps);
	m_deathsheet = TextureManager::loadTexture("poof2.png", "resources/effects/poof2.png");
}
