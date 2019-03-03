#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "Map/Map.h"

namespace Logic
{
	/**
	This static class acts as a easy access from every part of the code to the globaly important information
	*/
	class GlobalParameters
	{
	public:
		static unsigned int GetWindowWidth() { return m_windowWidth; }
		static unsigned int GetWindowHeight() { return m_windowHeight; }
		static unsigned int GetSpriteSize() { return m_spriteSize; }

		static sf::RenderWindow* GetMainWindow() { return m_mainWindow; }
		static void SetMainWindow(sf::RenderWindow *window) { m_mainWindow = window; }
		
		static const Map* GetMap() { return m_map; }
		static void SetMap(Map* map) { m_map = map; }

	private:
		static const unsigned int m_windowWidth = 1280;
		static const unsigned int m_windowHeight = 800;
		static const unsigned int m_spriteSize = 30;

		static sf::RenderWindow *m_mainWindow;
		static Map *m_map;
	};
}