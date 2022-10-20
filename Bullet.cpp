#include "Bullet.h"
#include "Enemy.h"

void destroy_bullet(Bullet* b, std::vector<Bullet*>& vb)
{
	vb.erase(std::find(vb.begin(), vb.end(), b));
	delete b;
}

Bullet::Bullet(double rotation, sf::Vector2f position, double sine, double cosine) : m_sine{ sine }, m_cosine{ cosine }
{
	Bullet::bullet.setOrigin(0,5);
	Bullet::bullet.setSize(sf::Vector2f(50, 10));
	Bullet::bullet.setFillColor(sf::Color::Blue);
	Bullet::bullet.setRotation(rotation * 180.f / 3.141f);
	Bullet::bullet.setPosition(position);
	Bullet::clk.restart();
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