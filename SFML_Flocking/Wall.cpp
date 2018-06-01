#include "Wall.h"
void Wall2d::draw(sf::RenderWindow& window)
{
	window.draw(vertices, 2, sf::Lines);
}