#include "EnemyComponent.h"

#include "PlayerDataComponent.h"
#include "Logic/Entity.h"
#include "Logic/GlobalParameters.h"
#include "Util/Math.h"

namespace Logic
{
	EnemyComponent::EnemyComponent(const std::string & componentType, const float& minDistanceToChase, const float& maxDistanceToChase, MovementComponent * movementComponentReference)
		: Component(componentType), m_minDistanceToFollowPlayer(minDistanceToChase), m_maxDistanceToFollowPlayer(maxDistanceToChase), m_movementComponentReference(movementComponentReference)
	{
		m_chasingPlayer = false;
	}

	EnemyComponent::~EnemyComponent()
	{
	}

	void EnemyComponent::Initialize(Entity * owner)
	{
		Component::Initialize(owner);
		m_initialPosition = m_owner->getPosition();		
		m_playerComponentReference = static_cast<PlayerDataComponent*>(GlobalParameters::GetPlayerEntity()->GetComponentByType("PlayerDataComponent"));
	}

	void EnemyComponent::Stop()
	{
	}

	void EnemyComponent::Update(const float & deltaTime)
	{
		if (m_chasingPlayer)
		{
			//Moving towards the player
			m_movementComponentReference->AddDestination(m_playerComponentReference->GetOwner()->getPosition(),true);

			const float& distance = Util::Math::Magnitude(m_playerComponentReference->GetOwner()->getPosition() - m_owner->getPosition());

			//If it is too far, stops chasing it and go back to its initial position
			if (distance > m_maxDistanceToFollowPlayer)
			{
				m_chasingPlayer = false;
				m_movementComponentReference->AddDestination(m_initialPosition, true);
			}
			//If it is very close, the player gets damaged and the enemy dissapears
			else if (distance < GlobalParameters::GetSpriteSize())
			{
				m_playerComponentReference->SetLives(m_playerComponentReference->GetLives() - 1);
				m_playerComponentReference->SetPoints(m_playerComponentReference->GetPoints() + 100);
				m_owner->Stop();
			}
		}
		//If was not chasing the player but is now close enough to do it, starts chasing him
		else if (Util::Math::Magnitude(m_playerComponentReference->GetOwner()->getPosition() - m_owner->getPosition()) < m_minDistanceToFollowPlayer)
		{
			m_chasingPlayer = true;
		}	

		//Stepping over traps cause the enemy to dissapear
		if (!GlobalParameters::GetMap()->GetValueAt(m_owner->getPosition()))
		{
			m_playerComponentReference->SetPoints(m_playerComponentReference->GetPoints() + 100);
			m_owner->Stop();
		}
	}
}
