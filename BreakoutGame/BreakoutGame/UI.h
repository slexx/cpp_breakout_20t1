#pragma once
#include <SFML/Graphics.hpp>

class UI 
{
public:
	sf::Font font;
	sf::Text text;

	

	void DrawText(sf::RenderWindow& window,int chSize, sf::String input)
	{
		if (!font.loadFromFile("OpenSans-Regular"))
		{

		}
		sf::Text newText;
		text = newText;

		text.setFont(font);
		text.setString(input);
		text.setCharacterSize(chSize);
		text.setFillColor(sf::Color::White);
		text.setPosition(100, 100);
		window.draw(text);

	}

private:



};