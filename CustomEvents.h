#pragma once
#include <iostream>
class iwmoEntity;
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
				KidShootEvent
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