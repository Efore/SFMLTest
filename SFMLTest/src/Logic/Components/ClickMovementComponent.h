#pragma once

#include "MovementComponent.h"

namespace Logic
{
	class Entity;
}

namespace Logic 
{
	class ClickMovementComponent : public MovementComponent
	{
	public:
		ClickMovementComponent(const std::string& componentType, const float& movementSpeed);
		virtual ~ClickMovementComponent();

		virtual void Initialize(Entity *owner);
		virtual void Stop();
		virtual void Update(const float& deltaTime);
	};
}



