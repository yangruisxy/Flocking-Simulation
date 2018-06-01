#include "path.h"
Line::Line(const sf::Vector2f& p1, const sf::Vector2f& p2) :color(sf::Color::Red), thickniess(5.f)
{
	sf::Vector2f direction = p2 - p1;
	sf::Vector2f unitDirection = direction / std::sqrt(direction.x * direction.x + direction.y + direction.y);
	sf::Vector2f unitPerpendicular(-unitDirection.y, unitDirection.x);

	sf::Vector2f offset = (thickniess / 2.f) * unitPerpendicular;

	vertices[0].position = p1 + offset;
	vertices[1].position = p2 + offset;
	vertices[2].position = p2 - offset;
	vertices[3].position = p1 - offset;

	for (int i = 0; i < 4; ++i)
	{
		vertices[i].color = color;
	}
}

void Line::draw(sf::RenderWindow& window) const
{
	window.draw(vertices, 4, sf::Quads);
}