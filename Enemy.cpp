#include "Enemy.h"

void destroy_enemy(Enemy* e, std::vector<Enemy*>& ve)
{
	ve.erase(std::find(ve.begin(), ve.end(), e));
	delete e;
}


Enemy::Enemy(sf::Vector2f position)
{
	Enemy::enemy.setFillColor(sf::Color::Red);
	Enemy::enemy.setPosition(position);
	Enemy::enemy.setSize(sf::Vector2f(50, 50));
	Enemy::health_bar.setSize(sf::Vector2f(50, 5));
	Enemy::health_bar.setPosition(position.x, position.y + 52);
	Enemy::health_bar.setFillColor(sf::Color(155,155,155));
	Enemy::health = 100;
}

void Enemy::draw_enemy(sf::RenderWindow& w)
{
	w.draw(Enemy::enemy);
	w.draw(Enemy::health_bar);
}

void Enemy::should_die(std::vector<Bullet*>& bullet_vec, std::vector<Enemy*>& ev, int& pts, int& cash)
{
	for (int i = 0; i < bullet_vec.size(); i++)
	{
		if (bullet_vec[i]->bullet.getPosition().x > Enemy::enemy.getPosition().x && bullet_vec[i]->bullet.getPosition().x < Enemy::enemy.getPosition().x + Enemy::enemy.getSize().x &&
			bullet_vec[i]->bullet.getPosition().y > Enemy::enemy.getPosition().y && bullet_vec[i]->bullet.getPosition().y < Enemy::enemy.getPosition().y + Enemy::enemy.getSize().y)
		{
			Enemy::health -= 20;
			Enemy::health_bar.setSize(sf::Vector2f(Enemy::health_bar.getSize().x - 10, 5));
			if (health <= 0)
			{
				destroy_enemy(this, ev);
				destroy_bullet(bullet_vec[i], bullet_vec);
				pts += 1;
				cash += 10;
				break;
			}
			else
			{
				destroy_bullet(bullet_vec[i], bullet_vec);
				break;
			}
		}
	}
}

void Enemy::step(double dt, sf::Vector2f player_pos)
{
	double angle = atan2(player_pos.y - enemy.getPosition().y, player_pos.x - enemy.getPosition().x);
	double sine = sin(angle);
	double cosine = cos(angle);
	Enemy::enemy.move(cosine * dt * 100.f, sine * dt * 100.f);
	Enemy::health_bar.move(cosine * dt * 100.f, sine * dt * 100.f);
}
