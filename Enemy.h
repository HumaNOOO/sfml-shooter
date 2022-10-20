#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <vector>

class Enemy
{
public:
	Enemy(sf::Vector2f);
	void draw_enemy(sf::RenderWindow&);
	void should_die(std::vector<Bullet*>&, std::vector<Enemy*>&, int&, int&);
	void step(double, sf::Vector2f);
	sf::RectangleShape enemy;
	sf::RectangleShape health_bar;
	int health;
};

void destroy_enemy(Enemy*, std::vector<Enemy*>&);