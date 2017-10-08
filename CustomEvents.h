#pragma once
#include <iostream>
class iwmoEntity;
namespace Iwmo
{
	namespace Events
	{
		namespace Types
		{
			enum EventTypes
			{
				unknown,
				EntityMoveEvent
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
	}
}