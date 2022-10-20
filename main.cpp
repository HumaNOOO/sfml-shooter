#include <iostream>
#include <ctime>
#include "Enemy.h"
#include "Bullet.h"
#include "Debug.h"
#include <chrono>

class Timer
{
	std::chrono::time_point<std::chrono::system_clock> start;
	std::chrono::time_point<std::chrono::system_clock> stop;
public:
	Timer()
	{
		start = std::chrono::system_clock::now();
	}

	~Timer()
	{
		stop = std::chrono::system_clock::now();
		long long total = std::chrono::duration_cast<std::chrono::microseconds>(stop - start).count();
		std::cout << "time: " << total << " microseconds\n";
	}
};

int main()
{
	std::vector<Enemy*> enemy_vec;
	std::vector<Bullet*> bullets_vec;
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;

	srand(time(0));
	DebugInfo debug_info;
	sf::Vertex v1[2];
	sf::Vertex v2[2];
	sf::Vertex v3[2];
	bool pause = false;
	int pts{};
	bool debug = false;
	bool lock = false;
	int cash = 0;
	double last_dt{};
	int last_fps{};
	double fps_update{};
	double angle{};
	double sine{};
	double cosine{};
	int accuracy = 100;
	sf::Vector2i mp_last{};
	double distance_last{};
	sf::CircleShape point(3.f);
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2D Shooter", sf::Style::Close);
	window.setMouseCursorVisible(0);
	sf::CircleShape shape(50.f);
	shape.setPosition(300, 300);
	shape.setOrigin(50.f, 50.f);
	shape.setFillColor(sf::Color::Green);
	sf::Sprite cursor;
	sf::Texture texture;
	texture.loadFromFile("crosshair0.png");
	cursor.setTexture(texture);
	cursor.setOrigin(64, 64);
	cursor.setScale(0.5, 0.5);
	std::string str;

	sf::Font font;
	font.loadFromFile("font.ttf");
	sf::Text text;
	sf::Text pts_text;
	pts_text.setFont(font);
	pts_text.setCharacterSize(25);
	text.setFont(font);
	text.setScale(0.7, 0.7);

	sf::Clock clk;
	sf::Clock shot_clk;
	double delay = 0;
	double shot_clk_d = 0;
	double shot_delay = 0.2;
	double spawn_delay = 0;

	while (window.isOpen())
	{
		double dt = clk.restart().asSeconds();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				for (Bullet* b : bullets_vec) delete b;
				for (Enemy* e : enemy_vec) delete e;

				window.close();
				return 0;
			}

			if (event.type == sf::Event::KeyPressed)
			{
				if (event.key.code == sf::Keyboard::Escape) pause = pause ? false : true;

				if (event.key.code == sf::Keyboard::U && cash >= 50 && shot_delay > 0.02)
				{
					shot_delay -= 0.005;
					cash -= 50;
				}

				if (event.key.code == sf::Keyboard::Y && cash >= 50 && accuracy > 0)
				{
					accuracy -= 10;
					cash -= 50;
				}
			}
		}

		sf::Vector2i mp = sf::Mouse::getPosition(window);

		if (mp.y < 0) window.setMouseCursorVisible(1);
		else window.setMouseCursorVisible(0);

		if (!pause)
		{
			angle = atan2(mp.y - shape.getPosition().y, mp.x - shape.getPosition().x);
			sine = sin(angle);
			cosine = cos(angle);

			shot_clk_d -= dt;
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && shot_clk_d <= 0)
			{
				double angle_r;
				double sine_r;
				double cosine_r;

				accuracy > 0 ? angle_r = angle + (((rand() % accuracy) - (accuracy/2)) / 100.0) : angle_r = angle;

				sine_r = sin(angle_r);
				cosine_r = cos(angle_r);
				shot_clk_d = shot_delay;
				bullets_vec.insert(bullets_vec.begin(), new Bullet(angle_r, sf::Vector2f(shape.getPosition().x, shape.getPosition().y), sine_r, cosine_r));
			}

			spawn_delay -= dt;
			if (spawn_delay <= 0)
			{
				spawn_delay = 0.33;
				enemy_vec.insert(enemy_vec.begin(), new Enemy(sf::Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT)));
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				shape.move(-dt * 250, 0.f);
				if (shape.getPosition().x < 0-50) shape.setPosition(WINDOW_WIDTH, shape.getPosition().y);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				shape.move(dt * 250, 0.f);
				if (shape.getPosition().x > WINDOW_WIDTH+50) shape.setPosition(0-50, shape.getPosition().y);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				shape.move(0.f, -dt * 250);
				if (shape.getPosition().y < 0-50) shape.setPosition(shape.getPosition().x, WINDOW_HEIGHT-50);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				shape.move(0.f, dt * 250);
				if (shape.getPosition().y > WINDOW_HEIGHT+50) shape.setPosition(shape.getPosition().x, 0-50);
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F3) && !lock)
			{
				lock = true;
				debug = debug ? false : true;
			}
			else if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F3))
			{
				lock = false;
			}
		}

		str = std::string("points: " + std::to_string(pts) + '\n' + "cash: " + std::to_string(cash) + '$');
		pts_text.setString(str);
		pts_text.setPosition(shape.getPosition().x - 65, shape.getPosition().y - 120);

		debug_info.update(1/dt, dt * 1000, angle, sqrt(pow(mp.x - shape.getPosition().x, 2) + pow(mp.y - shape.getPosition().y, 2)), mp, shape.getPosition(),
			bullets_vec.size(), enemy_vec.size(), sine, cosine, sizeof(Bullet), sizeof(Enemy), pause);

		if (mp.y < 0)
		{
			window.setMouseCursorVisible(1);
		}
		else
		{
			window.setMouseCursorVisible(0);
		}
		cursor.setPosition(sf::Vector2f(mp.x, mp.y));
		window.clear();
		window.draw(shape);

		for (Enemy* e : enemy_vec)
		{
			if (std::find(enemy_vec.begin(), enemy_vec.end(), e) != enemy_vec.end())
			{
				e->draw_enemy(window);
				if (!pause)
				{
					e->step(dt, shape.getPosition());
					e->should_die(bullets_vec, enemy_vec, pts, cash);
				}
			}
		}

		for (Bullet* b : bullets_vec)
		{
			if (std::find(bullets_vec.begin(), bullets_vec.end(), b) != bullets_vec.end())
			{
				b->draw_bullet(window);
				if (!pause)
				{
					b->step(dt);
					b->should_destroy(bullets_vec, dt);
				}
			}
		}

		if (debug)
		{
			if (!pause)
			{
				v1[0].position = shape.getPosition();
				v1[1].position = sf::Vector2f(mp.x, shape.getPosition().y);

				v2[0].position = sf::Vector2f(mp.x, shape.getPosition().y);
				v2[1].position = sf::Vector2f(mp.x, mp.y);

				v3[0].position = shape.getPosition();
				v3[1].position = sf::Vector2f(mp.x, mp.y);
			}

			window.draw(v1, 2, sf::Lines);
			window.draw(v2, 2, sf::Lines);
			window.draw(v3, 2, sf::Lines);
		}


		window.draw(pts_text);
		window.draw(text);
		if (debug)
		{
			debug_info.draw_debug(window);
		}
		if (mp.y < 0)
		{
			window.setMouseCursorVisible(1);
		}
		else
		{
			window.setMouseCursorVisible(0);
			window.draw(cursor);
		}
		window.display();
	}

	return 0;
}