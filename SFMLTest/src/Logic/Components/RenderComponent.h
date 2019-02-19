#pragma once
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics.hpp>

#include "Logic/Component.h"

namespace Logic
{
	class RenderComponent :
		public Component
	{
	public:
		RenderComponent(const std::string& componentType, sf::Texture* texture, const sf::IntRect& textureRect, const sf::Color& spriteColor);
		virtual ~RenderComponent();

		virtual void Initialize(Entity *owner);
		virtual void Stop();
		virtual void Update(const float& deltaTime);

		void StartFlashing(const float& flashTime);

	private:
		sf::Texture* m_texture;
		sf::IntRect m_textureRect;
		sf::Sprite m_sprite;

		float m_isFlashing;
		float m_flashingTime;
	};
}

