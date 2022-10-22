#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include <vector>
#include <ctime>

class Player
{
	sf::Texture player_texture;
	double shot_delay;
	double shot_timer;
	short cash;
	short points;
	int inaccuracy;
	sf::Text text;
	sf::Font font;
	int damage;
public:
	Player();
	void move(const double&, const int&, const int&, const sf::Vector2i&);
	void draw_player(sf::RenderWindow&);
	void shoot(std::vector<Bullet*>&, const double&);
	void set_points(short);
	void set_inaccuracy(short);
	void set_cash(short);
	int get_cash();
	int get_inaccuracy();
	void set_shot_delay(double);
	float get_shot_delay();
	sf::Sprite player_sprite;
};