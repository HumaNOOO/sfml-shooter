#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bullet
{
	float m_sine;
	float m_cosine;
	float m_life_time;
	short m_damage;
public:
	Bullet(float, sf::Vector2f, float, float, short);
	void step(double);
	void draw_bullet(sf::RenderWindow&);
	void should_destroy(std::vector<Bullet*>&, double&);
	sf::Vector2f get_sin_cos();
	int get_bullet_damage();
	sf::RectangleShape bullet;
};

void destroy_bullet(Bullet*, std::vector<Bullet*>&);