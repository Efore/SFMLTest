#include <SFML/Graphics.hpp>
#include <iostream>

#include "Logic/GlobalParameters.h"

#include "Logic/Entity.h"
#include "Logic/Components/RenderComponent.h"
#include "Logic/Components/ClickMovementComponent.h"
#include "Logic/Components/EnemyComponent.h"
#include "Logic/Components/PlayerDataComponent.h"

#include "Logic/UI/UIManager.h"
#include "Logic/Map/Map.h"

int main()
{
	//Window initialization
	sf::RenderWindow window(sf::VideoMode(Logic::GlobalParameters::GetWindowWidth(), Logic::GlobalParameters::GetWindowHeight()), "SFML TEST");
	Logic::GlobalParameters::SetMainWindow(&window);	

	//Game view initialization
	sf::View view(sf::FloatRect(0, 0, (float)Logic::GlobalParameters::GetWindowWidth(), (float)Logic::GlobalParameters::GetWindowHeight()));
	view.zoom(0.75f);

	sf::Clock clock;

	//Loading resources
	sf::Texture playerTexture;
	playerTexture.loadFromFile("../resources/player.png");
	sf::Texture mapTexture;
	mapTexture.loadFromFile("../resources/maptiles.png");

	//Creating map
	Logic::Map* map = new Logic::Map(64, 64, mapTexture);
	Logic::GlobalParameters::SetMap(map);

	//Creating the player and its components
	Logic::Entity* playerEntity = new Logic::Entity("Player");	

	Logic::RenderComponent* renderComponent = new Logic::RenderComponent("RenderComponent", playerEntity, playerTexture,
		sf::IntRect(0, 0, Logic::GlobalParameters::GetSpriteSize(), Logic::GlobalParameters::GetSpriteSize()), sf::Color::White);

	Logic::PlayerDataComponent* playerDataComponent = new Logic::PlayerDataComponent("PlayerDataComponent", playerEntity, 3, renderComponent);

	Logic::ClickMovementComponent* clickMovementcomponent = new Logic::ClickMovementComponent("ClickMovementComponent", playerEntity, 100.0f);
	
	//Adding components to the player
	playerEntity->AddComponent(renderComponent);
	playerEntity->AddComponent(clickMovementcomponent);
	playerEntity->AddComponent(playerDataComponent);
	playerEntity->Initialize(sf::Vector2f(Logic::GlobalParameters::GetSpriteSize() * 0.5f, Logic::GlobalParameters::GetSpriteSize() * 0.5f));


	//Creating enemies
	Logic::Entity** enemies = new Logic::Entity*[8];

	for (int i = 0; i < 8; ++i)
	{
		enemies[i] = new Logic::Entity("Enemy" + i);

		//Creating enemy components
		Logic::RenderComponent* enemyRenderComponent = new Logic::RenderComponent("RenderComponent", enemies[i] , playerTexture,
			sf::IntRect(0, 0, Logic::GlobalParameters::GetSpriteSize(), Logic::GlobalParameters::GetSpriteSize()), sf::Color::Red);

		Logic::MovementComponent* movementComponent = new Logic::MovementComponent("MovementComponent", enemies[i], 80.0f);

		Logic::EnemyComponent* enemyComponent = new Logic::EnemyComponent("EnemyComponent", enemies[i], Logic::GlobalParameters::GetSpriteSize() * 5.0f, 
			Logic::GlobalParameters::GetSpriteSize() * 7.0f, movementComponent, playerDataComponent);

		//Adding components to the enemies
		enemies[i]->AddComponent(enemyRenderComponent);
		enemies[i]->AddComponent(movementComponent);
		enemies[i]->AddComponent(enemyComponent);

		//Getting some valid initial positions for the enemies
		int row = 64 / 2 + i * (i % 3 == 0 ? -1 : 1);
		int col = 64 / 2 + i * (i % 3 == 0 ? -1 : 1);

		if (!map->GetValueAt(col, row))
		{
			row++;
			col--;
		}

		const sf::Vector2f& initialPosition = map->GetTileAt(col, row)->getPosition();

		enemies[i]->Initialize(initialPosition);
	}	

	//Creating UI
	UI::UIManager* uiManager = new UI::UIManager(*playerDataComponent);

	//Main loop
	while (window.isOpen())
	{
		sf::Time elapsed = clock.restart();
		
		sf::Event event;

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.setView(view);

		//Drawing the map tiles
		map->Draw(elapsed.asSeconds());
		
		//Drawing and updating the player
		playerEntity->Update(elapsed.asSeconds());				
		
		//Drawing and updating the enemies
		bool allEnemyDown = true;
		for (int i = 0; i < 8; ++i)
		{
			enemies[i]->Update(elapsed.asSeconds());							
			if (enemies[i]->GetIsActive())
				allEnemyDown = false;
		}		
		
		//Centering the camera on the player
		view.setCenter(playerEntity->getPosition());

		//Changing the view to the ui to draw it
		window.setView(uiManager->GetUiView());		
		uiManager->Draw(allEnemyDown || !playerEntity->GetIsActive());

		window.display();
	}

	//Cleaning up
	for (int i = 0; i < 8; ++i)
	{
		delete[] enemies[i];
	}
	delete[] enemies;

	delete uiManager;
	delete map;
	delete playerEntity;	
	
	return 0;
}

