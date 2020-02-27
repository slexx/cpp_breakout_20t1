#pragma once
#include <SFML/Graphics.hpp>


class GridCreate {
public:
	int posX = 0, posY = 0;
	int type = 0, maxType = 1;
	sf::RectangleShape rect;

	void Spawn(int x, int y) 
	{

		sf::RectangleShape newRect;
		rect = newRect;
		rect.setSize(sf::Vector2f(60.0f, 30.0f));
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineThickness(1);
		//rect.setOutlineColor(sf::Color::Green);

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

class BorderSetup {
public:
	sf::RectangleShape rect;

	void Setup(int yLength) {
		//std::cout << "Test" << std::endl;
		sf::RectangleShape border;
		rect = border;
		rect.setSize(sf::Vector2f(10.0f, yLength));
		rect.setPosition(1040, 1);
		rect.setFillColor(sf::Color::Black);
		rect.setOutlineThickness(1);
		rect.setOutlineColor(sf::Color::White);
	}

	int getX()
	{
		return rect.getPosition().x;
	}

	int getY()
	{
		return rect.getPosition().y;
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(rect);
	}


private:
};

class invisibleWalls {
public:
	sf::RectangleShape top;
	sf::RectangleShape bottom;
	sf::RectangleShape left;
	sf::RectangleShape right;
	
	void GameBorder(int w, int h) {
		

		top.setSize(sf::Vector2f(w, 1));
		top.setPosition(0, 0);
		top.setFillColor(sf::Color::Black);
		bottom.setSize(sf::Vector2f(w, 1));
		bottom.setPosition(sf::Vector2f(0, h - 1));
		bottom.setFillColor(sf::Color::Black);
		left.setSize(sf::Vector2f(1, h));
		left.setPosition(sf::Vector2f(0, 0));
		left.setFillColor(sf::Color::Black);
		right.setSize(sf::Vector2f(1, h));
		right.setPosition(sf::Vector2f(w - 1, 0));
		right.setFillColor(sf::Color::Black);
	}
private:
};