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
void coutkidcol(bool colLEFT, bool colRIGHT, bool colDOWN, bool colUP)
{
	if (colLEFT || colRIGHT || colDOWN || colUP)
	{
		cout << "------------------------" << endl;
		if (colLEFT)
			cout << "ColLEFT = " << checkbol(colLEFT) << endl;
		if (colRIGHT)
			cout << "ColRIGHT = " << checkbol(colRIGHT) << endl;
		if (colDOWN)
			cout << "ColDOWN = " << checkbol(colDOWN) << endl;
		if (colUP)
			cout << "ColUP = " << checkbol(colUP) << endl;
		cout << "------------------------" << endl;
	}
}
void coutFloatRect2(FloatRect R)
{
	cout << R.left << " " << R.top << " " << R.width << " " << R.height << endl;
}
void kid::control()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		kidentity->anim.flip(true);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		kidentity->anim.flip(false);
	}
	/*grounded = false;
	colUP = false;
	colDOWN = false;
	colLEFT = false;
	colRIGHT = false;*/
	static bool passed[4];

	passed[ColPoint::left] = false;
	passed[ColPoint::right] = false;
	passed[ColPoint::up] = false;
	passed[ColPoint::down] = false;
	colDOWN = false;
	colLEFT = false;
	colUP = false;
	colRIGHT = false;
	vector<FloatRect> curColRect[4];
	curColRect[0].reserve(0);
	curColRect[1].reserve(0);
	curColRect[2].reserve(0);
	curColRect[3].reserve(0);
	int animnum = anim.GetAnimNum(anim.currentAnim);
	//auto CurrentAnim = anim.animList[anim.currentAnim];
	//cout << animnum;
	int curf = anim.animList[anim.currentAnim].currentFrame;
	if (!anim.isFlip())
	{
		//int f = anim.animList[anim.currentAnim].currentFrame;
		curColRect[0] = anim.animList[anim.currentAnim].ColRect[0];
		curColRect[1] = anim.animList[anim.currentAnim].ColRect[1];
		curColRect[2] = anim.animList[anim.currentAnim].ColRect[2];
		curColRect[3] = anim.animList[anim.currentAnim].ColRect[3];
	}
	else
	{
		//cout << "FLIP" << endl;
		//int f = anim.animList[anim.currentAnim].currentFrame;
		curColRect[0] = anim.animList[anim.currentAnim].ColRectFlip[0];
		curColRect[1] = anim.animList[anim.currentAnim].ColRectFlip[1];
		curColRect[2] = anim.animList[anim.currentAnim].ColRectFlip[2];
		curColRect[3] = anim.animList[anim.currentAnim].ColRectFlip[3];
	}

	Sprite kidspr = *kidentity->anim.getSprite();
	
		for each (Block bl in m_engine->MapBlocks)
		{
			FloatRect blrect = bl.sprite.getLocalBounds();
			//auto B = bl.sprite.getLocalBounds();
			
			//RectangleShape colupshape(Vector2f(curAnim.Col_up.width,curAnim.Col_up.height));
			//colupshape.setPosition(curAnim.Col_up.left, curAnim.Col_up.top);
		//	m_engine->AddSprite(&colupshape, 0);
			Vector2f mtv;
			if (m_engine->m_math.sat_test(bl.sprite, kidspr, &mtv))
			{
				FloatRect mtvrect(mtv.x, mtv.y, blrect.width-mtv.x, blrect.height-mtv.y);
		//		coutMTV(mtv);
				if (!passed[ColPoint::up])
				{

					if (mtvrect.intersects(curColRect[ColPoint::up].at(curf)))
					{
						setPos(
							Vector2f(
								kidentity->GetX(), bl.sprite.getPosition().y - kidentity->anim.getSprite()->getOrigin().y
							));
						colUP = true;
						passed[ColPoint::up] = true;
						
					}
				}
				if (!passed[ColPoint::left])
				{
					if (mtvrect.intersects(curColRect[ColPoint::left].at(curf)))
					{
						//cout << "COLLEFT" << endl;
						colLEFT = true;
						setPos(
							Vector2f(
								bl.sprite.getPosition().x - kidentity->anim.getSprite()->getOrigin().x, kidentity->GetY()
							));
						passed[ColPoint::left] = true;
						/*cout << "MTVRECT = ";
						anim.animList[anim.currentAnim].coutFloatRect(mtvrect);
						cout << "CurColRect = ";
						anim.animList[anim.currentAnim].coutFloatRect(curColRect[cp::left].at(curf));*/
					}
				}
				if (!passed[ColPoint::right])
				{
					if (mtvrect.intersects(curColRect[ColPoint::right].at(curf)))
					{
						colRIGHT = true;
						setPos(
							Vector2f(
								bl.sprite.getPosition().x - kidentity->anim.getSprite()->getOrigin().x, kidentity->GetY()
							));
						passed[ColPoint::right] = true;
						//cout << "COLRIGHT" << endl;
						
					}
				}
				if (!passed[ColPoint::down])
				{
					if (mtvrect.intersects(curColRect[ColPoint::down].at(curf)))
					{
						//	cout << "COL DOWN" << endl;
						colDOWN = true;
						setPos(
							Vector2f(
								kidentity->GetX(), bl.sprite.getPosition().y - kidentity->anim.getSprite()->getOrigin().y
							));
						passed[ColPoint::down] = true;
						
					}
				}

			}
		}
		if (!passed[cp::left])
		{
			colLEFT = false;
		}
		if (!passed[cp::right])
		{
			colRIGHT = false;
		}
		if (!passed[cp::up])
		{
			colUP = false;
		}
		if (!passed[cp::down])
		{
			colDOWN = false;
			//cout << "not col down" << endl;
		}

		if (colDOWN)
		{
			grounded = true;
			//	cout << "grounded" << endl;
			if (kidentity->state != walk && kidentity->state != idle)
			{
				kidentity->state = idle;
				kidentity->anim.play("idle");

			}
		}
		if (!colDOWN)
		{
			grounded = false;
			if (kidentity->state != fall && kidentity->state != jump)
			{
				kidentity->anim.play("fall");
				kidentity->state = fall;
				//	cout << "fall" << endl;
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			kidentity->m_move(-SpeedX, 0);
			//kidentity->anim.flip(true);
			if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump)
			{
				kidentity->anim.play("walk");
				kidentity->state = walk;
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			kidentity->m_move(SpeedX, 0);
			//kidentity->anim.flip(false);
			if (kidentity->state != walk && kidentity->state != fall && kidentity->state != jump)
			{
				kidentity->anim.play("walk");
				kidentity->state = walk;
			}


		}
		if (grounded)
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
			//cout << "fall move" << endl;
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
	SpeedY = 35;
	m_engine = engine;
	
	
	
}
void kid::MGetEvent(Event event)
{
}