#pragma once
#include <SFML/System/Vector2.hpp>
#include "Logic/Component.h"

namespace Logic
{
	class MovementComponent;
	class PlayerDataComponent;
}

namespace Logic
{
	class EnemyComponent : public Component
	{
	public:
		EnemyComponent(const std::string& componentType, Entity* owner, const float& minDistanceToChase, const float& maxDistanceToChase,
			MovementComponent * movementComponentReference, PlayerDataComponent* playerComponentReference);
		virtual ~EnemyComponent() override;

		virtual void Update(const float& deltaTime);

	protected:
		MovementComponent * m_movementComponentReference;
		PlayerDataComponent * m_playerComponentReference;

		float m_minDistanceToFollowPlayer;
		float m_maxDistanceToFollowPlayer;		

		bool m_chasingPlayer;
		bool m_goingBack;

		sf::Vector2f m_initialPosition;
	};
}

