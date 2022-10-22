#include <ctime>
#include "Enemy.h"
#include "Bullet.h"
#include "Debug.h"
#include "Player.h"

int main()
{
	std::vector<Enemy*> enemy_vec;
	std::vector<Bullet*> bullets_vec;
	const int WINDOW_WIDTH = 1920;
	const int WINDOW_HEIGHT = 1080;

	srand(time(0));
	DebugInfo debug_info;
	Player player;
	sf::Vertex v1[2];
	sf::Vertex v2[2];
	sf::Vertex v3[2];
	bool pause = false;
	int pts{};
	bool debug = false;
	int cash = 0;
	int accuracy = 100;
	sf::CircleShape point(3.f);
	point.setOrigin(3, 3);
	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "2D Shooter", sf::Style::Close);
	window.setMouseCursorVisible(0);
	//shape.setFillColor(sf::Color::Green);
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

			if (event.type == sf::Event::KeyReleased)
			{
				if (event.key.code == sf::Keyboard::Escape) pause = pause ? false : true;

				if (event.key.code == sf::Keyboard::U && cash >= 50)
				{
					if (player.get_shot_delay() >= 0.02)
					{
						player.set_shot_delay(player.get_shot_delay() - 0.005);
						cash -= 50;
					}
				}

				if (event.key.code == sf::Keyboard::Y && cash >= 50)
				{
					if (player.get_inaccuracy() >= 1)
					{
						player.set_inaccuracy(player.get_inaccuracy() - 10);
						cash -= 50;
					}
				}

				if (event.key.code == sf::Keyboard::F3) debug = debug ? false : true;
			}
		}
		player.set_points(pts);
		player.set_cash(cash);

		sf::Vector2i mp = sf::Mouse::getPosition(window);
		if (!pause) player.move(dt, WINDOW_WIDTH, WINDOW_HEIGHT, mp);

		if (mp.y < 0) window.setMouseCursorVisible(1);
		else window.setMouseCursorVisible(0);

		if (!pause)
		{
			player.shoot(bullets_vec, dt);

			spawn_delay -= dt;
			if (spawn_delay <= 0)
			{
				spawn_delay = 0.33;
				enemy_vec.insert(enemy_vec.begin(), new Enemy(sf::Vector2f(rand() % WINDOW_WIDTH, rand() % WINDOW_HEIGHT)));
			}
		}

		debug_info.update(1 / dt, dt * 1000, player.player_sprite.getRotation(), sqrt(pow(mp.x - player.player_sprite.getPosition().x, 2) + pow(mp.y - player.player_sprite.getPosition().y, 2)), mp, player.player_sprite.getPosition(),
			bullets_vec.size(), enemy_vec.size(), sizeof(Bullet), sizeof(Enemy), pause);

		if (mp.y < 0)
		{
			window.setMouseCursorVisible(1);
		}
		else
		{
			window.setMouseCursorVisible(0);
		}
		cursor.setPosition(sf::Vector2f(mp.x, mp.y));
		cursor.rotate(dt * 100);
		window.clear();
		player.draw_player(window);

		for (Enemy* e : enemy_vec)
		{
			if (std::find(enemy_vec.begin(), enemy_vec.end(), e) != enemy_vec.end())
			{
				e->draw_enemy(window);
				if (!pause)
				{
					e->step(dt, player.player_sprite.getPosition());
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
				v1[0].position = player.player_sprite.getPosition();
				v1[1].position = sf::Vector2f(mp.x, player.player_sprite.getPosition().y);

				v2[0].position = sf::Vector2f(mp.x, player.player_sprite.getPosition().y);
				v2[1].position = sf::Vector2f(mp.x, mp.y);

				v3[0].position = player.player_sprite.getPosition();
				v3[1].position = sf::Vector2f(mp.x, mp.y);
			}

			window.draw(v1, 2, sf::Lines);
			window.draw(v2, 2, sf::Lines);
			window.draw(v3, 2, sf::Lines);
		}

		window.draw(text);
		if (debug)
		{
			window.draw(point);
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