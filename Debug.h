#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>

class DebugInfo
{
	sf::Text text;
	std::string debug_str;
	sf::Font font;
public:
	DebugInfo();
	void update(int, double, double, double, sf::Vector2i, sf::Vector2f, int, int, int, int, bool&);
	void draw_debug(sf::RenderWindow&);
};