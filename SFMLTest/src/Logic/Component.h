#pragma once
#include <string>

namespace Logic
{
	class Entity;
}

namespace Logic
{	
	/**
	This base clase represents the separated possible behaviours of a Entity
	*/
	class Component
	{
	public:
		Component(const std::string& componentType, Entity* owner);
		virtual ~Component();

		virtual void Update(const float& deltaTime);

		inline const std::string& GetType() const { return m_componentType; }
		inline Entity* GetOwner() const { return m_owner; }

	protected:
		Entity* m_owner;
		const std::string& m_componentType;
	};
}