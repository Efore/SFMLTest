#pragma once

#include "RenderComponent.h"

namespace Logic
{
	class PlayerDataComponent : public Component
	{
	public:
		PlayerDataComponent(const std::string& componentType, const int& initialLives, RenderComponent* renderComponentReference);
		virtual ~PlayerDataComponent();

		virtual void Initialize(Entity *owner);
		virtual void Stop();
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
