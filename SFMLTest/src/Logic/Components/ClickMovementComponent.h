#pragma once
#include "MovementComponent.h"


namespace Logic 
{
	class ClickMovementComponent : public MovementComponent
	{
	public:
		ClickMovementComponent(const std::string& componentType, Entity *owner, const float& movementSpeed);
		virtual ~ClickMovementComponent() override;

		virtual void Update(const float& deltaTime);
	};
}



