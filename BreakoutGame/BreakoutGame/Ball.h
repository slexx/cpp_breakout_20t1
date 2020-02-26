#pragma once
#include <SFML/Graphics.hpp>

class Ball
{
public:

	Ball(sf::Color color)
	{
		ballShape.setRadius(ballRadius);//Sorted Width || Height
		ballShape.setFillColor(color);
		ballShape.setOutlineThickness(1);
	}

	void Bounce(int dir) {


		switch (dir)
		{
		case 0:
			//Vertical
			ballVelocity.y = -ballVelocity.y;
			break;
		case 1:
			//Horizontal
			ballVelocity.x = -ballVelocity.x;
			break;

		case 2:
			//Both
			ballVelocity.y = -ballVelocity.y;
			ballVelocity.x = -ballVelocity.x;
			break;
		}
	}

	void setStartPos(sf::Vector2f pos) {
		ballShape.setPosition(pos);
	}

	sf::Vector2f getPos() {

		float x = ballShape.getPosition().x;
		float y = ballShape.getPosition().y;

		return sf::Vector2f(x, y);
	}

	sf::CircleShape ballShape;
	sf::Vector2f ballStartPos;
	sf::Vector2f ballVelocity;
	float ballRadius = 10.f;


	void drawTo(sf::RenderWindow& window)
	{
		window.draw(ballShape);
	}
};