#pragma once

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>

namespace Logic
{
	class Component;
}

namespace Logic
{
	/**
	This class represents everything that takes room in the scene.
	Contains a list of components that will define its behaviour
	*/
	class Entity : public sf::Transformable
	{
	public:
		
		Entity(std::string name);
		~Entity();

		void Initialize(const sf::Vector2f& position);
		void Stop();
		void Update(const float& deltaTime);

		inline std::string GetName() const { return m_name; }
		inline bool GetIsActive() const { return m_isActive; }

		void AddComponent(Component* component);
		Component* GetComponentByType(const std::string& type) const;

	protected:

		void DestroyComponents();

	protected:
		typedef std::vector<Component*> TComponentList;

		TComponentList m_components;
		std::string m_name;
		bool m_isActive;
	};
}