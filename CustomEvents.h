#pragma once
#include <iostream>
class iwmoEntity;
class iwmoEffect;
class kid;
class Bullet;
namespace Iwmo
{
	namespace Events
	{
		namespace Types
		{
			enum EventTypes
			{
				unknown,
				EntityMoveEvent,
				EntityShootEvent,
				KidShootEvent,
				DestroyEffectEvent,
				KidChangePositionEvent,
				//Checking kid state and anim changing
				KidCheckStateEvent,
				PlayerFlipEvent
			};
		}
		class CustomEvent {
		public:
			Types::EventTypes eventtype = Types::EventTypes::unknown;
		};
		class EntityMoveEvent : public CustomEvent
		{
		public:
			iwmoEntity* whichEntity;
		};
		class DestroyEffectEvent : public CustomEvent
		{
		public:
			iwmoEffect* whichEffect;
		};
		class EntityShootEvent : public CustomEvent
		{
		public:
			iwmoEntity* whichEntity;
			Bullet* whichBullet;
		};
		class KidShootEvent : public EntityShootEvent
		{
		public:
		
			kid* whichKid;
		};
		class KidChangePositionEvent : public CustomEvent
		{
		public:

			kid* whichKid;
		};
		class KidCheckStateEvent : public CustomEvent
		{
		public:
			kid* whichKid;
		};
		class PlayerFlipEvent : public CustomEvent
		{
		public:
			iwmoEntity* whichEntity;
			bool flip;
		};
	}
}