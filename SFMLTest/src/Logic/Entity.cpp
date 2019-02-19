#include "Entity.h"

#include <functional>
#include "Component.h"

namespace Logic
{
	Entity::Entity(std::string name)
	{
		m_name = name;
	}

	Entity::~Entity()
	{
		DestroyComponents();
	}

	void Entity::Initialize(const sf::Vector2f& initialPosition)
	{
		setPosition(initialPosition.x, initialPosition.y);
		m_isActive = true;

		for (TComponentList::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->Initialize(this);
		}
	}

	void Entity::Stop()
	{
		for (TComponentList::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->Stop();
		}
		m_isActive = false;
	}

	void Entity::Update(const float& deltaTime)
	{
		if (!m_isActive)
			return;

		for (TComponentList::const_iterator it = m_components.begin(); it != m_components.end(); ++it)
		{
			(*it)->Update(deltaTime);
		}
	}

	void Entity::AddComponent(Component* component)
	{
		m_components.push_back(component);		
	}

	Component * Entity::GetComponentByType(const std::string & type) const
	{
		TComponentList::const_iterator it;

		std::function<bool(const Component* component)> componentTypeComparator =
			[&type](const Component* component) { return component->GetType() == type; };

		it = std::find_if(m_components.begin(), m_components.end(), componentTypeComparator);

		return (it != m_components.end()) ? (*it) : nullptr;
	}

	void Entity::DestroyComponents()
	{
		Component* c;
		while (!m_components.empty())
		{
			c = m_components.back();
			m_components.pop_back();
			delete c;
		}
	}
}