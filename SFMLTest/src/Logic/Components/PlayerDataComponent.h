#pragma once

#include "Logic/Component.h"

namespace Logic
{
	class RenderComponent;
}

namespace Logic
{
	class PlayerDataComponent : public Component
	{
	public:
		PlayerDataComponent(const std::string& componentType, Entity* owner, const int& initialLives, RenderComponent* renderComponentReference);
		virtual ~PlayerDataComponent() override;

		virtual void Update(const float& deltaTime);

		inline const int& GetPoints() const { return m_points; }
		inline void SetPoints(const int& points) { m_points = points; }
		
		inline const int& GetLives() const { return m_lives; }
		void SetLives(const int& lives);	


	private:

		RenderComponent * m_renderComponentReference;

		int m_lives;
		int m_points;

		bool m_invulnerable;
		float m_invulnerabilityTime;
	};
}
