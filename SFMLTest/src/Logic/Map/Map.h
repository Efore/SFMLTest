#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <list>

namespace Logic
{
	class Entity;
}

namespace Logic
{
	/**
	This class represents the map in the game. Contains an array of booleans that express which tiles are trap and which are not.
	Also, contains an array of Entities, which are the drawable tiles itself.
	*/
	class Map
	{
	public:
		Map(const unsigned int& colums, const unsigned int& rows,const sf::Texture& texture);
		~Map();

		void Draw(const float& deltaTime) const;
		
		sf::Vector2f GetClosestValidPosition(const sf::Vector2f& origin, const sf::Vector2f& worldPosition) const;		

		inline const bool& GetValueAt(const unsigned int& column, const unsigned int& row) const { return m_mapNavigation[column + (row * m_mapRows)]; }
		const bool& GetValueAt(const sf::Vector2f& Position) const;

		inline Entity* GetTileAt(const unsigned int& column, const unsigned int& row) const { return m_tileInstances[column + (row * m_mapRows)]; }
		Entity* GetTileAt(const sf::Vector2f& Position) const;

		inline unsigned int GetColumnAtIndex(const int& index) const { return index % m_mapColums; }
		inline unsigned int GetRowAtIndex(const int& index) const { return index / m_mapColums; }

		inline const unsigned int& GetMapRows() const { return m_mapRows; }
		inline const unsigned int& GetMapColums() const { return m_mapColums; }

	private:
		Entity * CreateTileEntity(const unsigned int & column, const unsigned int & row, const bool& validPosition,const sf::Texture & texture);

	private:
		const unsigned int& m_mapRows;
		const unsigned int& m_mapColums;

		bool* m_mapNavigation;		
		Entity** m_tileInstances;
	};
}

