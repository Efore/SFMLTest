#include "Component.h"
#include "Entity.h"

namespace Logic
{
	Component::~Component()
	{
	}

	void Component::Initialize(Entity * owner)
	{
		m_owner = owner;
	}

	void Component::Stop()
	{
	}

	void Component::Update(const float& deltaTime)
	{
	}
}
