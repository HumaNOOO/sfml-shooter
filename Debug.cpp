#include "Debug.h"

DebugInfo::DebugInfo()
{
	DebugInfo::font.loadFromFile("font.ttf");
	DebugInfo::text.setFont(font);
	DebugInfo::text.setCharacterSize(18);
};

void DebugInfo::update(int fps, double frame_time, double angle, double distance, sf::Vector2i mouse_pos, sf::Vector2f circle_pos, int number_of_bullets,
	int number_of_enemies, int sizeof_bullet, int sizeof_enemy, bool& pause)
{
	if (!pause)
	{
		DebugInfo::debug_str = "";
		DebugInfo::debug_str.append("FPS: " + std::to_string(fps) + ", " + std::to_string(frame_time) + " ms")
			.append("\nangle(deg): " + std::to_string(angle))
			.append("\ndistance(pixels): " + std::to_string(distance))
			.append("\nmouse pos(x,y): (" + std::to_string(mouse_pos.x) + "," + std::to_string(mouse_pos.y) + ")")
			.append("\nplayer pos(x,y): (" + std::to_string(circle_pos.x) + "," + std::to_string(circle_pos.y) + ")")
			.append("\nnumber of:")
			.append("\nbullets: " + std::to_string(number_of_bullets))
			.append("\nenemies: " + std::to_string(number_of_enemies))
			.append("\nmemory usage for: ")
			.append("\nbullets: " + std::to_string(number_of_bullets * sizeof_bullet / 1000.0) + "KB")
			.append("\nenemies: " + std::to_string(number_of_enemies * sizeof_enemy / 1000.0) + "KB");
	}
	DebugInfo::text.setString(debug_str);
}

void DebugInfo::draw_debug(sf::RenderWindow& w)
{
	w.draw(DebugInfo::text);
}