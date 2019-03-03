#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/View.hpp>

namespace Logic
{
	class PlayerDataComponent;
}

namespace UI
{
	class UIManager
	{
	public:
		UIManager(const Logic::PlayerDataComponent& playerDataComponentReference);
		virtual ~UIManager();

		void Draw(const bool& gameFinished);

		inline const sf::View& GetUiView() const { return m_uiView; }

	private:
		const Logic::PlayerDataComponent& m_playerDataComponentReference;

		sf::Font m_livesFont;
		sf::Font m_pointsFont;
		sf::Font m_gameFinishedFont;

		sf::Text m_livesText;
		sf::Text m_pointsText;
		sf::Text m_gameFinishedText;

		sf::View m_uiView;
	};
}

