#include "gem.h"



Gem::Gem(const float radius, sf::Color color)
{
	m_radius = radius;
	cur_color = color;
	texture.loadFromFile(PATH_TO_GEM);
	setTexture(&texture);
	setFillColor(color);
	setOutlineColor(OUTLINE_COLOR);
	update();
}

sf::Color Gem::getColor()
{
	return cur_color;
}


bool Gem::setColor(sf::Color color) {
	cur_color = color;
	setFillColor(color);
	return true;
}

std::size_t Gem::getPointCount() const
{
	return m_pointCount; // fixed, but could be an attribute of the class if needed
}

sf::Vector2f Gem::getPoint(std::size_t index) const
{//Без этого не работает, взято из овала, работает с кругом
	static const float pi = 3.141592654f;

	float angle = index * 2 * pi / getPointCount() - pi / 2;
	float x = std::cos(angle) * m_radius;
	float y = std::sin(angle) * m_radius;

	return sf::Vector2f(m_radius + x, m_radius + y);
}

void Gem::delSelect() {
	if (hasOutline)
	{
		setOutlineThickness(0.f);
		hasOutline = !hasOutline;
	}
}

void Gem::setSelect()
{
	if (!hasOutline)
	{
		setOutlineThickness(5.f);
		hasOutline = !hasOutline;
	}
}
