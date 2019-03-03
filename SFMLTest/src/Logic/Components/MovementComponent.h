#pragma once
#include <SFML/System/Vector2.hpp>
#include <string>
#include <list>

#include "Logic/Component.h"

namespace Logic
{
	class MovementComponent : public Component
	{
	public:
		MovementComponent(const std::string& componentType, Entity* owner, const float& movementSpeed) ;
		virtual ~MovementComponent() override;

		virtual void Update(const float& deltaTime);

		void AddDestination(const sf::Vector2f& destination, const bool& overwrite);

		inline const sf::Vector2f& GetMovementDirection() const { return m_movementDirection; }
		inline const bool& GetIsMoving() const { return m_isMoving; }

	protected:
		bool CurrentDestinationReached() const;

	protected:
		float m_movementSpeed;
		sf::Vector2f m_movementDirection;
		std::list<sf::Vector2f> m_destinations;
		bool m_isMoving;
	};
}

