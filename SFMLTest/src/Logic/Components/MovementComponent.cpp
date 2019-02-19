#include "MovementComponent.h"

#include <SFML/System/Vector2.hpp>
#include "Util/Math.h"
#include "Logic/Entity.h"

namespace Logic
{
	MovementComponent::MovementComponent(const std::string& componentType, const float& movementSpeed) : 
		Component(componentType), 
		m_movementSpeed(movementSpeed)
	{
		m_isMoving = false;
	}

	MovementComponent::~MovementComponent()
	{
	}

	void Logic::MovementComponent::Initialize(Entity * owner)
	{
		Component::Initialize(owner);
	}

	void Logic::MovementComponent::Stop()
	{
	}

	void Logic::MovementComponent::Update(const float & deltaTime)
	{
		if (!m_isMoving)
			return;

		if (CurrentDestinationReached())
		{
			m_destinations.pop_front();
		}

		if (!m_destinations.empty())
		{
			m_movementDirection = m_destinations.front() - m_owner->getPosition();
			m_movementDirection = Util::Math::Normalize(m_movementDirection);

			m_owner->setPosition(m_owner->getPosition() + (m_movementDirection * m_movementSpeed * deltaTime));
		}
		else
		{
			m_isMoving = false;
		}
	}

	void MovementComponent::AddDestination(const sf::Vector2f & destination, const bool& overwrite)
	{
		if (overwrite)
		{
			m_destinations.clear();
			m_destinations.push_back(destination);			
		}
		else
		{
			m_destinations.push_back(destination);
		}		
		m_isMoving = true;
	}

	bool MovementComponent::CurrentDestinationReached() const
	{
		return Util::Math::Magnitude(m_destinations.front() - m_owner->getPosition()) < 1.0f;
	}
}