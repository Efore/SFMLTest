#include "Component.h"
#include "Entity.h"

namespace Logic
{
	Component::Component(const std::string & componentType, Entity* owner): m_componentType(componentType), m_owner(owner)
	{
	}

	Component::~Component()
	{
	}
	
	void Component::Update(const float& deltaTime)
	{
	}
}
