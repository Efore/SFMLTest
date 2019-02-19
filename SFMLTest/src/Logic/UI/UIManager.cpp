#include "UIManager.h"
#include "Logic/GlobalParameters.h"

namespace UI
{
	UIManager::UIManager(PlayerDataComponent* playerDataComponentReference) : m_playerDataComponentReference(playerDataComponentReference)
	{
		m_livesFont.loadFromFile("../resources/arial.ttf");
		m_pointsFont.loadFromFile("../resources/arial.ttf");
		m_gameFinishedFont.loadFromFile("../resources/arial.ttf");

		m_livesText.setFont(m_livesFont);
		m_pointsText.setFont(m_pointsFont);
		m_gameFinishedText.setFont(m_gameFinishedFont);

		m_livesText.setCharacterSize(24); 								   
		m_livesText.setFillColor(sf::Color::Red);		
		m_livesText.setStyle(sf::Text::Bold);
		m_livesText.setPosition(sf::Vector2f(0.0f, 0.0f));

		m_pointsText.setCharacterSize(24);
		m_pointsText.setFillColor(sf::Color::Green);
		m_pointsText.setStyle(sf::Text::Bold | sf::Text::Italic);
		m_pointsText.setPosition(sf::Vector2f(0.0f, 30.0f));

		m_gameFinishedText.setCharacterSize(44);
		m_gameFinishedText.setFillColor(sf::Color::Blue);
		m_gameFinishedText.setStyle(sf::Text::Bold | sf::Text::Italic);
		m_gameFinishedText.setPosition(sf::Vector2f(Logic::GlobalParameters::GetWindowWidth() * 0.5f, Logic::GlobalParameters::GetWindowHeight() * 0.5f));

		m_uiView = sf::View(sf::FloatRect(0, 0, (float)Logic::GlobalParameters::GetWindowWidth(), (float)Logic::GlobalParameters::GetWindowHeight()));
	}


	UIManager::~UIManager()
	{
	}

	void UIManager::Draw(const bool& gameFinished)
	{
		if (!gameFinished)
		{
			m_livesText.setString("Lives: " + std::to_string(m_playerDataComponentReference->GetLives()));
			m_pointsText.setString("Points: " + std::to_string(m_playerDataComponentReference->GetPoints()));

			GlobalParameters::GetMainWindow()->draw(m_livesText);
			GlobalParameters::GetMainWindow()->draw(m_pointsText);
		}
		else
		{
			m_gameFinishedText.setString(m_playerDataComponentReference->GetOwner()->GetIsActive() ? "YOU WON!!" : "Game Over! Try again!");
			GlobalParameters::GetMainWindow()->draw(m_gameFinishedText);
		}
	}
}
