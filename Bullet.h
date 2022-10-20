#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
	sf::Clock clk;
	double m_sine;
	double m_cosine;
	double m_life_time;
public:
	Bullet(double, sf::Vector2f, double, double);
	void step(double);
	void draw_bullet(sf::RenderWindow&);
	void should_destroy(std::vector<Bullet*>&, double&);
	sf::RectangleShape bullet;
};

void destroy_bullet(Bullet*, std::vector<Bullet*>&);