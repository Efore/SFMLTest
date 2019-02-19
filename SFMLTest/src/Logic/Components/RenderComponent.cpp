#include "RenderComponent.h"

#include "Logic/GlobalParameters.h"
#include "Logic/Entity.h"

namespace Logic
{
	RenderComponent::RenderComponent(const std::string& componentType, sf::Texture* texture, const sf::IntRect& textureRect, const sf::Color& spriteColor) : 
		Component(componentType), m_textureRect(textureRect), m_texture(texture)
	{	
		m_sprite.setTexture(*m_texture);
		m_sprite.setTextureRect(m_textureRect);
		m_sprite.setOrigin(m_textureRect.width * 0.5f, m_textureRect.height * 0.5f);
		m_sprite.setColor(spriteColor);

		m_isFlashing = false;
		m_flashingTime = 0.0f;
	}

	RenderComponent::~RenderComponent()
	{
	}

	void RenderComponent::Initialize(Entity * owner)
	{
		Component::Initialize(owner);
		
	}

	void RenderComponent::Stop()
	{
	}

	void RenderComponent::Update(const float& deltaTime)
	{
		m_sprite.setPosition(m_owner->getPosition());

		if (m_isFlashing)
		{
			m_flashingTime -= deltaTime;
			if (m_flashingTime <= 0)
			{
				m_isFlashing = false;
			}
			else if(((int)(m_flashingTime / 0.1f) % 2 ) == 0)
			{
				GlobalParameters::GetMainWindow()->draw(m_sprite);
			}
		}
		else
		{
			GlobalParameters::GetMainWindow()->draw(m_sprite);
		}
	}

	void RenderComponent::StartFlashing(const float& flashTime)
	{
		m_flashingTime = flashTime;
		m_isFlashing = true;
	}
}
