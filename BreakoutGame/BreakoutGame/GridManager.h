#pragma once

class GridCreate {
public:
	int posX = 0, posY = 0;
	int type = 0, maxType = 2;
	sf::RectangleShape rect;

	void Spawn(int x, int y) 
	{

		sf::RectangleShape newRect;
		rect = newRect;
		rect.setSize(sf::Vector2f(32.0f, 32.0f));
		rect.setFillColor(sf::Color::White);
		rect.setOutlineThickness(1);

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