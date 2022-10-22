#include "Bullet.h"
#include "Enemy.h"

void destroy_bullet(Bullet* b, std::vector<Bullet*>& vb)
{
	vb.erase(std::find(vb.begin(), vb.end(), b));
	delete b;
}

Bullet::Bullet(float rotation, sf::Vector2f position, float sine, float cosine, short damage) : m_sine{ sine }, m_cosine{ cosine }, m_damage{ damage }
{
	Bullet::bullet.setOrigin(0,2);
	Bullet::bullet.setSize(sf::Vector2f(50, 4));
	Bullet::bullet.setFillColor(sf::Color::Blue);
	Bullet::bullet.setRotation(rotation * 180.f / 3.141f);
	Bullet::bullet.setPosition(position);
	Bullet::m_life_time = 2.5;
}

void Bullet::step(double dt)
{
	Bullet::bullet.move(m_cosine * dt * 1000, m_sine * dt * 1000);
}

void Bullet::draw_bullet(sf::RenderWindow& w)
{	
	w.draw(Bullet::bullet);
}

void Bullet::should_destroy(std::vector<Bullet*>& bullets_vec, double& delta_time)
{
	Bullet::m_life_time -= delta_time;
	if (Bullet::m_life_time <= 0) destroy_bullet(this, bullets_vec);
}

int Bullet::get_bullet_damage()
{
	return this->m_damage;
}

sf::Vector2f Bullet::get_sin_cos()
{
	return sf::Vector2f(this->m_sine, this->m_cosine);
}