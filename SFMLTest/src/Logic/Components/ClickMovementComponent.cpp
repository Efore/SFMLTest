#include "ClickMovementComponent.h"
#include "Logic/GlobalParameters.h"

#include <SFML/Window/Mouse.hpp>
#include "Util/Math.h"

namespace Logic
{	
	ClickMovementComponent::ClickMovementComponent(const std::string & componentType, Entity *owner, const float& movementSpeed) :
		MovementComponent(componentType, owner, movementSpeed)
	{
	}

	ClickMovementComponent::~ClickMovementComponent()
	{
	}

	void ClickMovementComponent::Update(const float & deltaTime)
	{
		MovementComponent::Update(deltaTime);

		//Moving with the mouse
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			const sf::Vector2i& localPosition = sf::Mouse::getPosition(*GlobalParameters::GetMainWindow());
			const sf::Vector2f& worldPos = (*GlobalParameters::GetMainWindow()).mapPixelToCoords(localPosition);
			
			if (worldPos.x > 0.0f && worldPos.x < (GlobalParameters::GetMap()->GetMapColums() *  GlobalParameters::GetSpriteSize())
				&& worldPos.y > 0.0f && worldPos.y < (GlobalParameters::GetMap()->GetMapRows() *  GlobalParameters::GetSpriteSize()))
			{
				sf::Vector2f destination = GlobalParameters::GetMap()->GetClosestValidPosition(m_owner->getPosition(), worldPos);
				AddDestination(destination, true);
			}
		}

		//The player gets pushed away from trap tiles
		if (!GlobalParameters::GetMap()->GetValueAt(m_owner->getPosition()))
		{
			const sf::Vector2f& trapPosition = GlobalParameters::GetMap()->GetTileAt(m_owner->getPosition())->getPosition();
			const sf::Vector2f directionFromTrap = m_owner->getPosition() - trapPosition;
			const sf::Vector2f& newDestination = m_owner->getPosition() + Util::Math::Normalize(directionFromTrap) * 10.0f;
			AddDestination(newDestination, true);
		}
	}
}