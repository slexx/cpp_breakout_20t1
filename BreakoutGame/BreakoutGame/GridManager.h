#pragma once
#include <SFML/Graphics.hpp>


class GridCreate {
public:
	int posX = 0, posY = 0;
	int type = 0, maxType = 2;
	sf::RectangleShape rect;

	void Spawn(int x, int y) 
	{

		sf::RectangleShape newRect;
		rect = newRect;
		rect.setSize(sf::Vector2f(35.0f, 25.0f));
		rect.setFillColor(sf::Color::White);
		rect.setOutlineThickness(1);
		rect.setOutlineColor(sf::Color::Green);

		posX = x;
		posY = y;
		rect.setPosition(posX, posY);

	}

	void ChangeType()
	{
		if (type < maxType)
		{
			type++;
		}
		else
		{
			type = 0;
		}
	}

};