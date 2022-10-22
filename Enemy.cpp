#include "Enemy.h"
#include "Timer.h"

void destroy_enemy(Enemy* e, std::vector<Enemy*>& ve)
{
	ve.erase(std::find(ve.begin(), ve.end(), e));
	delete e;
}


Enemy::Enemy(sf::Vector2f position)
{
	Enemy::enemy.setFillColor(sf::Color::Black);
	Enemy::enemy.setOutlineColor(sf::Color::Red);
	Enemy::enemy.setOutlineThickness(1);
	Enemy::enemy.setPosition(position);
	Enemy::enemy.setSize(sf::Vector2f(50, 50));
	Enemy::health_bar.setSize(sf::Vector2f(50, 1));
	Enemy::health_bar.setPosition(position.x, position.y + 52);
	Enemy::health_bar.setFillColor(sf::Color(190, 190, 190));
	Enemy::health_bar.setOutlineColor(sf::Color(190, 190, 190));
	Enemy::health_bar.setOutlineThickness(1);
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
		sf::Vector2f bullet_pos_transformed(bullet_vec[i]->bullet.getPosition().x + bullet_vec[i]->get_sin_cos().y * 50, bullet_vec[i]->bullet.getPosition().y + bullet_vec[i]->get_sin_cos().x * 50);
		if (bullet_pos_transformed.x > Enemy::enemy.getPosition().x && bullet_pos_transformed.x < Enemy::enemy.getPosition().x + Enemy::enemy.getSize().x &&
			bullet_pos_transformed.y > Enemy::enemy.getPosition().y && bullet_pos_transformed.y < Enemy::enemy.getPosition().y + Enemy::enemy.getSize().y)
		{
			Enemy::health -= bullet_vec[i]->get_bullet_damage();
			Enemy::health_bar.setSize(sf::Vector2f(Enemy::health_bar.getSize().x - (bullet_vec[i]->get_bullet_damage()/2), 1));
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
