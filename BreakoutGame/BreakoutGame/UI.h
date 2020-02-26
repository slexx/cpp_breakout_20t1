#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <conio.h>

class UI 
{
public:
	
	sf::Text text;
	
	template <typename T>
	std::string toString(T arg)
	{
		std::ostringstream ss;
		ss < arg;
		return ss.str();
	}
	

	void DrawText(sf::RenderWindow& window,int chSize, sf::String input, sf::Vector2f pos)
	{
		sf::Font font;
		if (!font.loadFromFile("OpenSans-Regular.ttf"))
		{

		}
		sf::Text newText;
		text = newText;

		text.setFont(font);
		text.setString(input);
		text.setCharacterSize(chSize);
		text.setFillColor(sf::Color::White);
		text.setPosition(pos);
		window.draw(text);

	}

private:



};