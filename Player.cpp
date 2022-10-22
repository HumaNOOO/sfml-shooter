#include "Player.h"

Player::Player()
{
	Player::player_texture.loadFromFile("player.png");
	Player::player_sprite.setTexture(player_texture);
	Player::player_sprite.setOrigin(64, 128);
	Player::player_sprite.setPosition(400, 400);
	Player::player_sprite.setScale(0.6, 0.6);
	Player::shot_delay = 0.2;
	Player::shot_timer = 0;
	Player::cash = 0;
	Player::points = 0;
	Player::inaccuracy = 100;
	Player::font.loadFromFile("font.ttf");
	Player::text.setFont(Player::font);
	Player::text.setScale(0.6, 0.6);
	Player::text.setString("points: " + std::to_string(Player::points).append("\ncash: " + Player::cash + '$'));
	Player::damage = 10;
	srand(time(0));
}

void Player::move(const double& dt, const int& WINDOW_WIDTH, const int& WINDOW_HEIGHT, const sf::Vector2i& mouse_pos)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		Player::player_sprite.move(-dt * 250, 0.f);
		if (Player::player_sprite.getPosition().x < 0 - 50) Player::player_sprite.setPosition(WINDOW_WIDTH, Player::player_sprite.getPosition().y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		Player::player_sprite.move(dt * 250, 0.f);
		if (Player::player_sprite.getPosition().x > WINDOW_WIDTH + 50) Player::player_sprite.setPosition(0 - 50, Player::player_sprite.getPosition().y);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		Player::player_sprite.move(0.f, -dt * 250);
		if (Player::player_sprite.getPosition().y < 0 - 50) Player::player_sprite.setPosition(Player::player_sprite.getPosition().x, WINDOW_HEIGHT - 50);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		Player::player_sprite.move(0.f, dt * 250);
		if (Player::player_sprite.getPosition().y > WINDOW_HEIGHT + 50) Player::player_sprite.setPosition(Player::player_sprite.getPosition().x, 0 - 50);
	}

	Player::text.setPosition(Player::player_sprite.getPosition().x - 65, Player::player_sprite.getPosition().y - 120);
	Player::text.setString("points: " + std::to_string(Player::points).append("\ncash: " + std::to_string(Player::cash) + '$'));
	Player::player_sprite.setRotation(atan2(mouse_pos.y - Player::player_sprite.getPosition().y, mouse_pos.x - Player::player_sprite.getPosition().x) * 180 / 3.14 + 90);
}

void Player::shoot(std::vector<Bullet*>& bullet_vec, const double& dt)
{
	Player::shot_timer -= dt;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && Player::shot_timer <= 0)
	{
		Player::shot_timer = Player::shot_delay;
		double radians = (Player::player_sprite.getRotation()-90) * 3.14 / 180;
		double radians_r = radians;
		if (Player::inaccuracy >= 1)
		{
			double res = (rand() % inaccuracy - inaccuracy / 2) / 100.0;
			radians_r += res;
		}
		bullet_vec.push_back(new Bullet(radians_r, sf::Vector2f(Player::player_sprite.getPosition().x + cos(radians) * 76, Player::player_sprite.getPosition().y + sin(radians) * 76), sin(radians_r), cos(radians_r), Player::damage));
	}
}

void Player::set_points(short amount)
{
	Player::points = amount;
}

void Player::set_inaccuracy(short amount)
{
	Player::inaccuracy = amount;
}

int Player::get_inaccuracy()
{
	return this->inaccuracy;
}

void Player::set_cash(short cash_amt)
{
	Player::cash = cash_amt;
}

int Player::get_cash()
{
	return this->cash;
}

void Player::set_shot_delay(double amount)
{
	Player::shot_delay = amount;
}

float Player::get_shot_delay()
{
	return this->shot_delay;
}

int Player::get_damage()
{
	return this->damage;
}

void Player::set_damage(short amount)
{
	Player::damage = amount;
}

void Player::draw_player(sf::RenderWindow& w)
{
	w.draw(Player::player_sprite);
	w.draw(Player::text);
}
