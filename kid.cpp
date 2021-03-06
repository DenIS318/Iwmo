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
void kid::AddWalls()
{
	vector< IwmoLayer >::iterator row;
	vector<Block*>::iterator col;
	for (row = m_engine->MapBlocks.begin(); row != m_engine->MapBlocks.end(); row++) {
		for (col = row->objects.begin(); col != row->objects.end(); col++) {
				auto bl2 = *col._Ptr;
				if (dir != None)
				{
					if (!bl2->fake)
					{
						if (bl2->blocktype == solid || bl2->blocktype == slidable)
						{
							//fix wall collision
							auto newpos = kidentity->GetPos();
							int x = newpos.x;
							int y = newpos.y;
							auto wid = kidentity->anim.getSprite()->getLocalBounds().width;
							auto hei = kidentity->anim.getSprite()->getLocalBounds().height;
							newpos.x = (x / wid) * wid;
							newpos.y = (y / hei) * hei;
							FloatRect rect(newpos.x - (wid / 2), newpos.y - hei, wid, hei);
							if (bl2->GetGlobalRect().intersects(rect))
							{
								if (bl2->blocktype == solid)
								{
									if (JumpThruPassed || JumpThruJumped)
									{
										if (!bl2->jumpthru)
										{

											tmpvc.push_back(bl2);

										}

									}
									else
									{
										tmpvc.push_back(bl2);
									}
								}
								else
								{
									bool b = false;
									if (sf::Keyboard::isKeyPressed(HotkeyMoveLeft) && bl2->flipped)
									{
										b = true;
									}
									else if (sf::Keyboard::isKeyPressed(HotkeyMoveRight) && !bl2->flipped)
									{
										b = true;
									}
									if (b)
									{
										jumpcount = 1;
										state = slide;
										m_ps = true;
									}
								}
							}
						}
					}
				}
		}
	}
	
}
void kid::Col()
{
	if (Alive)
	{
		updaterect();
		if (m_engine->debugger.Enabled)
		{
			m_engine->debugger.AddRectangle(kidrect, sf::Color::Yellow);
		}
		m_p = false;
		m_ps = false;
		CWJTB = false;
		Sprite* kidspr = &anim.animList[anim.currentAnim].sprite;
		auto curf = anim.animList[anim.currentAnim].currentFrame;
		vector< IwmoLayer >::iterator row;
		vector<Block*>::iterator col;
		AddWalls();
#define vector2d m_engine->MapBlocks
			for (row = vector2d.begin(); row != vector2d.end(); row++) {
				for (col = row->objects.begin(); col != row->objects.end(); col++) {
					if (!m_p)
					{
						auto bl2 = *col._Ptr;

						sf::Vector2f mtv;
						if (!bl2->fake)
						{

							if (m_engine->m_math.sat_test(kidrect, bl2->sprite.getGlobalBounds(), &mtv))
							{
								if (bl2 == JumpThruedBlock)
								{
									CWJTB = true;
								}
								if (bl2->killable)
								{
									death();
									m_p = true;
									return;
								}
								if (bl2->blocktype == Iwmo::BlockType::solid)
								{
									if (JumpThruPassed || JumpThruJumped)
									{
										if (!bl2->jumpthru)
										{
											kidentity->setPos(kidentity->GetPos() + mtv);
										}
										else if (bl2 != JumpThruedBlock && state == fall && mtv.y < -0.2)
										{
											grounded = true;
											state = idle;
											JumpThruPassed = false;
											JumpThruJumped = false;
											JumpThruedBlock = NULL;

											kidentity->setPos(kidentity->GetPos() + mtv);
											
										}
										
									}
									else
									{
										grounded = true;
										state = idle;
										JumpThruPassed = false;
										JumpThruJumped = false;
										JumpThruedBlock = NULL;

										kidentity->setPos(kidentity->GetPos() + mtv);
									}
									if (mtv.y <= bl2->sprite.getTexture()->getSize().y / (-2) && mtv.x == 0)
									{
										//if collides with down bound of block
										m_p = true;
										m_ps = false;
										if (!bl2->jumpthru)
										{
											//if (state != jump)
											{
												grounded = true;
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
									else if (state != slide &&  mtv.y > bl2->sprite.getTexture()->getSize().y / (-2))
									{
										//mm its a up bounds,yeah?
										
											if (!bl2->jumpthru)
											{
												state = fall;
												m_p = true;
												grounded = false;
												vel.y = 0;
											}
											else if (bl2 != JumpThruedBlock && state == fall && mtv.y < -0.2)
											{
												grounded = true;
												state = idle;
												JumpThruPassed = false;
												JumpThruJumped = false;
												JumpThruedBlock = NULL;
												
												kidentity->setPos(kidentity->GetPos() + mtv);
												
											}
										
									}
								}

							}
							else
								if (m_engine->m_math.onblock(bl2, kidrect))
								{
									if (bl2 == JumpThruedBlock)
									{
										CWJTB = true;
									}
									if(bl2->blocktype == Iwmo::BlockType::solid)
									{
										m_p = true;
										m_ps = false;
										if (JumpThruPassed || JumpThruJumped)
										{
											if (!bl2->jumpthru)
											{
												grounded = true;
												vel.y = 0;
												lshiftcounter = 0;
												jumpcount = 0;
												if (state != walk && state != idle)
												{
													state = idle;
												}
											}
											else
											{
												if (state==fall && bl2 != JumpThruedBlock)
												{
												
													grounded = true;
													state = idle;
													JumpThruPassed = false;
													JumpThruJumped = false;
													JumpThruedBlock = NULL;
													kidentity->setPos(kidentity->GetPos() + mtv);
													
												}
										}


										}
									else
									{
										grounded = true;
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
				}
			}
		}
		if (!m_p)
		{
			grounded = false;
			if (state == fall && !CWJTB) {
				JumpThruPassed = false;
				JumpThruedBlock = NULL;
				
				//JumpThruJumped = false;
			}
			if (state == slide && !m_ps)
			{
				if (state != jump && state != fall)
				{
					state = fall;
				}
			}
		}
		if (!tmpvc.empty())
		{
			//���� ������ ��� ����� ���� �����
			///DEBUG
			if (m_engine->debugger.Enabled)
			{
				for (auto it = tmpvc.begin(); it != tmpvc.end(); ++it)
				{
					
					auto bl2 = *it._Ptr;
					if (dir == WalkLeft && m_engine->m_math.hasBlockLeft(bl2, kidrect))
					{

						m_engine->debugger.AddRectangle(bl2->GetGlobalRect(), Color::Red);
						FloatRect brect = bl2->GetGlobalRect();
						brect.width = brect.width + 0.1;
						m_engine->debugger.AddRectangle(brect, Color::Green);
					}
					else if (dir == WalkRight && m_engine->m_math.hasBlockRight(bl2, kidrect))
					{

						m_engine->debugger.AddRectangle(bl2->GetGlobalRect(), Color::Blue);
						FloatRect brect = bl2->GetGlobalRect();
						brect.left = brect.left - 0.1;
						m_engine->debugger.AddRectangle(brect, Color::Green);
					}
					
				}
			}
			///ENDDEBUG
			tmpvc.clear();
		}
		else
		{
			//���� ����� � ������ ��� ����
			if (dir == WalkLeft)
			{
				kidentity->m_move(-SpeedX, 0);
			}
			else if (dir == WalkRight)
			{
				kidentity->m_move(SpeedX, 0);
			}
			if (kidentity->state != walk && kidentity->state != fall &&state != slide && kidentity->state != jump && grounded)
			{

				kidentity->state = walk;
			}
			dir = None;
		}
		if (JumpPassed)
		{
			JumpThruJumped = true;
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
		if (state != slide)
		{
			if (grounded)
			{
				JumpThruPassed = false;
				JumpThruJumped = false;
				JumpThruedBlock = NULL;
				if (kidentity->state != walk && kidentity->state != idle) {
					kidentity->state = idle;


				}
				if (kidentity->state != jump && kidentity->state != fall)
				{
					if (!sf::Keyboard::isKeyPressed(HotkeyMoveRight) &&
						!sf::Keyboard::isKeyPressed(HotkeyMoveLeft) &&
						!sf::Keyboard::isKeyPressed(HotkeyJump))
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
	for (auto it = m_engine->allmusic->begin(); it != m_engine->allmusic->end(); ++it)
	{
		auto sound = it._Ptr->_Myval.second;
		sound->setVolume(100);
		sound->setPlayingOffset(sf::seconds(0));
	}

	volCounter = 100;
	state = unknown;
	anim.play("idle");
	flip(false);
	updaterect();
	jumpcount = 0;
	Alive = true;
	visible = true;
}
void kid::death()
{
	if (Alive && state != unknown)
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
		if (yourkid)
		{
			if (mynetwork != NULL)
			{
				KidCheckStateEvent e;
				e.eventtype = Types::EventTypes::KidCheckStateEvent;
				e.whichKid = reinterpret_cast<kid*>(this);
				__raise m_souc->OnCustomEvent(&e);
			}
		}
		//cout << anim.currentAnim << endl;
	}
}
void kid::CheckBulletCols(Bullet* bullet,int i)
{
	vector< IwmoLayer >::iterator row;
	vector<Block*>::iterator col;

	for (row = m_engine->MapBlocks.begin(); row != m_engine->MapBlocks.end(); row++) {
		for (col = row->objects.begin(); col != row->objects.end(); col++) {
			auto bl2 = *col._Ptr;
			if (!bl2->fake)
			{
				if (bl2->blocktype == solid)
				{
					//���� ���� ��������
					auto ptr = bullet->sprite();
					if (bl2->GetGlobalRect().intersects(ptr->getGlobalBounds()))
					{
						m_engine->RemoveBullet(Bulletlist[i]);
						Bulletlist.erase(Bulletlist.begin() + i);
						currentbullets--;
						return;
					}
				}
			}
		}
	}
}
void kid::_setcam(View* _camera)
{
	m_camera = _camera;
}
void kid::tick(float time)
{
	if (ScreenCamera && m_camera != NULL)
	{
		int x = GetX();
		int y = GetY();
		float posx, posy;
		/*
		ORIGINAL KAIYAN FORMULA
		X( "Player" ) - ( X( "Player" ) mod 800 ) + 400
		Y( "Player" ) - ( Y( "Player" ) mod 608 ) + 304
		MOD = %
		*/
		posx = x - (x % 800) + 400;
		posy = y - (y % 608) + 304;
		Vector2f vec(posx, posy);
		//coutVector2(vec);
		m_camera->setCenter(vec);
	}
	int oldsize = Bulletlist.size();
	for (int i = 0; i < oldsize; i++)
	{
		if (Bulletlist[i] != NULL)
		{
			auto bullet = Bulletlist[i];
			if (bullet->finisheddistance < bullet->maxdistance)
			{
				//���� ���� �� �������� ������� ����������� ���������
				CheckBulletCols(bullet,i);

			}
			else
			{
				//���� ���� �������� ������� ���������
				m_engine->RemoveBullet(Bulletlist[i]);
				Bulletlist.erase(Bulletlist.begin() + i);
				currentbullets--;
			}
		}
	}
	//muting sounds
	if (!Alive)
	{
		if (volCounter != 0)
		{
			volCounter -= 2.5;
			for (auto it = m_engine->allsounds.begin(); it != m_engine->allsounds.end(); ++it)
			{
				auto sound = *it._Ptr;
				if (volCounter >= 0)
				{
					sound->setVolume(volCounter);
				}


			}
			for (auto it = m_engine->allmusic->begin(); it != m_engine->allmusic->end(); ++it)
			{
				auto sound = it._Ptr->_Myval.second;
				if (volCounter >= 0)
				{
					sound->setVolume(volCounter);
				}
			}
		}
	}
}
void kid::updaterect()
{
	//kid subrect
	FloatRect r = anim.getSprite()->getGlobalBounds();
	if (anim.isFlip())
	{
		//������� ��������
		r.left = r.left +3;
	}
	else
	{
		r.width = r.width -3;
	}
	kidrect = r;
}
void kid::deleteentity()
{
	for (auto bull = Bulletlist.begin(); bull != Bulletlist.end(); ++bull)
	{;
		m_engine->RemoveBullet(*bull._Ptr);
	}
	Bulletlist.clear();
	kid::~kid();
	
}
void kid::control()
{
	if (yourkid)
	{
		if (m_engine->ImGuifocus)
		{
			AllowControl2 = false;
		}
		else
		{
			AllowControl2 = true;
		}
		if (AllowControl&& AllowControl2)
		{
			if (Alive)
			{
				if (sf::Keyboard::isKeyPressed(HotkeyMoveLeft))
				{
					if (!anim.isFlip())
					{
						flip(true);
					}
				}
				if (sf::Keyboard::isKeyPressed(HotkeyMoveRight))
				{
					if (anim.isFlip())
					{
						flip(false);
					}
				}
			}
		}

		Col();
		if (AllowControl && AllowControl2)
		{
			if (m_engine->GetWindow()->hasFocus())
			{

				if (sf::Keyboard::isKeyPressed(HotkeyMoveLeft) && !sf::Keyboard::isKeyPressed(HotkeyMoveRight))
				{

					if (state != slide)
					{
						dir = WalkLeft;
					}
					else if (state == slide && anim.isFlip())
					{
						dir = WalkLeft;
					}




				}
				if (sf::Keyboard::isKeyPressed(HotkeyMoveRight) && !sf::Keyboard::isKeyPressed(HotkeyMoveLeft))
				{
					if (state != slide)
					{
						dir = WalkRight;
					}
					else if (state == slide && !anim.isFlip())
					{
						dir = WalkRight;
					}



				}
				if (!sf::Keyboard::isKeyPressed(HotkeyJump))
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
								if (vel.y > JumpPower*0.4)
								{
									//- ��������� ��� � ��� �� +������� ���������, ��� ����� ������� ������� ���� �����
									vel.y += (-GRAVITY / 1.75);
									//cout << vel.y << endl;
									//�� �� ������� ���� �����!
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
		}
	}
		//CheckState();
	
	
}
void kid::UpdateState()
{
	CheckState();
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
			static Vector2f SnapToGun(8, 1.5);
			if (!kidentity->anim.isFlip())
			{
				bulpoint = sf::Vector2i(b.left + b.width - SnapToGun.x, b.top + (b.height / 2) + SnapToGun.y);
				flipped = false;
			}
			else
			{
				bulpoint = sf::Vector2i(b.left + SnapToGun.x, b.top + (b.height / 2) + SnapToGun.y);
				flipped = true;
			}
			if (state == slide)
			{
				if (!flipped)
				{
					bulpoint = sf::Vector2i(b.left + b.width - SnapToGun.x, b.top + (b.height / 2) + SnapToGun.y);
					flipped = !flipped;
					goto jmp2;
				}
				if (flipped)
				{
					bulpoint = sf::Vector2i(b.left + SnapToGun.x, b.top + (b.height / 2) + SnapToGun.y);
					flipped = !flipped;
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
			m_engine->AddBullet(bul);
			KidShootEvent e;
			e.eventtype = Types::EventTypes::KidShootEvent;
			e.whichEntity = this;
			e.whichBullet = bul;
			__raise m_souc->OnCustomEvent(&e);
		}
	
	
}
Block* kid::GetBlockUnder(BlockType type)
{
	auto newrect = FloatRect(kidrect.left + (kidrect.width / 2 ) - 1, kidrect.top + kidrect.height, 2, 1.0);
	/*RectangleShape* r = new RectangleShape(Vector2f(kidrect.width, kidrect.height));
	r->setPosition(newrect.left, newrect.top);
	r->setOutlineColor(Color::Black);
	r->setOutlineThickness(2);
	m_engine->AddSprite(r, 5);*/
	auto blvec = m_engine->GetBlocksIntersectedAtRect(newrect);
	if (!blvec.empty())
	{
		for (auto it = blvec.begin(); it != blvec.end(); ++it)
		{
			auto val = *it._Ptr;
			if (val->blocktype == type)
			{
				return val;
			}
		}
	}
	return NULL;
}
void kid::ProcessKeyboard(Event event)
{
	if (AllowControl && AllowControl2)
	{
		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == HotkeyRestart)
			{
				Restart();
			}
		}
		if (Alive)
		{
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == HotkeyJump)
				{
					JumpPassed = true;
				}
				if (event.key.code == HotkeyShoot)
				{
					shoot();
				}
				if (event.key.code == HotkeyDeath)
				{
					death();
				}
				if (event.key.code == HotkeyJumpThru)
				{
					if (grounded)
					{
						JumpThruPassed = true;
						JumpThruedBlock = GetBlockUnder(solid);
						grounded = false;
						state = fall;
					}
				}
				if (event.key.code == HotkeyTeleport)
				{
					setPos(m_engine->mouseboundsshow.getPosition());
				}
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
	if (camera != NULL)
	{
		m_camera = camera;
	}
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
	jumps.setAttenuation(40);
	jumps.setMinDistance(300);
	fires.setAttenuation(50);
	fires.setMinDistance(200);
	doublejumps.setAttenuation(50);
	doublejumps.setMinDistance(200);
	m_deathsheet = TextureManager::loadTexture("poof2.png", "resources/effects/poof2.png");
}
