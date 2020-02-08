//This file should contain everything relevant to the player object.
#include <SFML/Graphics.hpp>

class Player
{
public:
	Player(sf::Vector2f size, sf::Color color)
	{
		player.setSize(size);//Sorted Width || Height
		player.setFillColor(color);
		player.setOutlineThickness(1);
	}

	void drawTo(sf::RenderWindow& window)
	{
		window.draw(player);
	}

	void Move(sf::Vector2f distance)
	{
		player.move(distance);
	}

	void setPos(sf::Vector2f newPos)
	{
		player.setPosition(newPos);
	}

	int getWidth()
	{
		return player.getSize().x + 5;
	}

	int getX()
	{
		return player.getPosition().x;
	}

	int getY()
	{
		return player.getPosition().y;
	}


private:
	sf::RectangleShape player;
};
