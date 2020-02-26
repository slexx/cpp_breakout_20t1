//This file should contain everything relevant to the player object.
#include <SFML/Graphics.hpp>

class Player
{
public:
	sf::RectangleShape player;

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

	sf::Vector2f getPosForBall() {

		float x = player.getPosition().x;
		float y = player.getPosition().y - 50.f;
		
		return sf::Vector2f(x, y);
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
};
