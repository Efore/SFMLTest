#include "PlayerDataComponent.h"
#include "Logic/Entity.h"

namespace Logic
{
	PlayerDataComponent::PlayerDataComponent(const std::string & componentType, const int & initialLives, RenderComponent* renderComponentReference) : 
		Component(componentType),
		m_lives(initialLives), 
		m_renderComponentReference(renderComponentReference)
	{
		m_points = 0;
		m_invulnerable = false;
		m_invulnerabilityTime = 0.0f;
	}

	PlayerDataComponent::~PlayerDataComponent()
	{
	}

	void PlayerDataComponent::Initialize(Entity * owner)
	{
		Component::Initialize(owner);		
	}

	void PlayerDataComponent::Stop()
	{
	}

	void PlayerDataComponent::Update(const float & deltaTime)
	{
		if (m_invulnerable)
		{
			m_invulnerabilityTime -= deltaTime;
			if (m_invulnerabilityTime < 0.0f)
				m_invulnerable = false;
		}
	}
	void PlayerDataComponent::SetLives(const int & lives)
	{
		m_lives = lives;

		if (lives == 0)
		{
			m_owner->Stop();
		}
		else
		{
			m_invulnerable = true;
			m_invulnerabilityTime = 3.0f;
			m_renderComponentReference->StartFlashing(m_invulnerabilityTime);
		}
	}
}