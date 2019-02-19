#include "Map.h"
#include "Logic/Entity.h"
#include "Logic/Components/RenderComponent.h"
#include "Logic/GlobalParameters.h"
#include <queue>

namespace Logic
{
	Map::Map(const unsigned int& rows, const unsigned int& colums, sf::Texture& texture ) : 
		m_mapRows(rows), 
		m_mapColums(colums)
	{
		const size_t mapSize = rows * colums;
		m_mapNavigation = new bool[mapSize];
		m_tileInstances = new Entity*[mapSize];

		//The first tile is free of traps
		m_mapNavigation[0] = true;
		m_tileInstances[0] = CreateTileEntity(GetColumnAtIndex(0), GetRowAtIndex(0), m_mapNavigation[0], texture);

		for (size_t i = 1; i < mapSize; ++i)
		{			
			m_mapNavigation[i] = (GetRowAtIndex(i) % 4 == 0 && GetColumnAtIndex(i) % 4 == 0) ? false : true;	
			m_tileInstances[i] = CreateTileEntity(GetColumnAtIndex(i), GetRowAtIndex(i), m_mapNavigation[i], texture);
		}
	}

	Map::~Map()
	{
		for (size_t i = 0; i < (m_mapColums * m_mapRows); ++i)
		{
			delete[] m_tileInstances[i];
		}
		delete[] m_tileInstances;
		delete[] m_mapNavigation;
	}

	void Map::Draw(const float& deltaTime) const
	{
		for (size_t i = 0; i < (m_mapColums * m_mapRows); ++i)
		{
			m_tileInstances[i]->Update(deltaTime);
		}
	}
	
	sf::Vector2f Map::GetClosestValidPosition(const sf::Vector2f & origin, const sf::Vector2f & destination) const
	{
		int destColumn = (int)(destination.x / GlobalParameters::GetSpriteSize());
		int destRow = (int)(destination.y / GlobalParameters::GetSpriteSize());

		sf::Vector2f closestValidPosition = destination;

		if (!GetValueAt(destColumn, destRow))
		{
			int directionColumn = ((int)(origin.x / GlobalParameters::GetSpriteSize())) - destColumn;
			int directionRow = ((int)(origin.y / GlobalParameters::GetSpriteSize())) - destRow;

			int closestValidColumn = destColumn + (directionColumn < 0 ? -1 : directionColumn == 0 ? 0 : 1);
			int closestValidRow = destRow + (directionRow < 0 ? -1 : directionRow == 0 ? 0 : 1);

			closestValidPosition = GetTileAt(closestValidColumn, closestValidRow)->getPosition();
		}

		return closestValidPosition;
	}

	const bool & Map::GetValueAt(const sf::Vector2f & position)
	{
		int destColumn = (int)(position.x / GlobalParameters::GetSpriteSize());
		int destRow = (int)(position.y / GlobalParameters::GetSpriteSize());

		return GetValueAt(destColumn, destRow);
	}

	Entity* Map::GetTileAt(const sf::Vector2f & position)
	{
		int destColumn = (int)(position.x / GlobalParameters::GetSpriteSize());
		int destRow = (int)(position.y / GlobalParameters::GetSpriteSize());

		return GetTileAt(destColumn, destRow);
	}
	
	Entity * Map::CreateTileEntity(const unsigned int & column, const unsigned int & row, const bool& validPosition, sf::Texture & texture)
	{
		Entity* tileEntity = new Entity("TileMap");

		RenderComponent* renderComponent = new RenderComponent("RenderComponent", &texture, sf::IntRect(validPosition ? 0 : 80, validPosition ? 0 : 80, 
			GlobalParameters::GetSpriteSize(), GlobalParameters::GetSpriteSize()),sf::Color::White);

		tileEntity->AddComponent(renderComponent);
		tileEntity->Initialize(sf::Vector2f((((float)GlobalParameters::GetSpriteSize() * 0.5f) + (float) GlobalParameters::GetSpriteSize() * column), 
			((float)GlobalParameters::GetSpriteSize() * 0.5f) + (float) GlobalParameters::GetSpriteSize() * row));

		return tileEntity;
	}
}