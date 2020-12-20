#pragma once
#include <SFML/Graphics.hpp> 

const int RADIUS_GEM          = 30;
const char PATH_TO_GEM[] = "resources\\gem.png";
const sf::Color OUTLINE_COLOR = sf::Color(250, 150, 100);


class Gem: public sf::CircleShape
{
private:
	sf::Color cur_color;
	bool hasOutline = false;
	sf::Texture texture;
	float m_radius;
	std::size_t m_pointCount = 30;
	
public:

	explicit Gem(const float radius = RADIUS_GEM, sf::Color color = sf::Color(0, 0, 0));

	sf::Color getColor();
	bool setColor(sf::Color color);

	std::size_t getPointCount() const;
	sf::Vector2f getPoint(std::size_t index) const;

	void setSelect();
	void delSelect();

};

