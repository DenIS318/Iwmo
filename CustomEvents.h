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
				DestroyEffectEvent
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
		
	}
}