// BreakoutGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GridManager.h"
#include "Player.h"

int WIN_W = 1200, WIN_H = 600, ground = WIN_H - 40;
int gridX = 1200, gridY = 600;
const int gridLoopCount = 2000;
float speedMulti = 4.0f;

int main()
{
	Player player({ 90.0f, 25.0f }, { sf::Color::White });
	player.setPos({100, 550});


	GridCreate grid[gridLoopCount];
	//grid.Spawn({ 10 }, {10});

	sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "SFML works!");
	window.setFramerateLimit(60);

	//Grid - Spawn (Haigen)
	for (int x = 10; x < 30; x++) //ScreenW - BlockW / BlockW
	{
		for (int y = 0; y < 10; y++)//ScreenH - BlockH / BlockH
		{
			grid[x * 30 + y].Spawn(30 * x, 30 * y);
		}
	}

	//sf::CircleShape shape(100.f);
	//shape.setFillColor(sf::Color::Green);
	
	
	while (window.isOpen())
	{
		//Event Handler
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::KeyPressed:
				//Do Stuff
				//cout << "Pressed: " << event.key.code << "\n"; //This code outputs the keyCode for any pressed button to help determine the numbers without needing to google.

				break;
			case sf::Event::MouseButtonReleased: 
					//cout << "Mouse Left Pressed";
					break;
			default:
				break;
			}
		
			//InputChecks

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			{
				window.close();
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				sf::Vector2i mousePos = sf::Mouse::getPosition(window);
				sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));

				for (int i = 0; i < gridLoopCount; i++)
				{
					if (grid[i].rect.getGlobalBounds().contains(mousePosF))
					{
						grid[i].ChangeType();
					}
				}
			}
		}//WhileEnd

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getX() < (WIN_W - player.getWidth()))
			{
				//std::cout << "Right Repsonse \n";
				//playerRect.move(1 * speedMulti, 0);
				player.Move({1 * speedMulti, 0});
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getX() > 5)
			{
				//std::cout << "Left Response \n";
				//playerRect.move(-1 * speedMulti, 0);
				player.Move({ -1 * speedMulti, 0 });
			}


		

		window.clear();

		/*for (int i = 0; i < gridLoopCount; i++)
		{
				window.draw(grid[i].rect);
		}*/

		for (int i = 0; i < gridLoopCount; i++)
		{
			switch (grid[i].type)
			{
			case 0:
				grid[i].rect.setFillColor(sf::Color::Black);
				grid[i].rect.setOutlineColor(sf::Color::Green);
				break;
			case 1:
				grid[i].rect.setFillColor(sf::Color::White);
				grid[i].rect.setOutlineColor(sf::Color::Black);
				break;
			}
				window.draw(grid[i].rect);
		}

		//DRAW HERE
		//window.draw(playerRect);
		player.drawTo(window);
		//window.draw(grid.rect);
		window.display();
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

	/* TEST CODE
	sf::RectangleShape playerRect;
	playerRect.setSize(sf::Vector2f(90.0f, 20.0f));
	playerRect.setFillColor(sf::Color::White);
	playerRect.setOutlineThickness(1);
	playerRect.setPosition(sf::Vector2f(100, 750));
	*/