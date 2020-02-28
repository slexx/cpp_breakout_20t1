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
#include "Ball.h"

#pragma region Variables
int WIN_W = 1200, WIN_H = 700, ground = WIN_H - 40;
int gridX = 1200, gridY = 600;
int lives = 5;
int score = 0;
const int gridLoopCount = 2000;
float speedMulti = 8.0f;
#pragma endregion


template <typename T>
std::string toString(T arg)
{
	std::ostringstream ss;
	ss < arg;
	return ss.str();
}

int main()
{
#pragma region Creation
	BorderSetup border;
	border.Setup(WIN_H);
	invisibleWalls walls;
	walls.GameBorder(border.rect.getPosition().x, WIN_H);
	UI interface;
	Player player({ 90.0f, 25.0f }, { sf::Color::White });
	player.setPos({ (border.getX() / 2.0f - player.getWidth()), (WIN_H - 50.0f) });

	Ball ball({ sf::Color::Green });
	ball.ballVelocity.x = rand() % 10;
	ball.ballVelocity.y = -5;

	ball.setStartPos({player.getPosForBall()});

	GridCreate grid[gridLoopCount];
	//grid.Spawn({ 10 }, {10});

	sf::RenderWindow window(sf::VideoMode(WIN_W, WIN_H), "SFML works!");
	window.setFramerateLimit(60);

	//Grid - Spawn 
	for (int x = 0; x < 16; x++) //ScreenW - BlockW / BlockW |<| to figure out how many fit
	{
		for (int y = 0; y < 10; y++)//ScreenH - BlockH / BlockH |<| to figure out how many fit
		{
			grid[x * 30 + y].Spawn(65 * x, 35 * y);
		}
	}

#pragma endregion	
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
#pragma region InputONCE
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

#pragma endregion

		}//WhileEnd

#pragma region BallCollision
		//BallStuff
		ball.ballShape.move(ball.ballVelocity);

		////Horizontal
		//if (ball.getPos().x > (border.getX() - 20)|| ball.getPos().x < 0)
		//{
		//	ball.Bounce(1);
		//}

		////Vertical1
		//if (ball.getPos().y < 0)
		//{
		//	ball.Bounce(0);
		//}
		////vertical2
		//if (ball.getPos().y > (WIN_H - 20))
		//{
		//	if (lives > 1)
		//	{
		//		lives -= 1;
		//		ball.Bounce(0);
		//	}
		//	else
		//	{
		//		window.close();
		//	}
		//}

		//COLLISION - HorizontalBarrier
		if (walls.left.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(1, walls.left, ball.ballShape);
		}
		if (walls.right.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(1, walls.right, ball.ballShape);
		}

		//COLLISION - VerticalBarrier
		if (walls.top.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0, walls.top, ball.ballShape);
			//PlaySound
		}
		if (walls.bottom.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0, walls.bottom, ball.ballShape);
			lives -= 1;
			//PlaySound
		}

		if (lives < 1)
		{
			window.close();			
		}

		//COLLISION - Player&Ball
		if (player.player.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()))
		{
			ball.Bounce(0, player.player, ball.ballShape);
		}

		//COLLISION - Brick&Ball
		for (int i = 0; i < 2000; i++)
		{
			if (grid[i].rect.getGlobalBounds().intersects(ball.ballShape.getGlobalBounds()) && grid[i].type != 1)
			{
				ball.Bounce(0, grid[i].rect, ball.ballShape);
				score += 1;
				ball.ballVelocity = ball.ballVelocity * 1.01f;
				grid[i].ChangeType();
				//If Score == max , end game
			}
		}
#pragma endregion
#pragma region InputRepeat

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

#pragma endregion
#pragma region Drawing
		window.clear();

		for (int i = 0; i < gridLoopCount; i++)
		{
			switch (grid[i].type)
			{
			case 0:
				grid[i].rect.setFillColor(sf::Color::White);
				grid[i].rect.setOutlineColor(sf::Color::White);
				break;
			case 1:
				grid[i].rect.setFillColor(sf::Color::Black);
				grid[i].rect.setOutlineColor(sf::Color::Black);
				break;
			}
				window.draw(grid[i].rect);
		}

		//DRAW HERE
		//window.draw(playerRect);
		interface.DrawText(window, 18, "Breakout Classic", { (border.rect.getPosition().x + 15.f), 5}); //Border is at 1025x
		interface.DrawText(window, 20, "Lives: " + std::to_string(lives) , { (border.rect.getPosition().x + 15.f), 25 });
		interface.DrawText(window, 20, "Score: " + std::to_string(score), { (border.rect.getPosition().x + 15.f), 45 });
		ball.drawTo(window);
		player.drawTo(window);
		border.drawTo(window);
		window.display();

#pragma endregion
	}

	return 0;
}