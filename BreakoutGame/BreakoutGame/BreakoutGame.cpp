// BreakoutGame.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <sstream>
#include <string>
#include <SFML/Graphics.hpp>
#include "GridManager.h"
#include "Player.h"
#include "UI.h"

int WIN_W = 1200, WIN_H = 700, ground = WIN_H - 40;
int gridX = 1200, gridY = 600;
int lives = 5;
const int gridLoopCount = 2000;
float speedMulti = 8.0f;

template <typename T>
std::string toString(T arg)
{
	std::ostringstream ss;
	ss < arg;
	return ss.str();
}

int main()
{
	BorderSetup border;
	border.Setup(WIN_H);

	UI interface;
	Player player({ 90.0f, 25.0f }, { sf::Color::White });
	player.setPos({(border.getX()/2.0f - player.getWidth()), (WIN_H - 50.0f)});


	GridCreate grid[gridLoopCount];
	//grid.Spawn({ 10 }, {10});

	sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "SFML works!");
	window.setFramerateLimit(60);

	//Grid - Spawn 
	for (int x = 1; x < 16; x++) //ScreenW - BlockW / BlockW |<| to figure out how many fit
	{
		for (int y = 0; y < 10; y++)//ScreenH - BlockH / BlockH |<| to figure out how many fit
		{
			grid[x * 30 + y].Spawn(60 * x, 30 * y);
		}
	}
	
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

		//Inputs
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player.getX() < (border.rect.getPosition().x - player.getWidth() - 10))//(WIN_W - player.getWidth()))
			{
				//std::cout << "Right Repsonse \n";
				//playerRect.move(1 * speedMulti, 0);
				player.Move({1 * speedMulti, 0});
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player.getX() > 7)
			{
				//std::cout << "Left Response \n";
				//playerRect.move(-1 * speedMulti, 0);
				player.Move({ -1 * speedMulti, 0 });
			}

			/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				BorderSetup border;
				border.Setup();
			}*/


		

		window.clear();

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
		interface.DrawText(window, 18, "Breakout Classic", {1040, 5});
		interface.DrawText(window, 20, "Lives: " , { (1040), 25 });
		player.drawTo(window);
		border.drawTo(window);
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