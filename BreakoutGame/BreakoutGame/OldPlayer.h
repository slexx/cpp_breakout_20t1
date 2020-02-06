#pragma once
#pragma once
#include <SFML/Graphics.hpp>

using namespace std;

class OldPlayer {

public:
	Player(sf::Vector2f size) {
		player.setSize(size); //size is formatted Width,Height
		player.setFillColor(sf::Color::Green);
	}

	void SetDetector(sf::Vector2f size) {
		detector.setSize(size);
		detector.setFillColor(sf::Color::Red);
		detector.setPosition(player.getPosition().x + (player.getLocalBounds().height / 2), player.getPosition().y + player.getLocalBounds().width);
	}
	void drawTo(sf::RenderWindow& window) {
		window.draw(player);
		//window.draw(detector);
	}

	void move(sf::Vector2f distance) {
		player.move(distance);
	}

	void setPos(sf::Vector2f newPos) {
		player.setPosition(newPos);
	}

	int getY() {
		return player.getPosition().y;
	}
	int getX() {
		return player.getPosition().x + (player.getLocalBounds().width / 2);
	}




	sf::FloatRect getGlobalBounds() {
		return player.getGlobalBounds();
	}
private:
	sf::RectangleShape player;
	sf::RectangleShape detector;
};