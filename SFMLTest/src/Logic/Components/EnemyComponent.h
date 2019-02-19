#pragma once
#include <SFML/System/Vector2.hpp>
#include "Logic/Components/MovementComponent.h"


namespace Logic
{
	class EnemyComponent : public Component
	{
	public:
		EnemyComponent(const std::string& componentType, const float& minDistanceToChase, const float& maxDistanceToChase, MovementComponent * movementComponentReference);
		virtual ~EnemyComponent();

		virtual void Initialize(Entity *owner);
		virtual void Stop();
		virtual void Update(const float& deltaTime);

	protected:
		MovementComponent * m_movementComponentReference;
		class PlayerDataComponent * m_playerComponentReference;

		float m_minDistanceToFollowPlayer;
		float m_maxDistanceToFollowPlayer;		

		bool m_chasingPlayer;
		bool m_goingBack;

		sf::Vector2f m_initialPosition;
	};
}

